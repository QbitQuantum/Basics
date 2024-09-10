HFF
TestFdLoadFontFileTE (
    ULONG cFiles,
    ULONG *piFile,
    PVOID *ppvView,
    ULONG *pcjView,
    ULONG ulLangId
    )
{

    FONTFILE *pff = NULL;
    ULONG cjIFI;

    BYTE *pjView0 = (BYTE *)ppvView[0];
    BYTE *pjView1 = (BYTE *)ppvView[1];

    ULONG cjView0 = pcjView[0];
    ULONG cjView1 = pcjView[1];


    ulLangId;

    if (cFiles != 2)
        return 0;

// first file contains facename only

    cjIFI = ALIGN4(sizeof(IFIMETRICS) + (cjView0 + 1) * sizeof(WCHAR));

    pff = (FONTFILE*)EngAllocMem(0, sizeof(FONTFILE) + cjIFI, EXFDTAG);

    if (pff)
    {
        WCHAR *pwszFace;
        ULONG cwc = cjView0; // wcslen(pwszFace);
        IFIMETRICS * pifi;

        pff->id = 0Xff;

    // remember these so that we can open files later

        pff->iFilePFM = piFile[0];
        pff->iFilePFB = piFile[1];
        pff->ulGlyph = *pjView1; // just touch it to be sure it is mapped

        pifi = pff->pifi = (IFIMETRICS *)(pff+1);

        memset((PVOID)pifi, 0, cjIFI);
        pifi->cjThis = cjIFI;
        pifi->dpwszFaceName  = sizeof(IFIMETRICS);
        pifi->dpwszFamilyName = pifi->dpwszFaceName;

    // point to terminating zero

        pifi->dpwszStyleName = pifi->dpwszFaceName
                                    +sizeof(WCHAR) * cwc;
        pifi->dpwszUniqueName = pifi->dpwszStyleName;

        pwszFace = (WCHAR *)((BYTE*)pifi + pifi->dpwszFaceName);

        EngMultiByteToWideChar(
            1252,                  //   CodePage,
            pwszFace,              // LPWSTR WideCharString,
            cwc * sizeof(WCHAR) ,  // BytesInWideCharString,
            (LPSTR)pjView0,        // MultiByteString
            (INT)cjView0           // BytesInMultiByteString
            );

        if (cwc > 2)
            cwc-=2; // hack to get rid of \r\n at the end of the line

        pwszFace[cwc] = L'\0';     // zero terminate

        pifi->fwdWinAscender = 4;
        pifi->fwdWinDescender = 3;
        pifi->fwdUnitsPerEm = pifi->fwdWinDescender + pifi->fwdWinAscender;

        pifi->usWinWeight = 400;

        pifi->flInfo = (  FM_INFO_TECH_BITMAP
                        | FM_INFO_RETURNS_BITMAPS
                        | FM_INFO_1BPP
                        | FM_INFO_INTEGER_WIDTH
                        | FM_INFO_RIGHT_HANDED
                        | FM_INFO_NONNEGATIVE_AC
                       );

        pifi->fwdMacAscender   =  pifi->fwdWinAscender;
        pifi->fwdMacDescender  = -pifi->fwdWinDescender;
        pifi->fwdMacLineGap    =  0;

        pifi->fwdTypoAscender  = pifi->fwdMacAscender;
        pifi->fwdTypoDescender = pifi->fwdMacDescender;
        pifi->fwdTypoLineGap   = pifi->fwdMacLineGap;

        pifi->fwdMaxCharInc    = pifi->fwdAveCharWidth  = 5;

        pifi->fwdUnderscoreSize = 1;
        pifi->fwdUnderscorePosition = -(FWORD)(pifi->fwdUnderscoreSize / 2 + 1);
        pifi->fwdStrikeoutSize = pifi->fwdUnderscoreSize;
        pifi->fwdStrikeoutPosition = pifi->fwdWinAscender / 2;

        pifi->wcFirstChar   = pifi->chFirstChar   = THEGLYPH;
        pifi->wcLastChar    = pifi->chLastChar    = THEGLYPH;
        pifi->wcBreakChar   = pifi->chBreakChar   = THEGLYPH;
        pifi->wcDefaultChar = pifi->chDefaultChar = THEGLYPH;

        pifi->fwdCapHeight = pifi->fwdUnitsPerEm/2;
        pifi->fwdXHeight   = pifi->fwdUnitsPerEm/4;

        pifi->dpCharSets = 0; // no multiple charsets in bm fonts

    // All the fonts that this font driver will see are to be rendered left
    // to right

        pifi->ptlBaseline.x = 1;
        pifi->ptlBaseline.y = 0;

        pifi->ptlAspect.y = 1;
        pifi->ptlAspect.x = 1;

        pifi->rclFontBox.left   = 0;
        pifi->rclFontBox.top    = (LONG) pifi->fwdTypoAscender;
        pifi->rclFontBox.right  = (LONG) pifi->fwdMaxCharInc;
        pifi->rclFontBox.bottom = (LONG) pifi->fwdTypoDescender;

    // achVendorId, unknown, don't bother figure it out from copyright msg

        pifi->achVendId[0] = 'U';
        pifi->achVendId[1] = 'n';
        pifi->achVendId[2] = 'k';
        pifi->achVendId[3] = 'n';

    }

    return (HFF)pff;
}