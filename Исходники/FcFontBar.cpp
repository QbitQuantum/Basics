void CFcFontBar::SetSelectedFontName(const CString& SelectString, BOOL bEnable) 
{
	CComboBox* pCb = (CComboBox*)GetDlgItem(ID_FORMAT_FONTNAME);
	ASSERT_VALID(pCb);

	if (SelectString.GetLength() > 0)
		pCb->SelectString(-1, SelectString);
	else
		pCb->SetCurSel(-1);

	pCb->EnableWindow(bEnable);
}