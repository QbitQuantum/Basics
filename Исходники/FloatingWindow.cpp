LRESULT CFloatingWindow::OnHotKey(int HotKeyID, UINT flags, UINT vk)
{
	if (HotKeyID < 0 || HotKeyID > int(m_hotkeys.size()) - 1)
		return 0;
	if (m_bIsUploading)
		return 0;

	if (m_hotkeys[HotKeyID].func == _T("windowscreenshot"))
	{
		pWizardDlg->executeFunc(_T("windowscreenshot,1"));
	}
	else
	{
		m_bFromHotkey = true;
		SetActiveWindow();
		SetForegroundWindow(m_hWnd);
		SendMessage(WM_COMMAND, MAKEWPARAM(m_hotkeys[HotKeyID].commandId, 0));
		m_bFromHotkey = false;
	}
	return 0;
}