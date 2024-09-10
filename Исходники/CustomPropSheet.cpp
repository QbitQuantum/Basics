BOOL CCustomPropSheet::OnInitDialog(void)
{
	__super::OnInitDialog();

	// get the font for the first active page
	CPropertyPage* pCurPage = GetActivePage();
	ASSERT(pCurPage != NULL);

	// change the font for the sheet
	ChangeDialogFont(this, &m_fontPage, CDF_CENTER);

	// change the font for each page
	for (int i = 0, cPages = GetPageCount(); i < cPages; ++i)
	{
		CPropertyPage* pPage = GetPage(i);
		ASSERT(pPage != NULL);
#if !defined(_BUGFIX_)
		ChangeDialogFont(pPage, &m_fontPage, CDF_CENTER);
#else
		ChangeDialogFont(pPage, &m_fontPage, CDF_TOPLEFT);
#endif   // _BUGFIX_
	}

	// set and save the size of the page
	CTabCtrl* pTab = GetTabControl();
	ASSERT(pTab != NULL);

	if ((m_psh.dwFlags & PSH_WIZARD) != 0)
	{
		pTab->ShowWindow(SW_HIDE);
#if !defined(_BUGFIX_)
		GetClientRect(&m_rcPage);
		CWnd* pButton = GetDlgItem(ID_WIZBACK);
		ASSERT(pButton != NULL);
		CRect rectButton;
		pButton->GetWindowRect(rectButton);
		ScreenToClient(rectButton);
		m_rcPage.bottom = rectButton.top - 2;
#else
		CRect rectDivider;
		CWnd* pDivider = GetDlgItem(0x3026);
		ASSERT(pDivider != NULL);
		pDivider->GetWindowRect(rectDivider);
		ScreenToClient(rectDivider);
		m_rcPage.bottom = rectDivider.top - 2;
#endif   // _BUGFIX_
	}
	else
	{
		pTab->GetWindowRect(&m_rcPage);
		ScreenToClient(&m_rcPage);
		pTab->AdjustRect(FALSE, &m_rcPage);
	}

	// resize the page
	pCurPage->MoveWindow(&m_rcPage);

	return (TRUE);
}