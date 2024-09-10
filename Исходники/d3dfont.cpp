//-----------------------------------------------------------------------------
// Name: InitDeviceObjects()
// Desc: Initializes device-dependent objects, including the vertex buffer used
//       for rendering text and the texture map which stores the font image.
//-----------------------------------------------------------------------------
HRESULT CD3DFont::InitDeviceObjects(
    LPDIRECTDRAW7 pDD,
    LPDIRECT3DDEVICE7 pd3dDevice
    )
{
    HRESULT hr;

    // Keep a local copy of the device
    m_pd3dDevice = pd3dDevice;

    typedef enum FontFormats
    {
        eNull,
        eX4R4G4B4,
        eR5G6B5,
        eX8R8G8B8,
    }FontFormats;

    FontFormats fmt = eNull;

    // Establish the font and texture size
    m_fTextScale  = 1.0f; // Draw fonts into texture without scaling

    // Large fonts need larger textures
    if( m_dwFontHeight > 40 )
        m_dwTexWidth = m_dwTexHeight = 1024;
    else if( m_dwFontHeight > 20 )
        m_dwTexWidth = m_dwTexHeight = 512;
    else
        m_dwTexWidth  = m_dwTexHeight = 256;

    // If requested texture is too big, use a smaller texture and smaller font,
    // and scale up when rendering.
    D3DDEVICEDESC7 d3dCaps;
    m_pd3dDevice->GetCaps( &d3dCaps );

    if( m_dwTexWidth > d3dCaps.dwMaxTextureWidth )
    {
        m_fTextScale = (FLOAT)d3dCaps.dwMaxTextureWidth / (FLOAT)m_dwTexWidth;
        m_dwTexWidth = m_dwTexHeight = d3dCaps.dwMaxTextureWidth;
    }

    DDSURFACEDESC2 ddsd;
    INITDDSTRUCT(ddsd);

    ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PIXELFORMAT;

    ddsd.ddsCaps.dwCaps  = DDSCAPS_TEXTURE;
    ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE | DDSCAPS2_HINTSTATIC;

    ddsd.dwWidth  = m_dwTexWidth;
    ddsd.dwHeight = m_dwTexHeight;


    IDirectDrawSurface7 * pRT = NULL;
    hr = m_pd3dDevice->GetRenderTarget( &pRT );
    if( SUCCEEDED(hr) && pRT )
    {
        DDSURFACEDESC2 ddsd_rt;
        INITDDSTRUCT(ddsd_rt);
        ddsd_rt.dwFlags = DDSD_PIXELFORMAT;

        hr = pRT->GetSurfaceDesc( &ddsd_rt );
        if( SUCCEEDED( hr ))
        {
            memcpy( (LPVOID)&(ddsd.ddpfPixelFormat), (LPVOID)&(ddsd_rt.ddpfPixelFormat), sizeof( DDPIXELFORMAT));
        }

        if( ddsd.ddpfPixelFormat.dwRGBBitCount == 32)
        {
            fmt = eX8R8G8B8;
        }
        else if( ddsd.ddpfPixelFormat.dwRGBBitCount == 16 )
        {
            if( ddsd.ddpfPixelFormat.dwRBitMask == 0xF000 &&
                ddsd.ddpfPixelFormat.dwGBitMask == 0x00F0 &&
                ddsd.ddpfPixelFormat.dwBBitMask == 0x000F)
            {
                fmt = eX4R4G4B4;
            }
            else if ( ddsd.ddpfPixelFormat.dwRBitMask == 0xF800 &&
                      ddsd.ddpfPixelFormat.dwGBitMask == 0x7E0 &&
                      ddsd.ddpfPixelFormat.dwBBitMask == 0x1F )
            {
                fmt = eR5G6B5;
            }
        }
    }
    if(FAILED(hr))
    {
        ddsd.ddpfPixelFormat.dwFourCC = BI_RGB;
        ddsd.ddpfPixelFormat.dwFlags  = DDPF_RGB;
        ddsd.ddpfPixelFormat.dwRGBBitCount     = 16;
        ddsd.ddpfPixelFormat.dwRGBAlphaBitMask = 0xF000;
        ddsd.ddpfPixelFormat.dwRBitMask = 0x0F00;
        ddsd.ddpfPixelFormat.dwGBitMask = 0x00F0;
        ddsd.ddpfPixelFormat.dwBBitMask = 0x000F;
        fmt = eX4R4G4B4;
    }
    if( pRT )
    {
        pRT->Release();
        pRT = NULL;
    }

    // Create a new texture for the font
    hr = pDD->CreateSurface(&ddsd, &m_pTexture, NULL);

    if( FAILED(hr) )
        return hr;


    // Prepare to create a bitmap
    DWORD * pBitmapBits;
    BITMAPINFO bmi;
    ZeroMemory( &bmi.bmiHeader,   sizeof(BITMAPINFOHEADER));
    bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth       =  (int)m_dwTexWidth;
    bmi.bmiHeader.biHeight      = -(int)m_dwTexHeight;
    bmi.bmiHeader.biPlanes      = 1;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biBitCount    = 32;

    // Create a DC and a bitmap for the font
    HDC hDC = CreateCompatibleDC( NULL );
    if( NULL == hDC )
        return E_FAIL;

    HBITMAP hbmBitmap = CreateDIBSection( hDC, &bmi, DIB_RGB_COLORS,
                                          (VOID**)&pBitmapBits, NULL, 0 );
    SetMapMode( hDC, MM_TEXT );

    // Create a font.  By specifying ANTIALIASED_QUALITY, we might get an
    // antialiased font, but this is not guaranteed.
    INT nHeight    = -MulDiv( m_dwFontHeight,
                             (INT)(GetDeviceCaps(hDC, LOGPIXELSY) * m_fTextScale), 72 );
    DWORD dwBold   = (m_dwFontFlags&D3DFONT_BOLD)   ? FW_BOLD : FW_NORMAL;
    DWORD dwItalic = (m_dwFontFlags&D3DFONT_ITALIC) ? TRUE    : FALSE;
    HFONT hFont    = CreateFont( nHeight, 0, 0, 0, dwBold, dwItalic,
                                 FALSE, FALSE, DEFAULT_CHARSET, OUT_STRING_PRECIS,
                                 CLIP_STROKE_PRECIS, ANTIALIASED_QUALITY,
                                 VARIABLE_PITCH, m_strFontName );
    if( NULL==hFont )
        return E_FAIL;

    SelectObject( hDC, hbmBitmap );
    SelectObject( hDC, hFont );

    // Set text properties
    SetTextColor( hDC, RGB(255,255,255) );
    SetBkColor(   hDC, 0x00000000 );
    SetTextAlign( hDC, TA_TOP );

    // Loop through all printable character and output them to the bitmap..
    // Meanwhile, keep track of the corresponding tex coords for each character.
    DWORD x = 0;
    DWORD y = 0;
    TCHAR str[2] = _T("x");
    SIZE size;

    for( TCHAR c=32; c<127; c++ )
    {
        str[0] = c;
        GetTextExtentPoint32( hDC, str, 1, &size );

        if( (DWORD)(x+size.cx+1) > m_dwTexWidth )
        {
            x  = 0;
            y += size.cy+1;
        }

        ExtTextOut( hDC, x+0, y+0, ETO_OPAQUE, NULL, str, 1, NULL );

        m_fTexCoords[c-32][0] = ((FLOAT)(x+0))/m_dwTexWidth;
        m_fTexCoords[c-32][1] = ((FLOAT)(y+0))/m_dwTexHeight;
        m_fTexCoords[c-32][2] = ((FLOAT)(x+0+size.cx))/m_dwTexWidth;
        m_fTexCoords[c-32][3] = ((FLOAT)(y+0+size.cy))/m_dwTexHeight;

        x += size.cx+1;
    }

    if( fmt == eNull )
    {
        OutputDebugString( TEXT("\n*** WARNING: This sample shows text only in one of the following formats: X8R8G8B8, X4R4G4B4, or R5G6B5. Text functions are DISABLED\n"));
    }

    // Lock the surface and write the alpha values for the set pixels
    m_pTexture->Lock(NULL, &ddsd, DDLOCK_NOSYSLOCK | DDLOCK_WAIT, NULL);

    switch( fmt )
    {
    case eX4R4G4B4:
        {
            WORD* pDst16 = (WORD*)ddsd.lpSurface;
            BYTE bAlpha; // 4-bit measure of pixel intensity

            for( y=0; y < m_dwTexHeight; y++ )
            {
                for( x=0; x < m_dwTexWidth; x++ )
                {
                    bAlpha = (BYTE)((pBitmapBits[m_dwTexWidth*y + x] & 0xff) >> 4);
                    if (bAlpha > 0)
                    {
                        *pDst16++ = (WORD) ((bAlpha << 12) | 0x0fff);
                    }
                    else
                    {
                        *pDst16++ = 0x0000;
                    }
                }
            }
        }
        break;
    case eX8R8G8B8:
        {
            DWORD* pDst32 = (DWORD*)ddsd.lpSurface;
            BYTE bAlpha; // 4-bit measure of pixel intensity

            for( y=0; y < m_dwTexHeight; y++ )
            {
                for( x=0; x < m_dwTexWidth; x++ )
                {
                    bAlpha = (BYTE)((pBitmapBits[m_dwTexWidth*y + x] & 0xff));
                    if (bAlpha > 0)
                    {
                        *pDst32++ = (DWORD) ((bAlpha << 24) | 0x00ffffff);
                    }
                    else
                    {
                        *pDst32++ = 0x0000;
                    }
                }
            }
        }
        break;
    case eR5G6B5:
        {
            WORD* pDst16 = (WORD*)ddsd.lpSurface;
            BYTE bAlpha; // 4-bit measure of pixel intensity

            for( y=0; y < m_dwTexHeight; y++ )
            {
                for( x=0; x < m_dwTexWidth; x++ )
                {
                    bAlpha = (BYTE)((pBitmapBits[m_dwTexWidth*y + x] & 0xff) >> 3);
                    if (bAlpha > 0)
                    {
                        *pDst16++ = (WORD) ((bAlpha << 11) | (bAlpha << 6) | bAlpha);
                    }
                    else
                    {
                        *pDst16++ = 0x0000;
                    }
                }
            }
        }
    }// switch


    // Done updating texture, so clean up used objects
    m_pTexture->Unlock(NULL);
    DeleteObject( hbmBitmap );
    DeleteDC( hDC );
    DeleteObject( hFont );

    return S_OK;
}