void CDlgBlockAnalysis::SetSize()
{
	CRect rcClient, rcTab, rcList, rcCancel;
	CRect rcButton;

	GetClientRect(&rcClient);

	CWnd *pWnd = GetDlgItem(IDC_SAVEAS2);
	if( pWnd != NULL )
	{
		pWnd->GetWindowRect(&rcButton);
	}
	else
	{
		return;
	}

	rcClient.left += HS_TAB_X;
	rcClient.right -= HS_TAB_X;

	rcTab = rcClient;
	rcTab.top += HS_TAB_Y;
	rcTab.bottom = rcTab.top + HS_LIST_Y;
	m_Tab_Ctrl.MoveWindow(rcTab);

	rcList = rcClient;
	rcList.top = rcTab.bottom + HS_BORDER_H;
	rcList.bottom -= (HS_BORDER_H * 2 + rcButton.Height());
	m_List_Ctrl.MoveWindow(&rcList);

	rcClient.top = rcList.bottom + HS_BORDER_H;
	rcClient.bottom = rcClient.top + rcButton.Height();

	rcCancel = rcClient;
	rcCancel.left = rcCancel.right - rcButton.Width();
	pWnd->MoveWindow(&rcCancel);

	rcClient.right = rcCancel.left - 2*HS_BORDER_W;
	rcClient.left = rcClient.right - rcButton.Width();
	pWnd = GetDlgItem(IDC_SAVEAS);
	pWnd->MoveWindow(&rcClient);

	rcCancel.right = rcClient.left - HS_BORDER_W;
	rcCancel.left = rcCancel.right - rcButton.Width();
	m_add.MoveWindow(&rcCancel);

	rcClient.right = rcCancel.left - HS_BORDER_W;
	rcClient.left = rcClient.right - rcButton.Width();
	pWnd = GetDlgItem(IDC_SAVEAS);
	m_begin.MoveWindow(&rcClient);
}