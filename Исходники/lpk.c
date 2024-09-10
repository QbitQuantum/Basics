/*
 * @implemented 
 */
BOOL
WINAPI
LpkExtTextOut(
    HDC hdc,
    int x,
    int y,
    UINT fuOptions,
    const RECT *lprc,
    LPCWSTR lpString,
    UINT uCount,
    const INT *lpDx,
    INT unknown)
{
    LPWORD glyphs = NULL;
    INT cGlyphs;

    UNREFERENCED_PARAMETER(unknown);

    if (!(fuOptions & ETO_IGNORELANGUAGE))
        fuOptions |= ETO_IGNORELANGUAGE;

    /* Check text direction */
    if ((GetLayout(hdc) & LAYOUT_RTL) || (GetTextAlign(hdc) & TA_RTLREADING))
    {
        if (!(fuOptions & ETO_RTLREADING))
            fuOptions |= ETO_RTLREADING;
    }

    /* Check if the string requires complex script processing and not a "glyph indices" array */
    if (ScriptIsComplex(lpString, uCount, SIC_COMPLEX) == S_OK && !(fuOptions & ETO_GLYPH_INDEX))
    {
        BIDI_Reorder(hdc, lpString, uCount, GCP_REORDER,
                     (fuOptions & ETO_RTLREADING) ? WINE_GCPW_FORCE_RTL : WINE_GCPW_FORCE_LTR,
                     NULL, uCount, NULL, &glyphs, &cGlyphs);

        fuOptions |= ETO_GLYPH_INDEX;

        if (uCount > cGlyphs)
            cGlyphs = uCount;

        return ExtTextOutW(hdc, x, y, fuOptions, lprc, (LPWSTR)glyphs, cGlyphs, lpDx);
    }

    return ExtTextOutW(hdc, x, y, fuOptions, lprc, lpString, uCount, lpDx);
}