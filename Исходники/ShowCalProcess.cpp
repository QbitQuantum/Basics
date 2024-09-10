void CShowCalProcess::OnBnClickedButton1()
{
	TerminateThread(handle, 1);
	OnCancel();
	// TODO: 在此添加控件通知处理程序代码
}