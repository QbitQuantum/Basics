//------------------------------------------------------------------------------------
D3D11Texture::D3D11Texture( const StringVector& vecTexNames )
    :m_pTexture2D(nullptr)
    ,m_pTexture3D(nullptr)
    ,m_pRenderSystem(g_env.pRenderSystem)
    ,m_rtView(nullptr)
    ,m_pSRV(nullptr)
    ,m_pDSV(nullptr)
    ,m_usage(0)
    ,m_texType(eTextureType_TextureArray)
    ,m_bMipMap(true)
{
    m_pd3dDevice = m_pRenderSystem->GetDevice();
    if (m_pd3dDevice)
        m_pd3dDevice->AddRef();

    assert(!vecTexNames.empty());

    HRESULT hr = S_OK;
    // First load all texture elements
    std::vector<ID3D11Texture2D*> vecTexs(vecTexNames.size());
    for (size_t i=0; i<vecTexNames.size(); ++i)
    {
        D3DX11_IMAGE_LOAD_INFO loadInfo;
        loadInfo.Width  = D3DX11_FROM_FILE;
        loadInfo.Height = D3DX11_FROM_FILE;
        loadInfo.Depth  = D3DX11_FROM_FILE;
        loadInfo.FirstMipLevel = 0;
        loadInfo.BindFlags = 0;
        loadInfo.Usage = D3D11_USAGE_STAGING;	// Local res
        loadInfo.MipLevels = 0;
        loadInfo.CpuAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
        loadInfo.MiscFlags = 0;
        loadInfo.Format = DXGI_FORMAT_FROM_FILE;
        loadInfo.Filter = D3DX11_FILTER_NONE;
        loadInfo.MipFilter = D3DX11_FILTER_LINEAR;
        loadInfo.pSrcInfo  = 0;

        V(D3DX11CreateTextureFromFileA(m_pRenderSystem->GetDevice(), vecTexNames[i].c_str(),
                                       &loadInfo, nullptr, (ID3D11Resource**)&vecTexs[i], nullptr));
    }

    // Then create the texture array object
    D3D11_TEXTURE2D_DESC texElementDesc;
    vecTexs[0]->GetDesc(&texElementDesc);

    // Store dimension and format
    m_width = texElementDesc.Width;
    m_height = texElementDesc.Height;

    m_texFormat = ConvertFromDXFormat(texElementDesc.Format);

    D3D11_TEXTURE2D_DESC texArrayDesc;
    texArrayDesc.Width              = texElementDesc.Width;
    texArrayDesc.Height             = texElementDesc.Height;
    texArrayDesc.MipLevels          = texElementDesc.MipLevels;
    texArrayDesc.ArraySize          = vecTexs.size();
    texArrayDesc.Format             = texElementDesc.Format;
    texArrayDesc.SampleDesc.Count   = 1;
    texArrayDesc.SampleDesc.Quality = 0;
    texArrayDesc.Usage              = D3D11_USAGE_DEFAULT;
    texArrayDesc.BindFlags          = D3D11_BIND_SHADER_RESOURCE;
    texArrayDesc.CPUAccessFlags     = 0;
    texArrayDesc.MiscFlags          = 0;

    V(m_pRenderSystem->GetDevice()->CreateTexture2D( &texArrayDesc, 0, &m_pTexture2D));

    // Fill texture array data
    ID3D11DeviceContext* dc = m_pRenderSystem->GetDeviceContext();

    for(size_t texElement=0; texElement<vecTexs.size(); ++texElement)
    {
        for(UINT mipLevel = 0; mipLevel < texElementDesc.MipLevels; ++mipLevel)
        {
            D3D11_MAPPED_SUBRESOURCE mappedTex2D;
            V(dc->Map(vecTexs[texElement], mipLevel, D3D11_MAP_READ, 0, &mappedTex2D));

            dc->UpdateSubresource(m_pTexture2D,
                                  D3D11CalcSubresource(mipLevel, texElement, texElementDesc.MipLevels),
                                  0, mappedTex2D.pData, mappedTex2D.RowPitch, mappedTex2D.DepthPitch);

            dc->Unmap(vecTexs[texElement], mipLevel);
        }
    }

    CreateSRV();

    for(size_t i=0; i<vecTexs.size(); ++i)
        vecTexs[i]->Release();
}