static VOID
NT5_DrawLogoffCaptionText(LPWSTR lpText,
                          HDC hdcMem)
{
    HFONT hFont;
    LOGFONTW LogFont;
    RECT TextRect;
    INT PrevBkMode;

    /* Setup the font we'll use */
    ZeroMemory(&LogFont, sizeof(LOGFONTW));
    LogFont.lfCharSet = DEFAULT_CHARSET;
    LogFont.lfHeight = 22;
    LogFont.lfWeight = 109; // From WinXP disassembly
    wcscpy_s(LogFont.lfFaceName, LF_FACESIZE, L"Arial");

    /* Create it */
    hFont = CreateFontIndirectW(&LogFont);
    if (hFont)
    {
        /* Set the font and font colour */
        SelectObject(hdcMem, hFont);
        SetTextColor(hdcMem, RGB(255, 255, 255));

        /* Create the text rect */
        TextRect.top = (g_pInfo->cy / 2) + 34;
        TextRect.bottom = (g_pInfo->cy / 2) + 34 + (GetDeviceCaps(hdcMem, LOGPIXELSY));
        TextRect.left = g_pInfo->cx / 3;
        TextRect.right = (g_pInfo->cx / 2) + 35 + 137;

        /* Set the background mode to transparent */
        PrevBkMode = SetBkMode(hdcMem, TRANSPARENT);

        /* Draw the text to the mem DC */
        DrawTextW(hdcMem,
                  lpText,
                  -1,
                  &TextRect,
                  DT_NOPREFIX | DT_WORDBREAK | DT_RIGHT); // WinXP disassembly uses 0x812

        /* Set the previous background mode */
        SetBkMode(hdcMem, PrevBkMode);

        /* Delete the font */
        DeleteObject(hFont);
    }
}