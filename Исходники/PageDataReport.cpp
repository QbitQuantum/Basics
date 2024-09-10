void CPageDataReport::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (nType == SIZE_MINIMIZED)
	{
		return;
	}

	CWnd *pWnd = NULL;
	pWnd = GetWindow(GW_CHILD);
	while (pWnd)
	{
		DWORD dwFlag = SIZE_NO_CHANGE;

		if (pWnd->GetDlgCtrlID() == IDC_LIST_QUERY)
		{
			dwFlag = SIZE_ELASTIC_X_EX | SIZE_ELASTIC_Y_EX;
		}
		else
		{
			dwFlag = SIZE_MOVE_X | SIZE_ELASTIC_X;
		}

		ChangeSize(pWnd,cx,cy,dwFlag);
		pWnd = pWnd->GetWindow(GW_HWNDNEXT);
	}

	GetClientRect(&m_rect);
}