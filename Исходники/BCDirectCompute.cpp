//-------------------------------------------------------------------------------------
_Use_decl_annotations_
HRESULT GPUCompressBC::Compress( const Image& srcImage, const Image& destImage )
{
    if ( !srcImage.pixels || !destImage.pixels )
        return E_INVALIDARG;

    if ( srcImage.width != destImage.width
         || srcImage.height != destImage.height
         || srcImage.width != m_width
         || srcImage.height != m_height
         || srcImage.format != m_srcformat
         || destImage.format != m_bcformat )
    {
        return E_UNEXPECTED;
    }

    //--- Create input texture --------------------------------------------------------
    auto pDevice = m_device.Get();
    if ( !pDevice )
        return E_POINTER;

    // We need to avoid the hardware doing additional colorspace conversion
    DXGI_FORMAT inputFormat = ( m_srcformat == DXGI_FORMAT_R8G8B8A8_UNORM_SRGB ) ? DXGI_FORMAT_R8G8B8A8_UNORM : m_srcformat;

    ScopedObject<ID3D11Texture2D> sourceTex;
    {
        D3D11_TEXTURE2D_DESC desc;
        memset( &desc, 0, sizeof(desc) );
        desc.Width = static_cast<UINT>( srcImage.width );
        desc.Height = static_cast<UINT>( srcImage.height ); 
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = inputFormat;
        desc.SampleDesc.Count = 1;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

        D3D11_SUBRESOURCE_DATA initData;
        initData.pSysMem = srcImage.pixels;
        initData.SysMemPitch = static_cast<DWORD>( srcImage.rowPitch );
        initData.SysMemSlicePitch = static_cast<DWORD>( srcImage.slicePitch );

        HRESULT hr = pDevice->CreateTexture2D( &desc, &initData, sourceTex.GetAddressOf() );
        if ( FAILED(hr) )
        {
            return hr;
        }
    }

    ScopedObject<ID3D11ShaderResourceView> sourceSRV;
    {
        D3D11_SHADER_RESOURCE_VIEW_DESC desc;
        memset( &desc, 0, sizeof(desc) );
        desc.Texture2D.MipLevels = 1;
        desc.Format = inputFormat;
        desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

        HRESULT hr = pDevice->CreateShaderResourceView( sourceTex.Get(), &desc, sourceSRV.ReleaseAndGetAddressOf() );
        if ( FAILED(hr) )
        {
            return hr;
        }
    }

    //--- Compress using DirectCompute ------------------------------------------------
    bool isbc7 = false;
    switch( m_bcformat )
    {
    case DXGI_FORMAT_BC6H_TYPELESS:
    case DXGI_FORMAT_BC6H_UF16:
    case DXGI_FORMAT_BC6H_SF16:
        break;

    case DXGI_FORMAT_BC7_TYPELESS:
    case DXGI_FORMAT_BC7_UNORM:
    case DXGI_FORMAT_BC7_UNORM_SRGB:
        isbc7 = true;
        break;

    default:
        return E_UNEXPECTED;
    }

    const UINT MAX_BLOCK_BATCH = 64;

    auto pContext = m_context.Get();
    if ( !pContext )
        return E_UNEXPECTED;

    size_t xblocks = std::max<size_t>( 1, (m_width + 3) >> 2 );
    size_t yblocks = std::max<size_t>( 1, (m_height + 3) >> 2 );

    UINT num_total_blocks = static_cast<UINT>( xblocks * yblocks );
    UINT num_blocks = num_total_blocks;
    int start_block_id = 0;
    while (num_blocks > 0)
    {
        UINT n = std::min<UINT>( num_blocks, MAX_BLOCK_BATCH );
        UINT uThreadGroupCount = n;

        {
            D3D11_MAPPED_SUBRESOURCE mapped;
            HRESULT hr = pContext->Map( m_constBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped );
            if ( FAILED(hr) )
                return hr;

            ConstantsBC6HBC7 param;
            param.tex_width = static_cast<UINT>( srcImage.width );
            param.num_block_x = static_cast<UINT>( xblocks );
            param.format = m_bcformat;
            param.mode_id = 0;
            param.start_block_id = start_block_id;
            param.num_total_blocks = num_total_blocks;
            param.alpha_weight = m_alphaWeight;
            memcpy( mapped.pData, &param, sizeof( param ) );

            pContext->Unmap( m_constBuffer.Get(), 0 );
        }

        if ( isbc7 )
        {
            //--- BC7 -----------------------------------------------------------------
            ID3D11ShaderResourceView* pSRVs[] = { sourceSRV.Get(), nullptr };
            RunComputeShader( pContext, m_BC7_tryMode456CS.Get(), pSRVs, 2, m_constBuffer.Get(),
                              m_err1UAV.Get(), std::max<UINT>(uThreadGroupCount / 4, 1) );

            for ( UINT i = 0; i < 3; ++i )
            {
                static const UINT modes[] = { 1, 3, 7 };
                {
                    D3D11_MAPPED_SUBRESOURCE mapped;
                    HRESULT hr = pContext->Map( m_constBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped );
                    if ( FAILED(hr) )
                    {
                        ResetContext( pContext );
                        return hr;
                    }

                    ConstantsBC6HBC7 param;
                    param.tex_width = static_cast<UINT>( srcImage.width );
                    param.num_block_x = static_cast<UINT>( xblocks );
                    param.format = m_bcformat;
                    param.mode_id = modes[i];
                    param.start_block_id = start_block_id;
                    param.num_total_blocks = num_total_blocks;
                    param.alpha_weight = m_alphaWeight;
                    memcpy( mapped.pData, &param, sizeof( param ) );
                    pContext->Unmap( m_constBuffer.Get(), 0 );
                }

                pSRVs[1] = (i & 1) ? m_err2SRV.Get() : m_err1SRV.Get();
                RunComputeShader( pContext, m_BC7_tryMode137CS.Get(), pSRVs, 2, m_constBuffer.Get(),
                                  (i & 1) ? m_err1UAV.Get() : m_err2UAV.Get(), uThreadGroupCount );
            }               

            for ( UINT i = 0; i < 2; ++i )
            {
                static const UINT modes[] = { 0, 2 };
                {
                    D3D11_MAPPED_SUBRESOURCE mapped;
                    HRESULT hr = pContext->Map( m_constBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped );
                    if ( FAILED(hr) )
                    {
                        ResetContext( pContext );
                        return hr;
                    }

                    ConstantsBC6HBC7 param;
                    param.tex_width = static_cast<UINT>( srcImage.width );
                    param.num_block_x = static_cast<UINT>( xblocks );
                    param.format = m_bcformat;
                    param.mode_id = modes[i];
                    param.start_block_id = start_block_id;
                    param.num_total_blocks = num_total_blocks;
                    param.alpha_weight = m_alphaWeight;
                    memcpy( mapped.pData, &param, sizeof( param ) );
                    pContext->Unmap( m_constBuffer.Get(), 0 );
                }

                pSRVs[1] = (i & 1) ? m_err1SRV.Get() : m_err2SRV.Get();
                RunComputeShader( pContext, m_BC7_tryMode02CS.Get(), pSRVs, 2, m_constBuffer.Get(),
                                  (i & 1) ? m_err2UAV.Get() : m_err1UAV.Get(), uThreadGroupCount );
            }

            pSRVs[1] = m_err2SRV.Get();
            RunComputeShader( pContext, m_BC7_encodeBlockCS.Get(), pSRVs, 2, m_constBuffer.Get(),
                              m_outputUAV.Get(), std::max<UINT>(uThreadGroupCount / 4, 1) );
        }
        else
        {
            //--- BC6H ----------------------------------------------------------------
            ID3D11ShaderResourceView* pSRVs[] = { sourceSRV.Get(), nullptr };
            RunComputeShader( pContext, m_BC6H_tryModeG10CS.Get(), pSRVs, 2, m_constBuffer.Get(),
                              m_err1UAV.Get(), std::max<UINT>(uThreadGroupCount / 4, 1) );

            for ( UINT i = 0; i < 10; ++i )
            {
                {
                    D3D11_MAPPED_SUBRESOURCE mapped;
                    HRESULT hr = pContext->Map( m_constBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped );
                    if ( FAILED(hr) )
                    {
                        ResetContext( pContext );
                        return hr;
                    }

                    ConstantsBC6HBC7 param;
                    param.tex_width = static_cast<UINT>( srcImage.width );
                    param.num_block_x = static_cast<UINT>( xblocks );
                    param.format = m_bcformat;
                    param.mode_id = i;
                    param.start_block_id = start_block_id;
                    param.num_total_blocks = num_total_blocks;
                    memcpy( mapped.pData, &param, sizeof( param ) );
                    pContext->Unmap( m_constBuffer.Get(), 0 );
                }

                pSRVs[1] = (i & 1) ? m_err2SRV.Get() : m_err1SRV.Get();
                RunComputeShader( pContext, m_BC6H_tryModeLE10CS.Get(), pSRVs, 2, m_constBuffer.Get(),
                                  (i & 1) ? m_err1UAV.Get() : m_err2UAV.Get(), std::max<UINT>(uThreadGroupCount / 2, 1) );
            }               

            pSRVs[1] = m_err1SRV.Get();
            RunComputeShader( pContext, m_BC6H_encodeBlockCS.Get(), pSRVs, 2, m_constBuffer.Get(),
                              m_outputUAV.Get(), std::max<UINT>(uThreadGroupCount / 2, 1) );
        }

        start_block_id += n;
        num_blocks -= n;
    }

    ResetContext( pContext );

    //--- Copy output texture back to CPU ---------------------------------------------

    pContext->CopyResource( m_outputCPU.Get(), m_output.Get() );

    D3D11_MAPPED_SUBRESOURCE mapped;
    HRESULT hr = pContext->Map( m_outputCPU.Get(), 0, D3D11_MAP_READ, 0, &mapped );
    if ( SUCCEEDED(hr) )
    {
        const uint8_t *pSrc = reinterpret_cast<const uint8_t *>( mapped.pData );
        uint8_t *pDest = destImage.pixels;

        size_t pitch = xblocks * sizeof( BufferBC6HBC7 );

        size_t rows = std::max<size_t>( 1, ( destImage.height + 3 ) >> 2 );

        for( size_t h = 0; h < rows; ++h )
        {
            memcpy( pDest, pSrc, destImage.rowPitch );

            pSrc += pitch;
            pDest += destImage.rowPitch;
        }

        pContext->Unmap( m_outputCPU.Get(), 0 );
    }

    return hr;
}