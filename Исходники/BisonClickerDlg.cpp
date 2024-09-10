BOOL CBisonClickerDlg::SetNotifyIcon(HICON NewIcon)
{
	nid.hIcon = NewIcon;
	BOOL Result = Shell_NotifyIconA(NIM_MODIFY, &nid);
	UpdateWindow();
	UpdateData();
	return Result;
}