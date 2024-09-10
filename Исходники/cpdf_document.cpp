CPDF_Font* CPDF_Document::AddWindowsFont(LOGFONTA* pLogFont,
                                         FX_BOOL bVert,
                                         FX_BOOL bTranslateName) {
  pLogFont->lfHeight = -1000;
  pLogFont->lfWidth = 0;
  HGDIOBJ hFont = CreateFontIndirectA(pLogFont);
  HDC hDC = CreateCompatibleDC(nullptr);
  hFont = SelectObject(hDC, hFont);
  int tm_size = GetOutlineTextMetrics(hDC, 0, nullptr);
  if (tm_size == 0) {
    hFont = SelectObject(hDC, hFont);
    DeleteObject(hFont);
    DeleteDC(hDC);
    return nullptr;
  }

  LPBYTE tm_buf = FX_Alloc(BYTE, tm_size);
  OUTLINETEXTMETRIC* ptm = reinterpret_cast<OUTLINETEXTMETRIC*>(tm_buf);
  GetOutlineTextMetrics(hDC, tm_size, ptm);
  int flags = CalculateFlags(false, pLogFont->lfItalic != 0,
                             (pLogFont->lfPitchAndFamily & 3) == FIXED_PITCH,
                             (pLogFont->lfPitchAndFamily & 0xf8) == FF_ROMAN,
                             (pLogFont->lfPitchAndFamily & 0xf8) == FF_SCRIPT,
                             pLogFont->lfCharSet == FXFONT_SYMBOL_CHARSET);

  bool bCJK = pLogFont->lfCharSet == FXFONT_CHINESEBIG5_CHARSET ||
              pLogFont->lfCharSet == FXFONT_GB2312_CHARSET ||
              pLogFont->lfCharSet == FXFONT_HANGUL_CHARSET ||
              pLogFont->lfCharSet == FXFONT_SHIFTJIS_CHARSET;
  CFX_ByteString basefont;
  if (bTranslateName && bCJK)
    basefont = FPDF_GetPSNameFromTT(hDC);

  if (basefont.IsEmpty())
    basefont = pLogFont->lfFaceName;

  int italicangle = ptm->otmItalicAngle / 10;
  int ascend = ptm->otmrcFontBox.top;
  int descend = ptm->otmrcFontBox.bottom;
  int capheight = ptm->otmsCapEmHeight;
  int bbox[4] = {ptm->otmrcFontBox.left, ptm->otmrcFontBox.bottom,
                 ptm->otmrcFontBox.right, ptm->otmrcFontBox.top};
  FX_Free(tm_buf);
  basefont.Replace(" ", "");
  CPDF_Dictionary* pBaseDict = new CPDF_Dictionary(m_pByteStringPool);
  pBaseDict->SetNameFor("Type", "Font");
  CPDF_Dictionary* pFontDict = pBaseDict;
  if (!bCJK) {
    if (pLogFont->lfCharSet == FXFONT_ANSI_CHARSET ||
        pLogFont->lfCharSet == FXFONT_DEFAULT_CHARSET ||
        pLogFont->lfCharSet == FXFONT_SYMBOL_CHARSET) {
      pBaseDict->SetNameFor("Encoding", "WinAnsiEncoding");
    } else {
      CalculateEncodingDict(pLogFont->lfCharSet, pBaseDict);
    }
    int char_widths[224];
    GetCharWidth(hDC, 32, 255, char_widths);
    CPDF_Array* pWidths = new CPDF_Array;
    for (size_t i = 0; i < 224; i++)
      pWidths->AddInteger(char_widths[i]);
    ProcessNonbCJK(pBaseDict, pLogFont->lfWeight > FW_MEDIUM,
                   pLogFont->lfItalic != 0, basefont, pWidths);
  } else {
    pFontDict =
        ProcessbCJK(pBaseDict, pLogFont->lfCharSet, bVert, basefont,
                    [&hDC](FX_WCHAR start, FX_WCHAR end, CPDF_Array* widthArr) {
                      InsertWidthArray(hDC, start, end, widthArr);
                    });
  }
  AddIndirectObject(pBaseDict);
  CPDF_Array* pBBox = new CPDF_Array;
  for (int i = 0; i < 4; i++)
    pBBox->AddInteger(bbox[i]);
  CPDF_Dictionary* pFontDesc =
      CalculateFontDesc(this, basefont, flags, italicangle, ascend, descend,
                        pBBox, pLogFont->lfWeight / 5);
  pFontDesc->SetIntegerFor("CapHeight", capheight);
  pFontDict->SetReferenceFor("FontDescriptor", this,
                             AddIndirectObject(pFontDesc));
  hFont = SelectObject(hDC, hFont);
  DeleteObject(hFont);
  DeleteDC(hDC);
  return LoadFont(pBaseDict);
}