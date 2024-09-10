void ClientConnection::ProcessLocalClipboardChange()
{
	vnclog.Print(2, _T("Clipboard changed\n"));
	
	HWND hOwner = GetClipboardOwner();

	//adzm 2010-05-11 - Ignore clipboard while initializing (copying a password, for example, will end up sending a packet and causing a failure)
	if (!m_running)
	{
		vnclog.Print(2, _T("Ignore Clipboard while initializing!\n"));
		//m_initialClipboardSeen = true;
	}
	else if (m_settingClipboardViewer)
	{
		vnclog.Print(2, _T("Ignore Clipboard while setting viewer!\n"));
		//m_initialClipboardSeen = true;
	}
	else if (m_pFileTransfer->m_fFileTransferRunning ||m_pFileTransfer->m_fFileUploadRunning || m_pFileTransfer->m_fFileDownloadRunning)
	{
		vnclog.Print(2, _T("Ignore Clipboard while FT is buzy!\n"));
		//m_initialClipboardSeen = true;
	}
	else if (hOwner == m_hwndcn) {
		vnclog.Print(2, _T("We changed it - ignore!\n"));
	/*} else if (!m_initialClipboardSeen) {
		vnclog.Print(2, _T("Don't send initial clipboard!\n"));
		m_initialClipboardSeen = true;*/
	} else if (!m_opts.m_DisableClipboard && !m_opts.m_ViewOnly) {
		UpdateRemoteClipboard();
	}
	// Pass the message to the next window in clipboard viewer chain
	if (m_hwndNextViewer != NULL && m_hwndNextViewer != (HWND)INVALID_HANDLE_VALUE) {
		vnclog.Print(6, _T("Passing WM_DRAWCLIPBOARD to 0x%08x\n"), m_hwndNextViewer);
		// use SendNotifyMessage instead of SendMessage so misbehaving or hung applications
		// (like ourself before this) won't cause our thread to hang.
		::SendNotifyMessage(m_hwndNextViewer, WM_DRAWCLIPBOARD , 0,0); 
	} else {
		vnclog.Print(6, _T("No next window in chain; WM_DRAWCLIPBOARD will not be passed\n"), m_hwndNextViewer);
	}
}