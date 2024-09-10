void AddInterFormFont(CPDF_Dictionary*& pFormDict,
                      CPDF_Document* pDocument,
                      const CPDF_Font* pFont,
                      CFX_ByteString& csNameTag) {
  if (!pFont) {
    return;
  }
  if (!pFormDict) {
    InitInterFormDict(pFormDict, pDocument);
  }
  CFX_ByteString csTag;
  if (FindInterFormFont(pFormDict, pFont, csTag)) {
    csNameTag = csTag;
    return;
  }
  if (!pFormDict) {
    InitInterFormDict(pFormDict, pDocument);
  }
  CPDF_Dictionary* pDR = pFormDict->GetDict("DR");
  if (!pDR) {
    pDR = new CPDF_Dictionary;
    pFormDict->SetAt("DR", pDR);
  }
  CPDF_Dictionary* pFonts = pDR->GetDict("Font");
  if (!pFonts) {
    pFonts = new CPDF_Dictionary;
    pDR->SetAt("Font", pFonts);
  }
  if (csNameTag.IsEmpty()) {
    csNameTag = pFont->GetBaseFont();
  }
  csNameTag.Remove(' ');
  csNameTag =
      CPDF_InterForm::GenerateNewResourceName(pDR, "Font", 4, csNameTag);
  pFonts->SetAtReference(csNameTag, pDocument, pFont->GetFontDict());
}