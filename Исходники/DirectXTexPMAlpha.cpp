static HRESULT _PremultiplyAlpha( _In_ const Image& srcImage, _In_ const Image& destImage )
{
    assert( srcImage.width == destImage.width );
    assert( srcImage.height == destImage.height );

    ScopedAlignedArrayXMVECTOR scanline( reinterpret_cast<XMVECTOR*>( _aligned_malloc( (sizeof(XMVECTOR)*srcImage.width), 16 ) ) );
    if ( !scanline )
        return E_OUTOFMEMORY;

    const uint8_t *pSrc = srcImage.pixels;
    uint8_t *pDest = destImage.pixels;
    if ( !pSrc || !pDest )
        return E_POINTER;

    for( size_t h = 0; h < srcImage.height; ++h )
    {
        if ( !_LoadScanline( scanline.get(), srcImage.width, pSrc, srcImage.rowPitch, srcImage.format ) )
            return E_FAIL;

        XMVECTOR* ptr = scanline.get();
        for( size_t w = 0; w < srcImage.width; ++w )
        {
            XMVECTOR v = *ptr;
            XMVECTOR alpha = XMVectorSplatW( *ptr );
            alpha = XMVectorMultiply( v, alpha );
            *(ptr++) = XMVectorSelect( v, alpha, g_XMSelect1110 );
        }

        if ( !_StoreScanline( pDest, destImage.rowPitch, destImage.format, scanline.get(), srcImage.width ) )
            return E_FAIL;

        pSrc += srcImage.rowPitch;
        pDest += destImage.rowPitch;
    }

    return S_OK;
}