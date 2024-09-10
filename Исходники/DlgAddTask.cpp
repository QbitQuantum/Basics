void CDlgAddTask::PopupDlg(BOOL bBlank)
{
	if (IsDlgPopedUp())
		return;

	m_uAddState = 2; // Added by Soar Chin 09/06/2007
	Create(CDlgAddTask::IDD);
	ShowWindow(SW_SHOW);

	SetForegroundWindow();
	SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0,SWP_NOMOVE|SWP_NOSIZE);
	SetActiveWindow();
	SetFocus();

	if (!bBlank)
		GetDlgItem(IDOK)->SetFocus();
}