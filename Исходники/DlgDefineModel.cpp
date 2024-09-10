void CDlgDefineModel::Enable2D(int bEnable)
{
	CWnd* pWnd;

	pWnd = GetDlgItem(IDC_NY);
	pWnd->EnableWindow(bEnable);

	pWnd = GetDlgItem(IDC_Y0);
	pWnd->EnableWindow(bEnable);

	pWnd = GetDlgItem(IDC_YCS);
	pWnd->EnableWindow(bEnable);
}