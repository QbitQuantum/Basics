BOOL bTestGRC (
    HDC         hdc
    )
{
    ULONG   row = 0;                    // screen row coordinate to print at
    HFONT   hfont;
    HFONT   hfontOriginal;
    LOGFONT lfnt;
    TEXTMETRIC  tm;
    PSZ     pszPitch, pszFamily;
    RASTERIZER_STATUS   rstat;

// Clear the screen to black.

    BitBlt(hdc, 0, 0, CX, CY, (HDC) 0, 0, 0, 0);

// Get a font.

    memset(&lfnt, 0, sizeof(lfnt));
    lstrcpy(lfnt.lfFaceName, "Courier New");
    lfnt.lfHeight = 21;
    lfnt.lfWeight = 400;

    if ((hfont = CreateFontIndirect(&lfnt)) == NULL)
    {
        DbgPrint("bTestGRC: Logical font creation failed.\n");
        return FALSE;
    }

    hfontOriginal = SelectObject(hdc, hfont);

// Get text metrics

    if (!GetTextMetrics (hdc, &tm))
    {
        DbgPrint("bTestGRC: GetTextMetrics failed.\n");
    }

// Call GetRasterizerCaps.

    if ( !GetRasterizerCaps(&rstat, sizeof(RASTERIZER_STATUS)) )
    {
        DbgPrint("bTestGRC: GetRasterizerCaps failed.\n");
        return FALSE;
    }

// Print those mothers!

    sprintf(szOutText, "RASTERIZER STATUS");
    TextOut(hdc, 0, row, szOutText, strlen(szOutText));
    row += tm.tmHeight+tm.tmExternalLeading;

    sprintf(szOutText, "nSize = %ld (0x%lx)", rstat.nSize, rstat.nSize);
    TextOut(hdc, 0, row, szOutText, strlen(szOutText));
    row += tm.tmHeight+tm.tmExternalLeading;

    sprintf(szOutText, "wFlags = %s%s", (rstat.wFlags & TT_ENABLED)? "enabled ":"", (rstat.wFlags & TT_AVAILABLE)? "available":"");
    TextOut(hdc, 0, row, szOutText, strlen(szOutText));
    row += tm.tmHeight+tm.tmExternalLeading;

    sprintf(szOutText, "nLanguageID = %ld (0x%lx)", rstat.nLanguageID, rstat.nLanguageID);
    TextOut(hdc, 0, row, szOutText, strlen(szOutText));
    row += tm.tmHeight+tm.tmExternalLeading;

// Avoid any weirdness (incomplete text output) in case a break point
// is inserted after this call.

    GdiFlush();

// Restore the font.

    SelectObject(hdc, hfontOriginal);
    DeleteObject(hfont);

    return TRUE;
}