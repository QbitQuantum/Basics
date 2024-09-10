int CRaster::Draw(CDC* pDC, POINT point,SIZE size) 
{
    HDC         hDC;
    CPalette*   oldPal;

    oldPal  = 0;

    hDC     =   pDC->m_hDC;
    if(pal) {
        oldPal  =   pDC->SelectPalette(pal, TRUE);
    }/* if */

    pDC->SetStretchBltMode(COLORONCOLOR);

    StretchDIBits(  hDC, 
                    point.x,        point.y, 
                    size.cx,        size.cy,
                    XSrc,           YSrc,
                    SrcWidth,       SrcHeight,
                    imgData,        imgInfo,
                    DIB_RGB_COLORS, SRCCOPY);

    if(pal) {
        pDC->SelectPalette(oldPal, TRUE);
    }/* if */

    return 1;
}/* CRaster::Draw */