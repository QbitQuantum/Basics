/*
 * Given a BITMAPINFOHEADER, create a palette based on the color table.
 *
 * Returns the handle of a palette, or zero if something went wrong.
 */
static HPALETTE PASCAL NEAR MakeDIBPalette(LPBITMAPINFOHEADER lpInfo)
{
    PLOGPALETTE npPal;
    RGBQUAD FAR *lpRGB;
    HPALETTE hLogPal;
    DWORD i;

    /*
     * since biClrUsed field was filled during the loading of the DIB,
     * we know it contains the number of colors in the color table.
     */
    if (lpInfo->biClrUsed)
    {
        npPal = (PLOGPALETTE)LocalAlloc(LMEM_FIXED, sizeof(LOGPALETTE) +
                                        (WORD)lpInfo->biClrUsed * sizeof(PALETTEENTRY));
        if (!npPal)
            return (FALSE);

        npPal->palVersion = 0x300;
        npPal->palNumEntries = (WORD)lpInfo->biClrUsed;

        /* get pointer to the color table */
        lpRGB = (RGBQUAD FAR *)((LPSTR)lpInfo + lpInfo->biSize);

        /* copy colors from the color table to the LogPalette structure */
        for (i = 0; i < lpInfo->biClrUsed; i++, lpRGB++)
        {
            npPal->palPalEntry[i].peRed = lpRGB->rgbRed;
            npPal->palPalEntry[i].peGreen = lpRGB->rgbGreen;
            npPal->palPalEntry[i].peBlue = lpRGB->rgbBlue;
            npPal->palPalEntry[i].peFlags = PC_NOCOLLAPSE;
        }

        hLogPal = CreatePalette((LPLOGPALETTE)npPal);
        LocalFree((HANDLE)npPal);
        return (hLogPal);
    }

    /*
     * 24-bit DIB with no color table.  return default palette.  Another
     * option would be to create a 256 color "rainbow" palette to provide
     * some good color choices.
     */
    else
    {
        return (GetStockObject(DEFAULT_PALETTE));
    }
}