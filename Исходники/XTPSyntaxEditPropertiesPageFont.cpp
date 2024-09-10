void CXTPSyntaxEditPropertiesPageFont::OnSelChangeComboNames()
{
	if (!m_wndComboName.GetListBox().SelChanged())
		return;

	if (GetLBText(m_wndComboName, m_csName) == CB_ERR)
		return;

	LOGFONT lf = {0};
	if (!GetSafeLogFont(lf))
		return;

	STRCPY_S(lf.lfFaceName, m_csName.GetLength() + 1, m_csName);

	if (CreateSafeFontIndirect(m_editFont, lf))
	{
		UpdateSampleFont();
		InitSizeCombo();
		InitScriptCombo();
		SetModified(TRUE);
	}
}