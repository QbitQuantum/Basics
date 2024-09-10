void CSmartFieldsDialog::InitList()
{
	if (m_pList == NULL)
	{
		m_pList = CreateListBox();
	}
	m_pList->SubclassDlgItem(IDC_MACRO_LIST, this);

/* Set the splitter offset. Line it up with the value text. */

	CWnd* pValueText = GetDlgItem(IDC_VALUE);
	ASSERT(pValueText != NULL);

	CRect crValueText;
	pValueText->GetWindowRect(crValueText);
	CRect crList;
	m_pList->GetWindowRect(crList);
	m_pList->SplitterOffset(crValueText.left - crList.left);
}