void CDLgBarH::SetViewTimeGlub()
{
	HideShowTimeDeepnessButtons(true);

	int style = gflgViewTimeGlub ? SW_SHOW : SW_HIDE;
	CWnd* w = &m_wndDialogBarDB;
	w->GetDlgItem(IDC_STATIC_R)->ShowWindow(style);
	w->GetDlgItem(IDC_RADIO_SELCT_TIMEGLUB2)->ShowWindow(style);
	w->GetDlgItem(IDC_EDIT_START_GLUB)->ShowWindow(style);
	w->GetDlgItem(IDC_STATIC_START_GLUB)->ShowWindow(style);
	w->GetDlgItem(IDC_EDIT_LEN_GLUB)->ShowWindow(style);
	w->GetDlgItem(IDC_STATIC_MONTH2)->ShowWindow(style);
}