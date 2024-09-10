void CDlgDeviceLedger::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CWnd* pWnd = NULL;
	CRect winrc,tree_rect,button_rect,list_rect;

	int nButtonHeight = 30;
	int nButtonWidth = 100;

	int nButtonListIntval = 10;

	int nListHeight = cy - nButtonHeight - nButtonListIntval;
	int nListWidth = cx;

	GetClientRect(&winrc);

	pWnd = GetDlgItem(IDC_BUTTON_ADD_DEVICE);
	if (pWnd != NULL)
	{
		button_rect.top = winrc.top;
		button_rect.bottom = button_rect.top + nButtonHeight;
		button_rect.left = winrc.left;
		button_rect.right = button_rect.left + nButtonWidth;
		pWnd->MoveWindow(button_rect);
	}

	pWnd = GetDlgItem(IDC_BUTTON_EDIT_DEVICE);
	if (pWnd != NULL)
	{
		button_rect.top = winrc.top;
		button_rect.bottom = button_rect.top + nButtonHeight;
		button_rect.left = button_rect.right;
		button_rect.right = button_rect.left + nButtonWidth;
		pWnd->MoveWindow(button_rect);
	}

	pWnd = GetDlgItem(IDC_BUTTON_DEL_DEVICE);
	if (pWnd != NULL)
	{
		button_rect.top = winrc.top;
		button_rect.bottom = button_rect.top + nButtonHeight;
		button_rect.left = button_rect.right;
		button_rect.right = button_rect.left + nButtonWidth;
		pWnd->MoveWindow(button_rect);
	}

	pWnd = GetDlgItem(IDC_LIST_DEVICE_LEDGER);
	if (pWnd != NULL)
	{
		list_rect.top = button_rect.bottom;//list_rect.top = button_rect.bottom + nButtonListIntval;
		list_rect.bottom = winrc.bottom;
		list_rect.left = winrc.left;
		list_rect.right = list_rect.left + nListWidth;
		pWnd->MoveWindow(list_rect);
	}	
}