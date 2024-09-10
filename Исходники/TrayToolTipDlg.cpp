void TrayToolTipDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	//TRACEST(_T("TrayToolTipDlg::OnLButtonDown"));
	//SetRealTransparency(0);
	//Hide();
	CWnd* wnd = AfxGetMainWnd();
	if (wnd->IsWindowVisible() == FALSE)
		wnd->SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
	CWnd::OnLButtonDown(nFlags, point);
}