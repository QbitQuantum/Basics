BOOL CMailMsg::MAPIInitialize()
{
	// Determine if there is default email program

	CString sMailClientName;
	if(!DetectMailClient(sMailClientName))
	{
		m_sErrorMsg = _T("Error detecting E-mail client");
		return FALSE;
	}
	else
	{
		m_sErrorMsg = _T("Detected E-mail client ") + sMailClientName;
	}

	// Load MAPI.dll

	m_hMapi = AtlLoadSystemLibraryUsingFullPath(_T("mapi32.dll"));
	if (!m_hMapi)
	{
		m_sErrorMsg = _T("Error loading mapi32.dll");
		return FALSE;
	}

	m_lpMapiSendMail = (LPMAPISENDMAIL)::GetProcAddress(m_hMapi, "MAPISendMail");

	m_bReady = !!m_lpMapiSendMail;

	if(!m_bReady)
	{
		m_sErrorMsg = _T("Not found required function entries in mapi32.dll");
	}

	return m_bReady;
}