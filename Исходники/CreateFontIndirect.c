void
Test_CreateFontIndirectW(void)
{
    LOGFONTW logfont;
    HFONT hFont;
    ULONG ret;
    ENUMLOGFONTEXDVW elfedv2;

    logfont.lfHeight = 12;
    logfont.lfWidth = 0;
    logfont.lfEscapement = 0;
    logfont.lfOrientation = 0;
    logfont.lfWeight = FW_NORMAL;
    logfont.lfItalic = 0;
    logfont.lfUnderline = 0;
    logfont.lfStrikeOut = 0;
    logfont.lfCharSet = DEFAULT_CHARSET;
    logfont.lfOutPrecision = OUT_DEFAULT_PRECIS;
    logfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    logfont.lfQuality = PROOF_QUALITY;
    logfont.lfPitchAndFamily = DEFAULT_PITCH;
    memset(logfont.lfFaceName, 'A', LF_FACESIZE * 2);
    hFont = CreateFontIndirectW(&logfont);
    ok(hFont != 0, "CreateFontIndirectW failed\n");

    memset(&elfedv2, 0, sizeof(elfedv2));
    ret = GetObjectW(hFont, sizeof(elfedv2), &elfedv2);
    ok(ret == sizeof(ENUMLOGFONTEXW) + 2*sizeof(DWORD), "\n");
    ok(elfedv2.elfEnumLogfontEx.elfLogFont.lfFaceName[LF_FACESIZE-1] == ((WCHAR)'A' << 8) + 'A', "\n");
    ok(elfedv2.elfEnumLogfontEx.elfFullName[0] == 0, "\n");
    /* Theres a bunch of data in elfFullName ... */
}