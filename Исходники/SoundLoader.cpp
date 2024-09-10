DWORD CSoundLoader::OnLoadFile(DWORD size, void *params)
{
	VERIFY_MESSAGE_SIZE(size, sizeof(TCHAR *));
	TCHAR *pFileName = (TCHAR *)params;
	
	StdString fileName = pFileName;

	fileName.tolower();

	DWORD retval = MSG_HANDLED_STOP;
	CHashString hszFileName(fileName);

	set<DWORD>::iterator fileIter = m_FilesLoaded.find(hszFileName.GetUniqueID());
	if (fileIter != m_FilesLoaded.end())
	{
		// this file has already been loaded (hopefully correctly)
		return retval;
	}

	StdString extension, currentToken;
	fileName.GetToken(_T("."), currentToken);

	while (_tcscmp(currentToken, _T("")) != 0)
	{
		extension = currentToken;
		fileName.GetToken(_T("."), currentToken);
	}
	
	static CHashString hszWav(_T("wav"));
	static CHashString hszOgg(_T("ogg"));
	static CHashString hszMP3(_T("mp3"));
	static CHashString hszXmp(_T("xmp"));

	CHashString hszExt(extension);
	DWORD extID = hszExt.GetUniqueID();

	if ((extID == hszWav.GetUniqueID()) ||
		(extID == hszOgg.GetUniqueID()) ||
		(extID == hszMP3.GetUniqueID()))
	{
		bool success = LoadSoundFile(fileName, &hszExt);
		if (!success)
		{
			m_ToolBox->Log(LOGWARNING, _T("Failed to load sound %s\n"), (const TCHAR*)fileName);
			retval = MSG_WARNING;
		}
		else
		{
			m_FilesLoaded.insert(hszFileName.GetUniqueID());
		}
	}

	else if (extID == hszXmp.GetUniqueID())
	{
		bool success = LoadPlaylistFile(fileName);
		if (!success)
		{
			m_ToolBox->Log(LOGWARNING, _T("Failed to load playlist %s\n"), (const TCHAR*)fileName);
			retval = MSG_WARNING;
		}
		else
		{
			m_FilesLoaded.insert(hszFileName.GetUniqueID());
		}
	}

	return retval;
}