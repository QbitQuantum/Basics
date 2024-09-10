void CIniFileProcessor::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	if(m_bInitialized && cx > 0 && cy > 130)
	{
		KillTimer(INVALIDATETIMER);
		int iY_Offset = cy - m_OldRect.bottom;
		int iX_Offset = cx - m_OldRect.right;

		CRect rect;
		CWnd *item;
		item = GetDlgItem(IDC_LIST1);
		item->GetWindowRect(&rect);
		ScreenToClient(&rect);
		item->MoveWindow(rect.left, rect.top,rect.Width() + iX_Offset, 
			rect.Height() + iY_Offset,TRUE);

		item = GetDlgItem(IDOK);
		item->GetWindowRect(&rect);
		ScreenToClient(&rect);
		item->MoveWindow(rect.left,rect.top + iY_Offset,rect.Width(),
			rect.Height(),TRUE);

		item = GetDlgItem(IDCANCEL);
		item->GetWindowRect(&rect);
		ScreenToClient(&rect);
		item->MoveWindow(rect.left,rect.top + iY_Offset,rect.Width(),
			rect.Height(),TRUE);

		item = GetDlgItem(ID_EDIT_TOGGLE);
		item->GetWindowRect(&rect);
		ScreenToClient(&rect);
		item->MoveWindow(rect.left,rect.top + iY_Offset,rect.Width(),
			rect.Height(),TRUE);

		CWnd *resizeWnd = GetDlgItem(AFX_IDW_SIZE_BOX);
		if(resizeWnd)
		{
			CRect rect,rect2;
			resizeWnd->GetWindowRect(&rect);
			GetClientRect(rect2);
			rect2.left = rect2.right - rect.Width();
			rect2.top = rect2.bottom - rect.Height();
			resizeWnd->MoveWindow(&rect2);
		}
		GetClientRect(&m_OldRect);
		//invalidate
		SetTimer(INVALIDATETIMER,100,NULL);
	}
}