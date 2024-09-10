DWORD CSoundManager::OnRunPlaylist(DWORD size, void *param)
{
	VERIFY_MESSAGE_SIZE(size, sizeof(IHashString*));

	IHashString *fileName = (IHashString*)param;
	IDTOOBJECTMAP::iterator plIter;	

	if (fileName)
	{
		// convert to lowercase hashstring
		StdString szFileName = fileName->GetString();
		szFileName.tolower();
		CHashString tempFileName(szFileName);

		if (m_pCurrentPlaylist)
		{
			m_pCurrentPlaylist->Stop();
		}

		IDTOOBJECTMAP *objMap = GetObjectMap(&m_hsPlaylistTypeName);
		bool found = false;
		if (objMap != NULL)
		{
			plIter = objMap->find(tempFileName.GetUniqueID());

			if (plIter != objMap->end())
			{
				found = true;
			}
		}

		if (!found)
		{

			// not in map... try to load and check again
			LOADFILEEXTPARAMS lfep;
			lfep.fileName = (TCHAR*) tempFileName.GetString();
			lfep.bInternalLoad = true;
			static DWORD msgHash_LoadFileByExtension = CHashString(_T("LoadFileByExtension")).GetUniqueID();
			m_ToolBox->SendMessage(msgHash_LoadFileByExtension, sizeof(LOADFILEEXTPARAMS), &lfep);
			
			objMap = GetObjectMap(&m_hsPlaylistTypeName);
			if (objMap != NULL)
			{
				plIter = objMap->find(tempFileName.GetUniqueID());
				if (plIter != objMap->end())
				{
					found = true;
				}
			}

			if (!found)
			{
				m_ToolBox->Log(LOGWARNING, _T("Sound manager: could not open playlist file %s\n"), tempFileName.GetString());
				return MSG_NOT_HANDLED;
			}
		}
		
		m_pCurrentPlaylist = dynamic_cast<ISoundObject *>(plIter->second);
		if (m_pCurrentPlaylist != NULL)
		{
			m_pCurrentPlaylist->Play();
		}
		else
		{
			m_ToolBox->Log(LOGWARNING, _T("Dynamic cast failed for CMusicPlayList in %s at line %d\n"),
				__FILE__, __LINE__);
			return MSG_NOT_HANDLED;
		}		
	}

	return MSG_HANDLED_STOP;
}