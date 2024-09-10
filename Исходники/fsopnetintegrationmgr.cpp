BOOL fsOpNetIntegrationMgr::IsNetscapePluginInstalled(BOOL bQueryPluginDirIfUnknown)
{
	if (m_strNetPath == "")
	{
		Initialize ();
		if (m_strNetPath.GetLength ())
			return IsNetscapePluginInstalled (bQueryPluginDirIfUnknown);

		if (bQueryPluginDirIfUnknown == FALSE)
			return FALSE;

		if (MessageBox (NULL, LS (L_CANTFINDNETSCAPEDIR), vmsFdmAppMgr::getAppName (), MB_ICONEXCLAMATION|MB_YESNO) == IDNO)
			return FALSE;

		CFolderBrowser *fb = CFolderBrowser::Create (LS (L_CHOOSEOUTFOLDER), NULL, NULL, NULL);
		if (fb == NULL)
			return FALSE;

		m_strNetPath = fb->GetPath ();
		if (m_strNetPath [m_strNetPath.GetLength () - 1] != '\\' || m_strNetPath [m_strNetPath.GetLength () - 1] != '/')
			m_strNetPath += '\\';
		if (strnicmp (LPCSTR (m_strNetPath)  + m_strNetPath.GetLength () - 8, "Plugins\\", 8))
			m_strNetPath += "Plugins\\";
	}

	CString str = m_strNetPath;
	str += "npfdm.dll";
	if (GetFileAttributes (str) == DWORD (-1))
		return FALSE;
	else
		return TRUE;
}