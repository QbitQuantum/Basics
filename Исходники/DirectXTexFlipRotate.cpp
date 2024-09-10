//-------------------------------------------------------------------------------------
// Flip/rotate image (complex)
//-------------------------------------------------------------------------------------
_Use_decl_annotations_
HRESULT FlipRotate( const Image* srcImages, size_t nimages, const TexMetadata& metadata,
                    DWORD flags, ScratchImage& result )
{
    if ( !srcImages || !nimages )
        return E_INVALIDARG;

    if ( IsCompressed( metadata.format ) )
    {
        // We don't support flip/rotate operations on compressed images
        return HRESULT_FROM_WIN32( ERROR_NOT_SUPPORTED );
    }

    static_assert( TEX_FR_ROTATE0 == WICBitmapTransformRotate0, "TEX_FR_ROTATE0 no longer matches WIC" );
    static_assert( TEX_FR_ROTATE90 == WICBitmapTransformRotate90, "TEX_FR_ROTATE90 no longer matches WIC" );
    static_assert( TEX_FR_ROTATE180 == WICBitmapTransformRotate180, "TEX_FR_ROTATE180 no longer matches WIC" );
    static_assert( TEX_FR_ROTATE270 == WICBitmapTransformRotate270, "TEX_FR_ROTATE270 no longer matches WIC" );
    static_assert( TEX_FR_FLIP_HORIZONTAL == WICBitmapTransformFlipHorizontal, "TEX_FR_FLIP_HORIZONTAL no longer matches WIC" );
    static_assert( TEX_FR_FLIP_VERTICAL == WICBitmapTransformFlipVertical, "TEX_FR_FLIP_VERTICAL no longer matches WIC" );

    // Only supports 90, 180, 270, or no rotation flags... not a combination of rotation flags
    switch ( flags & (TEX_FR_ROTATE90|TEX_FR_ROTATE180|TEX_FR_ROTATE270) )
    {
    case 0:
    case TEX_FR_ROTATE90:
    case TEX_FR_ROTATE180:
    case TEX_FR_ROTATE270:
        break;

    default:
        return E_INVALIDARG;
    }

    TexMetadata mdata2 = metadata;

    bool flipwh = false;
    if (flags & (TEX_FR_ROTATE90|TEX_FR_ROTATE270))
    {
        flipwh = true;
        mdata2.width = metadata.height;
        mdata2.height = metadata.width;
    }

    HRESULT hr = result.Initialize( mdata2 );
    if ( FAILED(hr) )
        return hr;

    if ( nimages != result.GetImageCount() )
    {
        result.Release();
        return E_FAIL;
    }

    const Image* dest = result.GetImages();
    if ( !dest )
    {
        result.Release();
        return E_POINTER;
    }

    WICPixelFormatGUID pfGUID;
    bool wicpf = _DXGIToWIC( metadata.format, pfGUID );

    for( size_t index=0; index < nimages; ++index )
    {
        const Image& src = srcImages[ index ];
        if ( src.format != metadata.format )
        {
            result.Release();
            return E_FAIL;
        }

#ifdef _AMD64_
        if ( (src.width > 0xFFFFFFFF) || (src.height > 0xFFFFFFFF) )
            return E_FAIL;
#endif

        const Image& dst = dest[ index ];
        assert( dst.format == metadata.format );

        if ( flipwh )
        {
            if ( src.width != dst.height || src.height != dst.width )
            {
                result.Release();
                return E_FAIL;
            }
        }
        else
        {
            if ( src.width != dst.width || src.height != dst.height )
            {
                result.Release();
                return E_FAIL;
            }
        }

        if (wicpf)
        {
            // Case 1: Source format is supported by Windows Imaging Component
            hr = _PerformFlipRotateUsingWIC( src, flags, pfGUID, dst );
        }
        else
        {
            // Case 2: Source format is not supported by WIC, so we have to convert, flip/rotate, and convert back
            hr = _PerformFlipRotateViaF32( src, flags, dst );
        }

        if ( FAILED(hr) )
        {
            result.Release();
            return hr;
        }
    }

    return S_OK;
}