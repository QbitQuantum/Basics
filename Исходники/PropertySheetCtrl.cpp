void CBCGPPropertySheetCtrl::ResizeControl()
{
	CWnd* pTabCtrl = GetTabControl();
	if (m_wndTab.GetSafeHwnd() != NULL)
	{
		pTabCtrl = &m_wndTab;
		m_wndTab.SetButtonsVisible(FALSE);
	}

	if (pTabCtrl->GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	pTabCtrl->SetWindowPos(NULL, 
		0, 0, rectClient.Width(), rectClient.Height(), 
		SWP_NOZORDER | SWP_NOACTIVATE);

	int nPageCount = CBCGPPropertySheet::GetPageCount();

	int nXBorder = ::GetSystemMetrics(SM_CXEDGE);
	int nYBorder = ::GetSystemMetrics(SM_CYEDGE);
	
	for (int nPage = 0; nPage <= nPageCount - 1; nPage++)
	{
		CPropertyPage* pPage = GetPage(nPage);
		if (pPage->GetSafeHwnd() != NULL)
		{
			CRect rectPage;

			pPage->GetWindowRect(&rectPage);
			pTabCtrl->ScreenToClient(rectPage);

			pPage->SetWindowPos(NULL, 
				rectPage.left, rectPage.top, 
				rectClient.Width() - nXBorder * 3, 
				rectClient.Height() - rectPage.top - nYBorder,
				SWP_NOZORDER | SWP_NOACTIVATE);
		}
	}

	RedrawWindow();
}