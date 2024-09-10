BOOL __stdcall AtlTraceLoadSettingsA(const CHAR *pszFileName, DWORD_PTR dwProcess /* = 0 */)
{
    CHAR szFileName[_MAX_PATH];
    if(!pszFileName)
    {
        CHAR szDrive[_MAX_DRIVE];
        CHAR szDir[_MAX_DIR];
        CHAR szFName[_MAX_FNAME];
        CHAR szExt[_MAX_EXT];

        DWORD dwret = ::GetModuleFileNameA(NULL, szFileName, MAX_PATH);
        if( dwret == 0 || dwret == MAX_PATH )
            return FALSE;
#if _SECURE_ATL
        ATL_CRT_ERRORCHECK(_splitpath_s(szFileName, szDrive, _countof(szDrive), szDir, _countof(szDir), szFName, _countof(szFName), szExt, _countof(szExt)));
        ATL_CRT_ERRORCHECK(strncpy_s(szExt, _MAX_EXT, TRACE_SETTINGS_EXT, sizeof(TRACE_SETTINGS_EXT)));
        ATL_CRT_ERRORCHECK(_makepath_s(szFileName, _MAX_PATH, szDrive, szDir, szFName, szExt));
#else
        _splitpath(szFileName, szDrive, szDir, szFName, szExt);
        strcpy(szExt, ".trc");
        _makepath(szFileName, szDrive, szDir, szFName, szExt);
#endif
        pszFileName = szFileName;
    }

    if(pszFileName)
    {
        if(-1 != GetFileAttributesA(pszFileName))
        {
            // file exists
            CHAR szSection[MAX_PATH], szKey[MAX_PATH], szValue[MAX_PATH];
            CHAR szName[MAX_PATH];
            UINT nModules, nCategories, nStatus, nLevel;
            UINT nModule;
            CAtlTraceProcess *pProcess;
            CAtlTraceModule *pModule;
            CAtlTraceCategory *pCategory;
            CHAR *pszProcess = "Process";
            CHAR cEnabled, cFuncAndCategoryNames, cFileNameAndLineInfo;
            CAtlAllocator *pAllocator = &g_Allocator;

            if (dwProcess)
                pAllocator = reinterpret_cast<CAtlAllocator*>(dwProcess);

            pProcess = pAllocator->GetProcess();
            ATLASSERT(pProcess);
            if(!pProcess)
                return FALSE;

            pProcess->m_bLoaded = true;

            ::GetPrivateProfileStringA(pszProcess, "Info", "", szValue, MAX_PATH, pszFileName);
            szValue[MAX_PATH - 1] = 0;

#if _SECURE_ATL
            if(5 != sscanf_s(szValue, "ModuleCount:%u, Level:%u, Enabled:%c, "
                             "FuncAndCategoryNames:%c, FileNameAndLineNo:%c", &nModules, &pProcess->m_nLevel, &cEnabled, sizeof(cEnabled),
                             &cFuncAndCategoryNames, sizeof(cFuncAndCategoryNames), &cFileNameAndLineInfo, sizeof(cFileNameAndLineInfo)))
#else
            if(5 != sscanf(szValue, "ModuleCount:%u, Level:%u, Enabled:%c, "
                           "FuncAndCategoryNames:%c, FileNameAndLineNo:%c", &nModules, &pProcess->m_nLevel, &cEnabled,
                           &cFuncAndCategoryNames, &cFileNameAndLineInfo))
#endif
            {
                return FALSE;
            }
            pProcess->m_bEnabled = cEnabled != 'f';
            pProcess->m_bFuncAndCategoryNames = cFuncAndCategoryNames != 'f';
            pProcess->m_bFileNameAndLineNo = cFileNameAndLineInfo != 'f';

            for(UINT i = 0; i < nModules; i++)
            {
#if _SECURE_ATL
                if(-1 == sprintf_s(szKey, MAX_PATH, "Module%d", i+1))
                    return FALSE;
#else
                sprintf(szKey, "Module%d", i+1);
#endif
                ::GetPrivateProfileStringA(pszProcess, szKey, "", szSection, MAX_PATH, pszFileName);
                szSection[MAX_PATH -1] = 0;

                ::GetPrivateProfileStringA(szSection, "Name", "", szName, MAX_PATH, pszFileName);
                szName[MAX_PATH -1] = 0;
                if(!pAllocator->FindModule(CA2W(szName), &nModule))
                    continue;

                pModule = pAllocator->GetModule(nModule);
                ATLASSERT(pModule);
                if(!pModule)
                    continue;

                ::GetPrivateProfileStringA(szSection, "Settings", "", szValue, MAX_PATH, pszFileName);
                szValue[MAX_PATH -1] = 0;
#if _SECURE_ATL
                if(3 != sscanf_s(szValue, "CategoryCount:%u, Level:%u, Status:%u", &nCategories, &nLevel, &nStatus))
#else
                if(3 != sscanf(szValue, "CategoryCount:%u, Level:%u, Status:%u", &nCategories, &nLevel, &nStatus))
#endif
                    continue;

                SetSettings(pModule, nLevel, nStatus);

                for(UINT j = 0; j < nCategories; j++)
                {
#if _SECURE_ATL
                    if(-1 == sprintf_s(szKey, MAX_PATH, "Category%d", j+1))
                        return FALSE;
#else
                    sprintf(szKey, "Category%d", j+1);
#endif
                    ::GetPrivateProfileStringA(szSection, szKey, "", szValue, MAX_PATH, pszFileName);
                    szValue[MAX_PATH -1] = 0;
#if _SECURE_ATL
                    if(3 != sscanf_s(szValue, "Level:%u, Status:%u, Name:%s", &nLevel, &nStatus, szName, _countof(szName)))
#else
                    if(3 != sscanf(szValue, "Level:%u, Status:%u, Name:%s", &nLevel, &nStatus, szName))
#endif
                        continue;

                    UINT iCategory = pModule->m_iFirstCategory;
                    while( iCategory != UINT( -1 ) )
                    {
                        pCategory = pAllocator->GetCategory(iCategory);

                        if( lstrcmpA(CW2A(pCategory->Name()), szName) == 0 )
                        {
                            SetSettings(pCategory, nLevel, nStatus);
                        }
                        iCategory = pCategory->m_iNextCategory;
                    }
                }
            }
            NotifyTool();
        }
    }
    return TRUE;
}