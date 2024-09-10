void CDlg5::HideMainWnd()
{
	if (GetPrivateProfileIntA(_T("System"),_T("BeginHide"),0,CAfx::filepath))
	{
		AfxGetMainWnd()->ShowWindow(SW_HIDE);
	}
}