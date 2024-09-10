//-------------------------------------------------------------------------------------
// Resize image (complex)
//-------------------------------------------------------------------------------------
_Use_decl_annotations_
HRESULT Resize( const Image* srcImages, size_t nimages, const TexMetadata& metadata,
                size_t width, size_t height, DWORD filter, ScratchImage& result )
{
    if ( !srcImages || !nimages || width == 0 || height == 0 )
        return E_INVALIDARG;

#ifdef _M_X64
    if ( (width > 0xFFFFFFFF) || (height > 0xFFFFFFFF) )
        return E_INVALIDARG;
#endif

    TexMetadata mdata2 = metadata;
    mdata2.width = width;
    mdata2.height = height;
    mdata2.mipLevels = 1;
    HRESULT hr = result.Initialize( mdata2 );
    if ( FAILED(hr) )
        return hr;

    bool usewic = _UseWICFiltering( metadata.format, filter );

    WICPixelFormatGUID pfGUID = {0};
    bool wicpf = ( usewic ) ? _DXGIToWIC( metadata.format, pfGUID, true ) : false;

    switch ( metadata.dimension )
    {
    case TEX_DIMENSION_TEXTURE1D:
    case TEX_DIMENSION_TEXTURE2D:
        assert( metadata.depth == 1 );

        for( size_t item = 0; item < metadata.arraySize; ++item )
        {
            size_t srcIndex = metadata.ComputeIndex( 0, item, 0 );
            if ( srcIndex >= nimages )
            {
                result.Release();
                return E_FAIL;
            }

            const Image* srcimg = &srcImages[ srcIndex ];
            const Image* destimg = result.GetImage( 0, item, 0 );
            if ( !srcimg || !destimg )
            {
                result.Release();
                return E_POINTER;
            }

            if ( srcimg->format != metadata.format )
            {
                result.Release();
                return E_FAIL;
            }

#ifdef _M_X64
            if ( (srcimg->width > 0xFFFFFFFF) || (srcimg->height > 0xFFFFFFFF) )
            {
                result.Release();
                return E_FAIL;
            }
#endif

            if ( usewic )
            {
                if ( wicpf )
                {
                    // Case 1: Source format is supported by Windows Imaging Component
                    hr = _PerformResizeUsingWIC( *srcimg, filter, pfGUID, *destimg );
                }
                else
                {
                    // Case 2: Source format is not supported by WIC, so we have to convert, resize, and convert back
                    hr = _PerformResizeViaF32( *srcimg, filter, *destimg );
                }
            }
            else
            {
                // Case 3: not using WIC resizing
                hr = _PerformResizeUsingCustomFilters( *srcimg, filter, *destimg );
            }

            if ( FAILED(hr) )
            {
                result.Release();
                return hr;
            }
        }
        break;

    case TEX_DIMENSION_TEXTURE3D:
        assert( metadata.arraySize == 1 );

        for( size_t slice = 0; slice < metadata.depth; ++slice )
        {
            size_t srcIndex = metadata.ComputeIndex( 0, 0, slice );
            if ( srcIndex >= nimages )
            {
                result.Release();
                return E_FAIL;
            }

            const Image* srcimg = &srcImages[ srcIndex ];
            const Image* destimg = result.GetImage( 0, 0, slice );
            if ( !srcimg || !destimg )
            {
                result.Release();
                return E_POINTER;
            }

            if ( srcimg->format != metadata.format )
            {
                result.Release();
                return E_FAIL;
            }

#ifdef _M_X64
            if ( (srcimg->width > 0xFFFFFFFF) || (srcimg->height > 0xFFFFFFFF) )
            {
                result.Release();
                return E_FAIL;
            }
#endif

            if ( usewic )
            {
                if ( wicpf )
                {
                    // Case 1: Source format is supported by Windows Imaging Component
                    hr = _PerformResizeUsingWIC( *srcimg, filter, pfGUID, *destimg );
                }
                else
                {
                    // Case 2: Source format is not supported by WIC, so we have to convert, resize, and convert back
                    hr = _PerformResizeViaF32( *srcimg, filter, *destimg );
                }
            }
            else
            {
                // Case 3: not using WIC resizing
                hr = _PerformResizeUsingCustomFilters( *srcimg, filter, *destimg );
            }

            if ( FAILED(hr) )
            {
                result.Release();
                return hr;
            }
        }
        break;

    default:
        result.Release();
        return E_FAIL;
    }

    return S_OK;
}