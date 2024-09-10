BOOL
FASTCALL
GetCharOutline(
    IN     LONG            Unknown,
           PVOID,
    IN     PVOID           pThis,
    IN     ULONG           Height,
    IN     WCHAR           uChar,
    OUT    PULONG          pBitsPerRow,
    IN OUT PULONG          pDescent,
    IN OUT ALICE_MEMORY   *pMem
)
{
    HDC   hDC;
    HFONT hFont;
    ULONG FontIndex, OutlineSize, BytesPerRow, BitsOfLeftSpace;
    GLYPHMETRICS GlyphMetrics;
    BYTE  Buffer[0x5000];
    PBYTE pbOutline, pbBuffer;
    FONT_OUTLINE_INFO *pOutlineInfo;

    static FONT_OUTLINE_INFO *s_pOutlineInfo;
    static MAT2  mat = { { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 1 } };

    pOutlineInfo = s_pOutlineInfo;
    if (s_pOutlineInfo == NULL)
    {
        HANDLE hHeap = CMem::GetGlobalHeap();
        if (hHeap == NULL)
        {
            hHeap = CMem::CreateGlobalHeap();
            if (hHeap == NULL)
                goto DEFAULT_PROC;
        }

        pOutlineInfo = (FONT_OUTLINE_INFO *)HeapAlloc(hHeap, 0, sizeof(*pOutlineInfo));
        if (pOutlineInfo == NULL)
            goto DEFAULT_PROC;

        s_pOutlineInfo = pOutlineInfo;

        pOutlineInfo->hDC = NULL;
        pOutlineInfo->LastFontIndex = -1;
        ZeroMemory(pOutlineInfo->hFont, sizeof(pOutlineInfo->hFont));
        FillMemory(pOutlineInfo->Descent, sizeof(pOutlineInfo->Descent), -1);
    }

    if (Unknown < 0 || IsCharSpec(uChar))
        goto DEFAULT_PROC;

    FontIndex = Height / FONT_STEP;
    if (FontIndex > countof(pOutlineInfo->hFont))
        goto DEFAULT_PROC;

    hDC = pOutlineInfo->hDC;
    if (hDC == NULL)
    {
        hDC = CreateCompatibleDC(NULL);
        if (hDC == NULL)
            goto DEFAULT_PROC;

        pOutlineInfo->hDC = hDC;
    }

    hFont = pOutlineInfo->hFont[FontIndex];
    if (hFont == NULL)
    {
        LOGFONTW lf;

        ZeroMemory(&lf, sizeof(lf));
        lf.lfHeight = Height;
        lf.lfWeight = FW_NORMAL;
        lf.lfCharSet = GB2312_CHARSET;
        lf.lfQuality = CLEARTYPE_QUALITY;
        lf.lfPitchAndFamily = FIXED_PITCH;
        CopyStruct(lf.lfFaceName, g_szFaceName, sizeof(g_szFaceName));

        hFont = CreateFontIndirectW(&lf);
        if (hFont == NULL)
            goto DEFAULT_PROC;

        pOutlineInfo->hFont[FontIndex] = hFont;
    }

    if (FontIndex != pOutlineInfo->LastFontIndex)
    {
        if (SelectObject(hDC, hFont) == HGDI_ERROR)
            goto DEFAULT_PROC;

        pOutlineInfo->LastFontIndex = FontIndex;
    }

    if (pDescent != NULL)
    {
        TEXTMETRICW tm;

        tm.tmDescent = pOutlineInfo->Descent[FontIndex];
        if (tm.tmDescent == -1)
        {
            if (GetTextMetricsW(hDC, &tm))
                pOutlineInfo->Descent[FontIndex] = tm.tmDescent;
            else
                ++tm.tmDescent;
        }

        *pDescent = tm.tmDescent;
        if (pBitsPerRow == NULL)
            return TRUE;
    }

    uChar = MBCharToUnicode(uChar);
    OutlineSize = GetGlyphOutlineW(
                    hDC,
                    uChar,
                    GGO_BITMAP,
                    &GlyphMetrics,
                    sizeof(Buffer),
                    pThis == NULL ? NULL : Buffer,
                    &mat);
    if (OutlineSize == GDI_ERROR)
        goto DEFAULT_PROC;

#if 0
    ULONG DwordOfLeftSpace, BytesPerRowRaw, Mask;
    static BYTE Bits[FONT_COUNT] = 
    {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x16,
        0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14,
        0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E,
        0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
        0x29, 0x2A, 0x2B, 0x2C
    };

    BitsOfLeftSpace = Bits[FontIndex];
    BitsOfLeftSpace = 4;
    DwordOfLeftSpace = BitsOfLeftSpace / 8 / 4;
    if (pBitsPerRow != NULL)
        *pBitsPerRow = GlyphMetrics.gmBlackBoxX + BitsOfLeftSpace % bitsof(DWORD) + DwordOfLeftSpace * 4 * 8;

    if (pDescent != NULL)
    {
        TEXTMETRICW tm;

        tm.tmDescent = s_Descent[FontIndex];
        if (tm.tmDescent == -1)
        {
            if (GetTextMetricsW(hDC, &tm))
                s_Descent[FontIndex] = tm.tmDescent;
            else
                ++tm.tmDescent;
        }

        *pDescent = tm.tmDescent;
    }

    if (pThis == NULL)
        return TRUE;

    BytesPerRow = GlyphMetrics.gmBlackBoxX + BitsOfLeftSpace;
    BytesPerRow = ROUND_UP(BytesPerRow, bitsof(DWORD)) / 8;
    BitsOfLeftSpace %= bitsof(DWORD);

    ChipSpriteEngAllocMemory(pMem, BytesPerRow * Height);
    if (pMem->pvBufferEnd == pMem->pvBuffer)
        goto DEFAULT_PROC;

    ZeroMemory(pMem->pvBuffer, BytesPerRow * Height);

    BytesPerRowRaw = ROUND_UP(GlyphMetrics.gmBlackBoxX, bitsof(DWORD)) / 8;

    pbBuffer   = Buffer;
    pbOutline  = (PBYTE)pMem->pvBuffer;
    pbOutline += (GlyphMetrics.gmBlackBoxY - 1) * BytesPerRow;
    pbOutline += ((Height - GlyphMetrics.gmBlackBoxY) / 2 - 1) * BytesPerRow;
    pbOutline += DwordOfLeftSpace * 4;
    Mask = _rotl(1, BitsOfLeftSpace) - 1;

    for (ULONG i = GlyphMetrics.gmBlackBoxY; i; --i)
    {
        PBYTE pbOutline2, pbBuffer2;
        DWORD BitsHigh, BitsLow;

        BitsHigh = 0;
        BitsLow = 0;
        pbBuffer2 = pbBuffer;
        pbOutline2 = pbOutline;
        for (ULONG Count = BytesPerRowRaw / 4; Count; --Count)
        {
            DWORD v = *(PDWORD)pbBuffer2;

            BitsHigh = _rotl(v, BitsOfLeftSpace) & Mask;
            v = (v << BitsOfLeftSpace) | BitsLow;
            BitsLow = BitsHigh;
            *(PDWORD)pbOutline2 = v;
            pbOutline2 += 4;
            pbBuffer2  += 4;
        }
//        *(PDWORD)pbOutline2 = BitsLow;

        pbOutline -= BytesPerRow;
        pbBuffer  += BytesPerRowRaw;
    }

    WCHAR buf[0x500];
    wsprintfW(
        buf - 1 + GetTextFaceW(hDC, countof(buf),
        buf),
        L" Char = %c Index = %02u Bits = %02X",
        uChar,
        FontIndex + 1,
        BitsOfLeftSpace);
    SetWindowTextW(GetActiveWindow(), buf);

#else
    ULONG BytesPerRowRaw;
    static BYTE Bits[FONT_COUNT] = 
    {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x16,
        0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14,
        0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E,
        0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
        0x29, 0x2A, 0x2B, 0x2C
    };

    BitsOfLeftSpace = Bits[FontIndex];

    if (pBitsPerRow != NULL)
        *pBitsPerRow = GlyphMetrics.gmBlackBoxX + BitsOfLeftSpace;


    if (pThis == NULL)
        return TRUE;

    BytesPerRow = GlyphMetrics.gmBlackBoxX + BitsOfLeftSpace;
    BytesPerRow = ROUND_UP(BytesPerRow, bitsof(DWORD)) / 8;

    ChipSpriteEngAllocMemory(pMem, BytesPerRow * Height);
    if (pMem->pvBufferEnd == pMem->pvBuffer)
        goto DEFAULT_PROC;

    ZeroMemory(pMem->pvBuffer, BytesPerRow * Height);

    BytesPerRowRaw = ROUND_UP(GlyphMetrics.gmBlackBoxX, bitsof(DWORD)) / 8;

    pbBuffer   = Buffer;
    pbOutline  = (PBYTE)pMem->pvBuffer;
    pbOutline += (GlyphMetrics.gmBlackBoxY - 1) * BytesPerRow;
    pbOutline += ((Height - GlyphMetrics.gmBlackBoxY) / 2 - 1) * BytesPerRow;

    for (ULONG i = GlyphMetrics.gmBlackBoxY; i; --i)
    {
        __movsd(pbOutline, pbBuffer, BytesPerRowRaw / 4);
        pbOutline -= BytesPerRow;
        pbBuffer  += BytesPerRowRaw;
    }
#endif

    return TRUE;

DEFAULT_PROC:
    if (pThis == NULL)
        return FALSE;

    return OldGetCharOutline(Unknown, 0, pThis, Height, uChar, pBitsPerRow, pDescent, pMem);
}