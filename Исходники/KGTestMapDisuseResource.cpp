int KGTestMapDisuseResource::CheckDisuseResource()
{
	int nResult  = false;
	int nRetCode = false;
	set<string>::iterator iterUsed;
	string strUsedResName;
	string strSourceResName;
	char szExt[MAX_PATH] = {0};

	printf("Checking Disuse Resource...\n");
	KGLogPrintf(KGLOG_INFO, "Checking Disuse Resource");
	for (iterUsed = m_setUsedRes.begin(); iterUsed != m_setUsedRes.end(); ++iterUsed)
	{
 		strUsedResName = *iterUsed;
 		nRetCode = _mbslwr_s((unsigned char*)strUsedResName.c_str(), strUsedResName.length() + 1);
 		KGLOG_PROCESS_ERROR(nRetCode == 0);

		nRetCode = _splitpath_s(strUsedResName.c_str(), NULL, 0, NULL , 0, NULL, 0, szExt, sizeof(szExt));
		KGLOG_PROCESS_ERROR(nRetCode == 0);
		for (UINT i = 0; i < m_mapSourceRes[szExt].size(); i++)
		{
			strSourceResName = m_mapSourceRes[szExt][i];
			if (strSourceResName.empty())
			{
				continue;
			}
			nRetCode = _mbslwr_s((unsigned char*)strSourceResName.c_str(), strSourceResName.length() + 1);
			KGLOG_PROCESS_ERROR(nRetCode == 0);

			nRetCode = (int)strSourceResName.find(strUsedResName);
			if (nRetCode != -1)
			{
				if (strncmp(szExt, ".mesh", sizeof(".mesh")) == 0 ||
					strncmp(szExt, ".mtl", sizeof(".mtl")) == 0)
				{				
					char szLODRes[MAX_PATH] = {0};
					char szDrive[MAX_PATH]	= {0};
					char szDir[MAX_PATH]	= {0};
					char szName[MAX_PATH]	= {0};
					char szExt[MAX_PATH]	= {0};
					string strSourceLODRes;

					nRetCode = _splitpath_s(
						strUsedResName.c_str(),
						szDrive, sizeof(szDrive),
						szDir, sizeof(szDir),
						szName, sizeof(szName),
						szExt, sizeof(szExt));
					KGLOG_PROCESS_ERROR(nRetCode == 0);

					nRetCode = _snprintf_s(
						szLODRes,
						sizeof(szLODRes),
						sizeof(szLODRes) - 1,
						"%s%s%s_l%s",
						szDrive, szDir, szName, szExt);
					KGLOG_PROCESS_ERROR(nRetCode > 0);

					for (size_t i = 0; i < m_vecLODRes.size(); i++)
					{
						strSourceLODRes = m_vecLODRes[i];
						nRetCode = _mbslwr_s((unsigned char*)strSourceLODRes.c_str(), strSourceLODRes.length() + 1);
						KGLOG_PROCESS_ERROR(nRetCode == 0);
						nRetCode = (int)strSourceLODRes.find(szLODRes);
						if (nRetCode != -1)
						{
							m_vecLODRes[i].clear();
							break;
						}
					}
				}

				(*iterUsed).clear();
				m_mapSourceRes[szExt][i].clear();
				break;
			}
		}
	}

	nResult = true;
Exit0:
	return nResult;
}