void CLogin::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	CString name;
	CString password;
	GetDlgItemTextW(IDC_LOGINNANE, name);
	GetDlgItemTextW(IDC_LOGINPASSWORD, password);
	if (name == _T("wangyu")){
		_loginSuccess = true;
		CDialogEx::OnOK();
	}
}