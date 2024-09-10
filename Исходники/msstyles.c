/* Prepare a bitmap to be used for alpha blending */
static BOOL prepare_alpha (HBITMAP bmp, BOOL* hasAlpha)
{
    DIBSECTION dib;
    int n;
    BYTE* p;

    *hasAlpha = FALSE;

    if (!bmp || GetObjectW( bmp, sizeof(dib), &dib ) != sizeof(dib))
        return FALSE;

    if(dib.dsBm.bmBitsPixel != 32)
        /* nothing to do */
        return TRUE;

    *hasAlpha = TRUE;
    p = dib.dsBm.bmBits;
    n = dib.dsBmih.biHeight * dib.dsBmih.biWidth;
    /* AlphaBlend() wants premultiplied alpha, so do that now */
    while (n-- > 0)
    {
        int a = p[3]+1;
        p[0] = (p[0] * a) >> 8;
        p[1] = (p[1] * a) >> 8;
        p[2] = (p[2] * a) >> 8;
        p += 4;
    }

    return TRUE;
}