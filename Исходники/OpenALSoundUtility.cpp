DWORD COpenALSoundUtility::OnLoadSoundDatabase(DWORD size, void* param)
{
	VERIFY_MESSAGE_SIZE(size, sizeof(IHashString));
	IHashString *dbFileName = (IHashString*) param;

	if ((dbFileName != NULL) && (_tcscmp(dbFileName->GetString(), _T("")) != 0))
	{
		TCHAR *fileName = _tcsdup(dbFileName->GetString());
		LOADFILEEXTPARAMS lfep;
		lfep.fileName = fileName;
		lfep.bInternalLoad = true;

		static DWORD msgLoadFileByExtension = CHashString(_T("LoadFileByExtension")).GetUniqueID();
		DWORD retval = m_ToolBox->SendMessage(msgLoadFileByExtension, sizeof(LOADFILEEXTPARAMS), &lfep);
		free( fileName );
		if (retval == MSG_HANDLED)
		{
			// clear prior sound list - not additive, exclusive!
			m_SoundMap.clear();
			
			CHashString hsSoundDBObject;
			DATABASEINFO dbi;
			dbi.m_FileName = dbFileName;
			static DWORD msgGetDatabase = CHashString(_T("GetDatabase")).GetUniqueID();
			retval = m_ToolBox->SendMessage(msgGetDatabase, sizeof(DATABASEINFO), &dbi);
			if (retval == MSG_HANDLED)
			{
				hsSoundDBObject.Init(dbi.m_DatabaseName->GetString());
				DATABASEATTRIBUTEPARAMS dap;
				CREATEARCHIVE ca;
				static CHashString memType(_T("Memory"));

				ca.mode = STREAM_MODE_WRITE | STREAM_MODE_READ;
				ca.streamData = NULL;
				ca.streamSize = 0;
				ca.streamType = &memType;
				static DWORD msgHash_CreateArchive = CHashString(_T("CreateArchive")).GetUniqueID();
				m_ToolBox->SendMessage(msgHash_CreateArchive, sizeof(CREATEARCHIVE), &ca);

				IArchive *attribArchive = ca.archive;
				if (attribArchive == NULL)
				{
					m_ToolBox->Log(LOGERROR, _T("Sound manager: archive is null; could not get sound attributes!\n\tNo sounds loaded!\n"));
					return MSG_ERROR;
				}

				dap.m_AttributeArchive = attribArchive;

				static DWORD msgGetAttribute = CHashString(_T("GetAttribute")).GetUniqueID();
				static CHashString hsKeyString(_T("KeyString"));
				static CHashString hsFileName(_T("FileName"));
				static CHashString hsGlobalVolume(_T("GlobalVolume"));
				static CHashString hsCachedUncompressed(_T("CacheUncompressed"));

				static CHashString hsDBType(_T("CDefinedDatabase"));
				for (UINT i=0; i<(UINT)dbi.m_nItems; i++)
				{
					// get key string
					attribArchive->SeekTo(0, SEEK_SET);
					dap.m_Index = i;
					dap.m_AttributeName = &hsKeyString;
					retval = m_ToolBox->SendMessage(msgGetAttribute, sizeof(DATABASEATTRIBUTEPARAMS), &dap, &hsSoundDBObject, &hsDBType);
					if (retval != MSG_HANDLED)
					{
						m_ToolBox->Log(LOGERROR, _T("Sound manager: could not get key attribute for row %d; sounds not fully loaded!\n"), i);
						attribArchive->Close();
						return MSG_ERROR;
					}

					CHashString hsKey;
					StdString szKey;
					attribArchive->SetIsWriting(false);
					attribArchive->Read(szKey);
					hsKey = szKey;

					// get filename
					attribArchive->SeekTo(0, SEEK_SET);
					dap.m_AttributeName = &hsFileName;
					retval = m_ToolBox->SendMessage(msgGetAttribute, sizeof(DATABASEATTRIBUTEPARAMS), &dap, &hsSoundDBObject, &hsDBType);
					if (retval != MSG_HANDLED)
					{
						m_ToolBox->Log(LOGERROR, _T("Sound manager: could not get file attribute for row %d; sounds not fully loaded!\n"), i);
						attribArchive->Close();
						return MSG_ERROR;
					}

					CHashString hsFile;
					StdString szFile;
					attribArchive->SetIsWriting(false);
					attribArchive->Read(szFile);
					szFile.tolower();
					hsFile = szFile;

					// get volume
					attribArchive->SeekTo(0, SEEK_SET);
					dap.m_AttributeName = &hsGlobalVolume;
					retval = m_ToolBox->SendMessage(msgGetAttribute, sizeof(DATABASEATTRIBUTEPARAMS), &dap, &hsSoundDBObject, &hsDBType);
					if (retval != MSG_HANDLED)
					{
						m_ToolBox->Log(LOGERROR, _T("Sound manager: could not get volume attribute for row %d; sounds not fully loaded!\n"), i);
						attribArchive->Close();
						return MSG_ERROR;
					}

					float fVolume;
					attribArchive->SetIsWriting(false);
					attribArchive->Read(fVolume);

					// get cached attribute
					attribArchive->SeekTo(0, SEEK_SET);
					dap.m_AttributeName = &hsCachedUncompressed;
					retval = m_ToolBox->SendMessage(msgGetAttribute, sizeof(DATABASEATTRIBUTEPARAMS), &dap, &hsSoundDBObject, &hsDBType);
					if (retval != MSG_HANDLED)
					{
						m_ToolBox->Log(LOGERROR, _T("Sound manager: could not get volume attribute for row %d; sounds not fully loaded!\n"), i);
						attribArchive->Close();
						return MSG_ERROR;
					}

					bool bCachedUncompressed;
					attribArchive->SetIsWriting(false);
					attribArchive->Read(bCachedUncompressed);

					if (_tcscmp(szKey, _T("GlobalSoundVolume")) == 0)
					{
						static DWORD msgSetGlobalSoundVolume = CHashString(_T("SetGlobalSoundVolume")).GetUniqueID();
						m_ToolBox->SendMessage(msgSetGlobalSoundVolume, sizeof(float), &fVolume);						
					}
					else if(_tcscmp(szKey, _T("GlobalMusicVolume")) == 0)
					{
						static DWORD msgSetGlobalMusicVolume = CHashString(_T("SetGlobalMusicVolume")).GetUniqueID();
						m_ToolBox->SendMessage(msgSetGlobalMusicVolume, sizeof(float), &fVolume);
					}
					else
					{					
						// insert into map
						GLOBALSOUNDDATA gsd;
						gsd.dwFileName = hsFile.GetUniqueID();
						gsd.fVolume = fVolume;
						gsd.bCachedUncompressed = bCachedUncompressed;

						m_SoundMap[hsKey.GetUniqueID()] = gsd;
						m_FileToKeyMap[hsFile.GetUniqueID()] = hsKey.GetUniqueID();
					}
				}

				attribArchive->Close();
			}
			else
			{
				m_ToolBox->Log(LOGERROR, _T("Sound manager: could not get database info!\n\tNo sounds loaded!\n"));
				return MSG_ERROR;
			}
		}
		else
		{
			m_ToolBox->Log(LOGERROR, _T("Sound manager: sound database failed to load!\n\tNo sounds loaded!\n"));
			return MSG_ERROR;
		}
	}
	return MSG_HANDLED_STOP;
}