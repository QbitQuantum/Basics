void COutputDialog::OnNMClickListFilter(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);

	CWnd* pList = GetDlgItem(IDC_LIST_FILTER);
	int nSelected = ListView_GetSelectionMark(pList->m_hWnd);

	BOOL bFilterSelected = FALSE;
	if (nSelected >= 0)
	{
		bFilterSelected = TRUE;
	}

	CWnd* pBtnFilterSetting	= GetDlgItem(IDC_BTN_FILTER_SETTING);
	CWnd* pBtnFilterDelete	= GetDlgItem(IDC_BTN_FILTER_DELETE);
	CWnd* pBtnFilterUp		= GetDlgItem(IDC_BTN_FILTER_UP);
	CWnd* pBtnFilterDown	= GetDlgItem(IDC_BTN_FILTER_DOWN);

	if(pBtnFilterSetting && ::IsWindow(pBtnFilterSetting->m_hWnd))
		pBtnFilterSetting->EnableWindow(bFilterSelected);
	if(pBtnFilterDelete && ::IsWindow(pBtnFilterDelete->m_hWnd))
		pBtnFilterDelete->EnableWindow(bFilterSelected);
	if(pBtnFilterUp && ::IsWindow(pBtnFilterUp->m_hWnd))
		pBtnFilterUp->EnableWindow(bFilterSelected);
	if(pBtnFilterDown && ::IsWindow(pBtnFilterDown->m_hWnd))
		pBtnFilterDown->EnableWindow(bFilterSelected);

	if(pResult) *pResult = 0;
}