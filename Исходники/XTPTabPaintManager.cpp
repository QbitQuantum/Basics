void CXTPTabPaintManager::SetFontIndirect(LOGFONT* pLogFont, BOOL bUseStandardFont /*= FALSE*/)
{
	m_bUseStandardFont = bUseStandardFont;

	if (!pLogFont)
		return;

	if (m_bClearTypeTextQuality && XTPSystemVersion()->IsClearTypeTextQualitySupported())
	{
		pLogFont->lfQuality = 5;
	}

	m_fntNormal.DeleteObject();
	m_fntBold.DeleteObject();
	m_fntVerticalNormal.DeleteObject();
	m_fntVerticalBold.DeleteObject();

	pLogFont->lfWeight = m_bBoldNormal ? FW_BOLD : FW_NORMAL;
	VERIFY(m_fntNormal.CreateFontIndirect(pLogFont));

	pLogFont->lfWeight = FW_BOLD;
	VERIFY(m_fntBold.CreateFontIndirect(pLogFont));

	STRCPY_S(pLogFont->lfFaceName, LF_FACESIZE, CXTPDrawHelpers::GetVerticalFontName(FALSE));
	pLogFont->lfOrientation = 900;
	pLogFont->lfEscapement = 2700;
	pLogFont->lfHeight = pLogFont->lfHeight < 0 ? __min(-11, pLogFont->lfHeight) : pLogFont->lfHeight;
	pLogFont->lfWeight = m_bBoldNormal ? FW_BOLD : FW_NORMAL;
	VERIFY(m_fntVerticalNormal.CreateFontIndirect(pLogFont));

	pLogFont->lfWeight = FW_BOLD;
	VERIFY(m_fntVerticalBold.CreateFontIndirect(pLogFont));
}