void CXfilterDlg::OnMain() 
{
	CMainDlg *dlg = new CMainDlg;
	dlg->Create(IDD_MAIN, this);
	dlg->ShowWindow(SW_SHOW);
	dlg->UpdateWindow();
//	dlg.DoModal();
}