void CBacnetProgramEdit::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	UnregisterHotKey(GetSafeHwnd(),KEY_F2);//注销F2键
	UnregisterHotKey(GetSafeHwnd(),KEY_F3);
	UnregisterHotKey(GetSafeHwnd(),KEY_F7);
	UnregisterHotKey(GetSafeHwnd(),KEY_F6);
	UnregisterHotKey(GetSafeHwnd(),KEY_F8);

	g_hwnd_now = mParent_Hwnd;
	if(m_pragram_dlg_hwnd!=NULL)
		::PostMessage(m_pragram_dlg_hwnd,WM_REFRESH_BAC_PROGRAM_LIST,NULL,NULL);
	CDialogEx::OnClose();
}