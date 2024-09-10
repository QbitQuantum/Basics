// 开启服务
void CSocketServerDlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	OpenServer();
	CWnd *pWnd = GetDlgItem(IDC_BUTTON_OPEN);
	pWnd->EnableWindow(FALSE);
	pWnd = GetDlgItem(IDC_BUTTON_CLOSE);
	pWnd->EnableWindow(TRUE);

}