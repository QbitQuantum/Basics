int32 CFont::m_InitMaterial(void)
{
    // Establish the font and texture size
    p_TextScale  = 1.0f; // Draw fonts into texture without scaling

    // Large fonts need larger textures
    if (p_FontHeight > 40) p_TexWidth = p_TexHeight = 1024;
    else if (p_FontHeight > 20) p_TexWidth = p_TexHeight = 512;
    else p_TexWidth = p_TexHeight = 256;

    // If requested texture is too big, use a smaller texture and smaller font,
    // and scale up when rendering.
    D3DCAPS8 d3dCaps;
    p_RenderLib->p_Device->GetDeviceCaps(&d3dCaps);

    if (p_TexWidth > d3dCaps.MaxTextureWidth)
    {
        p_TextScale = (float4)d3dCaps.MaxTextureWidth / (float4)p_TexWidth;
        p_TexWidth = p_TexHeight = d3dCaps.MaxTextureWidth;
    }

	// setup del materiale da usare
	p_Texture=new CGraphicSurface(p_TexWidth, p_TexHeight, 32);

    // Prepare to create a bitmap
    int32      *pBitmapBits;
    BITMAPINFO bmi;
    ZeroMemory(&bmi.bmiHeader,  sizeof(BITMAPINFOHEADER));
    bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth       =  (int32)p_TexWidth;
    bmi.bmiHeader.biHeight      = -(int32)p_TexHeight;
    bmi.bmiHeader.biPlanes      = 1;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biBitCount    = 32;

    // Create a DC and a bitmap for the font
    HDC hDC = CreateCompatibleDC(NULL);
    HBITMAP hbmBitmap = CreateDIBSection(hDC, &bmi, DIB_RGB_COLORS,
                                         (void **)&pBitmapBits, NULL, 0);
    SetMapMode(hDC, MM_TEXT);

    INT nHeight    = -MulDiv(p_FontHeight, 
        (INT)(GetDeviceCaps(hDC, LOGPIXELSY)*p_TextScale), 72);
    int32 dwBold   = (p_FontFlags & FONT_BOLD)   ? FW_BOLD : FW_NORMAL;
    int32 dwItalic = (p_FontFlags & FONT_ITALIC) ? TRUE    : FALSE;
    HFONT hFont    = CreateFont(nHeight, 0, 0, 0, dwBold, dwItalic,
                          FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                          CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
                          VARIABLE_PITCH, p_FontName);
    if (NULL==hFont) return(0);

    SelectObject(hDC, hbmBitmap);
    SelectObject(hDC, hFont);
    // Set text properties
    SetTextColor(hDC, RGB(255,255,255));
    SetBkColor(hDC, 0x00000000);
    SetTextAlign(hDC, TA_TOP);
    // Loop through all printable character and output them to the bitmap..
    // Meanwhile, keep track of the corresponding tex coords for each character.
    int32 x = 0;
    int32 y = 0;
    char8 str[2];
    SIZE size;

    for (char8 c=32; c<127; c++)
    {
        str[0] = c;
        GetTextExtentPoint32(hDC, str, 1, &size);

        if ((int32)(x+size.cx+1) > p_TexWidth)
        {
            x  = 0;
            y += size.cy+1;
        }
        ExtTextOut(hDC, x+0, y+0, ETO_OPAQUE, NULL, str, 1, NULL);
        p_TexCoords[c-32][0] = ((float4)(x+0))/p_TexWidth;
        p_TexCoords[c-32][1] = ((float4)(y+0))/p_TexHeight;
        p_TexCoords[c-32][2] = ((float4)(x+0+size.cx))/p_TexWidth;
        p_TexCoords[c-32][3] = ((float4)(y+0+size.cy))/p_TexHeight;
        x += size.cx+1;
    }

    int32 *pDst32=(int32 *)p_Texture->p_Pixels;
    uchar8 bAlpha;

    for (y=0; y<p_TexHeight; y++)
    {
      for (x=0; x<p_TexWidth; x++)
      {
         bAlpha = (uchar8)((pBitmapBits[p_TexWidth*y + x] & 0xff));
         if (bAlpha > 0) *pDst32++ = (bAlpha << 24) | 0x00ffffff;
         else *pDst32++ = 0x00000000;
      }
    }

    DeleteObject(hbmBitmap);
    DeleteDC(hDC);
    DeleteObject(hFont);
	p_RenderLib->m_AddUpdate_AlphaTexture(p_Texture, 1);
	return(1);
}