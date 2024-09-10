void CTemplateDialog::OnDblClkTemplate(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
	CWnd *pOkButton = GetDlgItem(IDC_BUTTON_CREATE);
	if (!pOkButton || !pOkButton->IsWindowEnabled())
		return;

	// simulate click on button
	OnCreate();

	*pResult = 0;
}