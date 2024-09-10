//-------------------------------------------------------------------------------------
bool _IsAlphaAllOpaqueBC( _In_ const Image& cImage )
{
    if ( !cImage.pixels )
        return false;

    // Promote "typeless" BC formats
    DXGI_FORMAT cformat;
    switch( cImage.format )
    {
    case DXGI_FORMAT_BC1_TYPELESS:  cformat = DXGI_FORMAT_BC1_UNORM; break;
    case DXGI_FORMAT_BC2_TYPELESS:  cformat = DXGI_FORMAT_BC2_UNORM; break;
    case DXGI_FORMAT_BC3_TYPELESS:  cformat = DXGI_FORMAT_BC3_UNORM; break;
    case DXGI_FORMAT_BC7_TYPELESS:  cformat = DXGI_FORMAT_BC7_UNORM; break;
    default:                        cformat = cImage.format;         break;
    }

    // Determine BC format decoder
    BC_DECODE pfDecode;
    size_t sbpp;
    switch(cformat)
    {
    case DXGI_FORMAT_BC1_UNORM:
    case DXGI_FORMAT_BC1_UNORM_SRGB:    pfDecode = D3DXDecodeBC1;   sbpp = 8;   break;
    case DXGI_FORMAT_BC2_UNORM:
    case DXGI_FORMAT_BC2_UNORM_SRGB:    pfDecode = D3DXDecodeBC2;   sbpp = 16;  break;
    case DXGI_FORMAT_BC3_UNORM:
    case DXGI_FORMAT_BC3_UNORM_SRGB:    pfDecode = D3DXDecodeBC3;   sbpp = 16;  break;
    case DXGI_FORMAT_BC7_UNORM:
    case DXGI_FORMAT_BC7_UNORM_SRGB:    pfDecode = D3DXDecodeBC7;   sbpp = 16;  break;
    default:
        // BC4, BC5, and BC6 don't have alpha channels
        return false;
    }

    // Scan blocks for non-opaque alpha
    static const XMVECTORF32 threshold = { 0.99f, 0.99f, 0.99f, 0.99f };

    XMVECTOR temp[16];
    const uint8_t *pPixels = cImage.pixels;
    for( size_t h = 0; h < cImage.height; h += 4 )
    {
        const uint8_t *ptr = pPixels;
        size_t ph = std::min<size_t>( 4, cImage.height - h );
        size_t w = 0;
        for( size_t count = 0; count < cImage.rowPitch; count += sbpp, w += 4 )
        {
            pfDecode( temp, ptr );

            size_t pw = std::min<size_t>( 4, cImage.width - w );
            assert( pw > 0 && ph > 0 );

            if ( pw == 4 && ph == 4 )
            {
                // Full blocks
                for( size_t j = 0; j < 16; ++j )
                {
                    XMVECTOR alpha = XMVectorSplatW( temp[j] );
                    if ( XMVector4Less( alpha, threshold ) )
                        return false;
                }
            }
            else
            {
                // Handle partial blocks
                for( size_t y = 0; y < ph; ++y )
                {
                    for( size_t x = 0; x < pw; ++x )
                    {
                        XMVECTOR alpha = XMVectorSplatW( temp[ y * 4 + x ] );
                        if ( XMVector4Less( alpha, threshold ) )
                            return false;
                    }
                }
            }

            ptr += sbpp;
        }

        pPixels += cImage.rowPitch;
    }

    return true;
}