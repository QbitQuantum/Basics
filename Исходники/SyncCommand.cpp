bool SyncCommand::Execute()
{
    bool bRet = false;
    CRegString rSyncPath(L"Software\\TortoiseSVN\\SyncPath");
    CTSVNPath syncPath = CTSVNPath(CString(rSyncPath));
    CTSVNPath syncFolder = syncPath;
    CRegDWORD regCount(L"Software\\TortoiseSVN\\SyncCounter");
    CRegDWORD regSyncAuth(L"Software\\TortoiseSVN\\SyncAuth");
    bool bSyncAuth = DWORD(regSyncAuth) != 0;
    if (!cmdLinePath.IsEmpty())
        syncPath = cmdLinePath;
    if (syncPath.IsEmpty() && !parser.HasKey(L"askforpath"))
    {
        return false;
    }
    syncPath.AppendPathString(L"tsvnsync.tsex");

    BOOL bWithLocals = FALSE;
    if (parser.HasKey(L"askforpath"))
    {
        // ask for the path first, then for the password
        // this is used for a manual import/export
        CString path;
        bool bGotPath = FileOpenSave(path, bWithLocals, !!parser.HasKey(L"load"), GetExplorerHWND());
        if (bGotPath)
        {
            syncPath = CTSVNPath(path);
            if (!parser.HasKey(L"load") && syncPath.GetFileExtension().IsEmpty())
                syncPath.AppendRawString(L".tsex");
        }
        else
            return false;
    }


    CSimpleIni iniFile;
    iniFile.SetMultiLine(true);
    SVNAuthData authData;

    CAutoRegKey hMainKey;
    RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\TortoiseSVN", 0, KEY_READ, hMainKey.GetPointer());
    FILETIME filetime = { 0 };
    RegQueryInfoKey(hMainKey, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &filetime);

    bool bCloudIsNewer = false;
    if (!parser.HasKey(L"save"))
    {
        // open the file in read mode
        CAutoFile hFile = CreateFile(syncPath.GetWinPathString(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile.IsValid())
        {
            // load the file
            LARGE_INTEGER fsize = { 0 };
            if (GetFileSizeEx(hFile, &fsize))
            {
                auto filebuf = std::make_unique<char[]>(DWORD(fsize.QuadPart));
                DWORD bytesread = 0;
                if (ReadFile(hFile, filebuf.get(), DWORD(fsize.QuadPart), &bytesread, NULL))
                {
                    // decrypt the file contents
                    std::string encrypted;
                    if (bytesread > 0)
                        encrypted = std::string(filebuf.get(), bytesread);
                    CRegString regPW(L"Software\\TortoiseSVN\\SyncPW");
                    CString password;
                    if (parser.HasKey(L"askforpath") && parser.HasKey(L"load"))
                    {
                        INT_PTR dlgret = 0;
                        bool bPasswordMatches = true;
                        do
                        {
                            bPasswordMatches = true;
                            CPasswordDlg passDlg(CWnd::FromHandle(GetExplorerHWND()));
                            passDlg.m_bForSave = !!parser.HasKey(L"save");
                            dlgret = passDlg.DoModal();
                            password = passDlg.m_sPW1;
                            if ((dlgret == IDOK) && (parser.HasKey(L"load")))
                            {
                                std::string passworda = CUnicodeUtils::StdGetUTF8((LPCWSTR)password);
                                std::string decrypted = CStringUtils::Decrypt(encrypted, passworda);
                                if ((decrypted.size() < 3) || (decrypted.substr(0, 3) != "***"))
                                {
                                    bPasswordMatches = false;
                                }
                            }
                        } while ((dlgret == IDOK) && !bPasswordMatches);
                        if (dlgret != IDOK)
                            return false;
                    }
                    else
                    {
                        auto passwordbuf = CStringUtils::Decrypt(CString(regPW));
                        if (passwordbuf.get())
                        {
                            password = passwordbuf.get();
                        }
                        else
                        {
                            // password does not match or it couldn't be read from
                            // the registry!
                            //
                            TaskDialog(GetExplorerHWND(), AfxGetResourceHandle(), MAKEINTRESOURCE(IDS_APPNAME), MAKEINTRESOURCE(IDS_ERR_ERROROCCURED), MAKEINTRESOURCE(IDS_SYNC_WRONGPASSWORD), TDCBF_OK_BUTTON, TD_ERROR_ICON, NULL);
                            CString sCmd = L" /command:settings /page:21";
                            CAppUtils::RunTortoiseProc(sCmd);
                            return false;
                        }
                    }
                    std::string passworda = CUnicodeUtils::StdGetUTF8((LPCWSTR)password);
                    std::string decrypted = CStringUtils::Decrypt(encrypted, passworda);
                    if (decrypted.size() >= 3)
                    {
                        if (decrypted.substr(0, 3) == "***")
                        {
                            decrypted = decrypted.substr(3);
                            // pass the decrypted data to the ini file
                            iniFile.LoadFile(decrypted.c_str(), decrypted.size());
                            int inicount = _wtoi(iniFile.GetValue(L"sync", L"synccounter", L""));
                            if (inicount != 0)
                            {
                                if (int(DWORD(regCount)) < inicount)
                                {
                                    bCloudIsNewer = true;
                                    regCount = inicount;
                                }
                            }

                            // load the auth data, but do not overwrite already stored auth data!
                            if (bSyncAuth)
                                authData.ImportAuthData(syncFolder.GetWinPathString(), password);
                        }
                        else
                        {
                            CTraceToOutputDebugString::Instance()(_T(__FUNCTION__) L": Error decrypting, password may be wrong\n");
                            return false;
                        }
                    }
                }
            }
        }
        else
        {
            CTraceToOutputDebugString::Instance()(_T(__FUNCTION__) L": Error opening file %s, Error %u\n", syncPath.GetWinPath(), GetLastError());
            auto lasterr = GetLastError();
            if ((lasterr != ERROR_FILE_NOT_FOUND) && (lasterr != ERROR_PATH_NOT_FOUND))
                return false;
        }
    }

    if (parser.HasKey(L"load"))
        bCloudIsNewer = true;
    if (parser.HasKey(L"save"))
        bCloudIsNewer = false;

    bool bHaveChanges = false;

    if (bWithLocals || parser.HasKey(L"local"))
    {
        // remove all blocks that are allowed for local exports
        for (const auto& allow : regBlockLocalArray)
        {
            regBlockArray.erase(std::remove(regBlockArray.begin(), regBlockArray.end(), allow), regBlockArray.end());
        }
    }
    // go through all registry values and update either the registry
    // or the ini file, depending on which is newer
    for (const auto& regname : regUseArray)
    {
        bool bChanges = HandleRegistryKey(regname, iniFile, bCloudIsNewer);
        bHaveChanges = bHaveChanges || bChanges;
    }
    if (bWithLocals || parser.HasKey(L"local"))
    {
        for (const auto& regname : regUseLocalArray)
        {
            bool bChanges = HandleRegistryKey(regname, iniFile, bCloudIsNewer);
            bHaveChanges = bHaveChanges || bChanges;
        }
    }

    if (bCloudIsNewer)
    {
        CString regpath = L"Software\\";

        CSimpleIni::TNamesDepend keys;
        iniFile.GetAllKeys(L"registry_dword", keys);
        for (const auto& k : keys)
        {
            CRegDWORD reg(regpath + k);
            reg = _wtol(iniFile.GetValue(L"registry_dword", k, L""));
        }

        keys.clear();
        iniFile.GetAllKeys(L"registry_qword", keys);
        for (const auto& k : keys)
        {
            CRegQWORD reg(regpath + k);
            reg = _wtoi64(iniFile.GetValue(L"registry_qword", k, L""));
        }

        keys.clear();
        iniFile.GetAllKeys(L"registry_string", keys);
        for (const auto& k : keys)
        {
            CRegString reg(regpath + k);
            reg = CString(iniFile.GetValue(L"registry_string", k, L""));
        }
    }
    {
        // sync project monitor settings
        CString sDataFilePath = CPathUtils::GetAppDataDirectory();
        sDataFilePath += L"\\MonitoringData.ini";
        CSimpleIni monitorIni;
        monitorIni.SetMultiLine(true);
        if (bCloudIsNewer)
        {
            CSimpleIni origMonitorIni;
            origMonitorIni.SetMultiLine(true);
            origMonitorIni.LoadFile(sDataFilePath);

            CSimpleIni::TNamesDepend keys;
            iniFile.GetAllKeys(L"ini_monitor", keys);
            for (const auto& k : keys)
            {
                CString sKey = k;
                CString sSection = sKey.Left(sKey.Find('.'));
                sKey = sKey.Mid(sKey.Find('.') + 1);
                if (sKey.CompareNoCase(L"name") == 0)
                {
                    // make sure the non-synced values are still used
                    monitorIni.SetValue(sSection, L"lastchecked", origMonitorIni.GetValue(sSection, L"lastchecked", L"0"));
                    monitorIni.SetValue(sSection, L"lastcheckedrobots", origMonitorIni.GetValue(sSection, L"lastcheckedrobots", L"0"));
                    monitorIni.SetValue(sSection, L"lastHEAD", origMonitorIni.GetValue(sSection, L"lastHEAD", L"0"));
                    monitorIni.SetValue(sSection, L"UnreadItems", origMonitorIni.GetValue(sSection, L"UnreadItems", L"0"));
                    monitorIni.SetValue(sSection, L"unreadFirst", origMonitorIni.GetValue(sSection, L"unreadFirst", L"0"));
                    monitorIni.SetValue(sSection, L"WCPathOrUrl", origMonitorIni.GetValue(sSection, L"WCPathOrUrl", L""));
                }
                CString sValue = CString(iniFile.GetValue(L"ini_monitor", k, L""));
                if ((sKey.Compare(L"username") == 0) || (sKey.Compare(L"password") == 0))
                {
                    sValue = CStringUtils::Encrypt(sValue);
                }
                monitorIni.SetValue(sSection, sKey, sValue);
            }
            FILE * pFile = NULL;
            errno_t err = 0;
            int retrycount = 5;
            CString sTempfile = CTempFiles::Instance().GetTempFilePathString();
            do
            {
                err = _tfopen_s(&pFile, sTempfile, L"wb");
                if ((err == 0) && pFile)
                {
                    monitorIni.SaveFile(pFile);
                    err = fclose(pFile);
                }
                if (err)
                {
                    CTraceToOutputDebugString::Instance()(_T(__FUNCTION__) L": Error saving %s, retrycount %d\n", (LPCWSTR)sTempfile, retrycount);
                    Sleep(500);
                }
            } while (err && retrycount--);
            if (err == 0)
            {
                if (!CopyFile(sTempfile, sDataFilePath, FALSE))
                    CTraceToOutputDebugString::Instance()(_T(__FUNCTION__) L": Error copying %s to %s, Error %u\n", (LPCWSTR)sTempfile, (LPCWSTR)sDataFilePath, GetLastError());
                else
                {
                    // now send a message to a possible running monitor to force it
                    // to reload the ini file. Otherwise it would overwrite the ini
                    // file without using the synced data!
                    HWND hWnd = FindWindow(NULL, CString(MAKEINTRESOURCE(IDS_MONITOR_DLGTITLE)));
                    if (hWnd)
                    {
                        UINT TSVN_COMMITMONITOR_RELOADINI = RegisterWindowMessage(L"TSVNCommitMonitor_ReloadIni");
                        PostMessage(hWnd, TSVN_COMMITMONITOR_RELOADINI, 0, 0);
                    }
                }
            }
        }
        else
        {
            CSimpleIni::TNamesDepend mitems;
            if (PathFileExists(sDataFilePath))
            {
                int retrycount = 5;
                SI_Error err = SI_OK;
                do
                {
                    err = monitorIni.LoadFile(sDataFilePath);
                    if (err == SI_FILE)
                    {
                        CTraceToOutputDebugString::Instance()(_T(__FUNCTION__) L": Error loading %s, retrycount %d\n", (LPCWSTR)sDataFilePath, retrycount);
                        Sleep(500);
                    }
                } while ((err == SI_FILE) && retrycount--);

                if (err == SI_FILE)
                {
                    return false;
                }
                monitorIni.GetAllSections(mitems);
            }

            for (const auto& mitem : mitems)
            {
                CString sSection = mitem;
                CString Name = monitorIni.GetValue(mitem, L"Name", L"");
                if (!Name.IsEmpty())
                {
                    CString newval = monitorIni.GetValue(mitem, L"WCPathOrUrl", L"");
                    iniFile.SetValue(L"ini_monitor", sSection + L".Name", Name);
                    CString oldval = iniFile.GetValue(L"ini_monitor", sSection + L".WCPathOrUrl", L"");
                    bHaveChanges |= ((newval != oldval) && (!oldval.IsEmpty()));
                    // only save monitored working copies if local settings are included, or
                    // if the monitored path is an url.
                    // Don't save paths to working copies for non-local stores
                    if (bWithLocals || newval.IsEmpty() || !PathIsDirectory(newval))
                        iniFile.SetValue(L"ini_monitor", sSection + L".WCPathOrUrl", newval);

                    newval = monitorIni.GetValue(mitem, L"interval", L"5");
                    oldval = iniFile.GetValue(L"ini_monitor", sSection + L".interval", L"0");
                    bHaveChanges |= newval != oldval;
                    iniFile.SetValue(L"ini_monitor", sSection + L".interval", newval);

                    newval = monitorIni.GetValue(mitem, L"minminutesinterval", L"0");
                    oldval = iniFile.GetValue(L"ini_monitor", sSection + L".minminutesinterval", L"0");
                    bHaveChanges |= newval != oldval;
                    iniFile.SetValue(L"ini_monitor", sSection + L".minminutesinterval", newval);

                    newval = CStringUtils::Decrypt(monitorIni.GetValue(mitem, L"username", L"")).get();
                    oldval = iniFile.GetValue(L"ini_monitor", sSection + L".username", L"");
                    bHaveChanges |= newval != oldval;
                    iniFile.SetValue(L"ini_monitor", sSection + L".username", newval);

                    newval = CStringUtils::Decrypt(monitorIni.GetValue(mitem, L"password", L"")).get();
                    oldval = iniFile.GetValue(L"ini_monitor", sSection + L".password", L"");
                    bHaveChanges |= newval != oldval;
                    iniFile.SetValue(L"ini_monitor", sSection + L".password", newval);

                    newval = monitorIni.GetValue(mitem, L"MsgRegex", L"");
                    oldval = iniFile.GetValue(L"ini_monitor", sSection + L".MsgRegex", L"");
                    bHaveChanges |= newval != oldval;
                    iniFile.SetValue(L"ini_monitor", sSection + L".MsgRegex", newval);

                    newval = monitorIni.GetValue(mitem, L"ignoreauthors", L"");
                    oldval = iniFile.GetValue(L"ini_monitor", sSection + L".ignoreauthors", L"");
                    bHaveChanges |= newval != oldval;
                    iniFile.SetValue(L"ini_monitor", sSection + L".ignoreauthors", newval);

                    newval = monitorIni.GetValue(mitem, L"parentTreePath", L"");
                    oldval = iniFile.GetValue(L"ini_monitor", sSection + L".parentTreePath", L"");
                    bHaveChanges |= newval != oldval;
                    iniFile.SetValue(L"ini_monitor", sSection + L".parentTreePath", newval);

                    newval = monitorIni.GetValue(mitem, L"uuid", L"");
                    oldval = iniFile.GetValue(L"ini_monitor", sSection + L".uuid", L"");
                    bHaveChanges |= newval != oldval;
                    iniFile.SetValue(L"ini_monitor", sSection + L".uuid", newval);

                    newval = monitorIni.GetValue(mitem, L"root", L"");
                    oldval = iniFile.GetValue(L"ini_monitor", sSection + L".root", L"");
                    bHaveChanges |= newval != oldval;
                    iniFile.SetValue(L"ini_monitor", sSection + L".root", newval);

                    ProjectProperties ProjProps;
                    ProjProps.LoadFromIni(monitorIni, sSection);
                    ProjProps.SaveToIni(iniFile, L"ini_monitor", sSection + L".pp_");
                }
                else if (sSection.CompareNoCase(L"global") == 0)
                {
                    CString newval = monitorIni.GetValue(mitem, L"PlaySound", L"1");
                    CString oldval = iniFile.GetValue(L"ini_monitor", sSection + L".PlaySound", L"1");
                    bHaveChanges |= newval != oldval;
                    iniFile.SetValue(L"ini_monitor", sSection + L".PlaySound", newval);

                    newval = monitorIni.GetValue(mitem, L"ShowNotifications", L"1");
                    oldval = iniFile.GetValue(L"ini_monitor", sSection + L".ShowNotifications", L"1");
                    bHaveChanges |= newval != oldval;
                    iniFile.SetValue(L"ini_monitor", sSection + L".ShowNotifications", newval);
                }
            }
        }
    }

    {
        // sync TortoiseMerge regex filters
        CSimpleIni regexIni;
        regexIni.SetMultiLine(true);
        CString sDataFilePath = CPathUtils::GetAppDataDirectory();
        sDataFilePath += L"\\regexfilters.ini";

        if (bCloudIsNewer)
        {
            CSimpleIni origRegexIni;

            if (PathFileExists(sDataFilePath))
            {
                int retrycount = 5;
                SI_Error err = SI_OK;
                do
                {
                    err = origRegexIni.LoadFile(sDataFilePath);
                    if (err == SI_FILE)
                    {
                        CTraceToOutputDebugString::Instance()(_T(__FUNCTION__) L": Error loading %s, retrycount %d\n", (LPCWSTR)sDataFilePath, retrycount);
                        Sleep(500);
                    }
                } while ((err == SI_FILE) && retrycount--);

                if (err == SI_FILE)
                {
                    return false;
                }
            }

            CSimpleIni::TNamesDepend keys;
            iniFile.GetAllKeys(L"ini_tmergeregex", keys);
            for (const auto& k : keys)
            {
                CString sKey = k;
                CString sSection = sKey.Left(sKey.Find('.'));
                sKey = sKey.Mid(sKey.Find('.') + 1);
                CString sValue = CString(iniFile.GetValue(L"ini_tmergeregex", k, L""));
                regexIni.SetValue(sSection, sKey, sValue);
            }
            FILE * pFile = NULL;
            errno_t err = 0;
            int retrycount = 5;
            CString sTempfile = CTempFiles::Instance().GetTempFilePathString();
            do
            {
                err = _tfopen_s(&pFile, sTempfile, L"wb");
                if ((err == 0) && pFile)
                {
                    regexIni.SaveFile(pFile);
                    err = fclose(pFile);
                }
                if (err)
                {
                    CTraceToOutputDebugString::Instance()(_T(__FUNCTION__) L": Error saving %s, retrycount %d\n", (LPCWSTR)sTempfile, retrycount);
                    Sleep(500);
                }
            } while (err && retrycount--);
            if (err == 0)
            {
                if (!CopyFile(sTempfile, sDataFilePath, FALSE))
                    CTraceToOutputDebugString::Instance()(_T(__FUNCTION__) L": Error copying %s to %s, Error: %u\n", (LPCWSTR)sTempfile, (LPCWSTR)sDataFilePath, GetLastError());
            }
        }
        else
        {
            if (PathFileExists(sDataFilePath))
            {
                int retrycount = 5;
                SI_Error err = SI_OK;
                do
                {
                    err = regexIni.LoadFile(sDataFilePath);
                    if (err == SI_FILE)
                    {
                        CTraceToOutputDebugString::Instance()(_T(__FUNCTION__) L": Error loading %s, retrycount %d\n", (LPCWSTR)sDataFilePath, retrycount);
                        Sleep(500);
                    }
                } while ((err == SI_FILE) && retrycount--);

                if (err == SI_FILE)
                {
                    return false;
                }
            }

            CSimpleIni::TNamesDepend mitems;
            regexIni.GetAllSections(mitems);
            for (const auto& mitem : mitems)
            {
                CString sSection = mitem;

                CString newval = regexIni.GetValue(mitem, L"regex", L"");
                CString oldval = iniFile.GetValue(L"ini_tmergeregex", sSection + L".regex", L"");
                bHaveChanges |= newval != oldval;
                iniFile.SetValue(L"ini_tmergeregex", sSection + L".regex", newval);

                newval = regexIni.GetValue(mitem, L"replace", L"5");
                oldval = iniFile.GetValue(L"ini_tmergeregex", sSection + L".replace", L"0");
                bHaveChanges |= newval != oldval;
                iniFile.SetValue(L"ini_tmergeregex", sSection + L".replace", newval);
            }
        }
    }


    if (bHaveChanges)
    {
        iniFile.SetValue(L"sync", L"version", TSVN_SYNC_VERSION_STR);
        DWORD count = regCount;
        ++count;
        regCount = count;
        CString tmp;
        tmp.Format(L"%lu", count);
        iniFile.SetValue(L"sync", L"synccounter", tmp);

        // save the ini file
        std::string iniData;
        iniFile.SaveString(iniData);
        iniData = "***" + iniData;
        // encrypt the string

        CString password;
        if (parser.HasKey(L"askforpath"))
        {
            CPasswordDlg passDlg(CWnd::FromHandle(GetExplorerHWND()));
            passDlg.m_bForSave = true;
            if (passDlg.DoModal() != IDOK)
                return false;
            password = passDlg.m_sPW1;
        }
        else
        {
            CRegString regPW(L"Software\\TortoiseSVN\\SyncPW");
            auto passwordbuf = CStringUtils::Decrypt(CString(regPW));
            if (passwordbuf.get())
            {
                password = passwordbuf.get();
            }
        }

        std::string passworda = CUnicodeUtils::StdGetUTF8((LPCWSTR)password);

        std::string encrypted = CStringUtils::Encrypt(iniData, passworda);
        CPathUtils::MakeSureDirectoryPathExists(syncPath.GetContainingDirectory().GetWinPathString());
        CString sTempfile = CTempFiles::Instance().GetTempFilePathString();
        CAutoFile hFile = CreateFile(sTempfile, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile.IsValid())
        {
            DWORD written = 0;
            if (WriteFile(hFile, encrypted.c_str(), DWORD(encrypted.size()), &written, NULL))
            {
                if (hFile.CloseHandle())
                {
                    if (!CopyFile(sTempfile, syncPath.GetWinPath(), FALSE))
                    {
                        CTraceToOutputDebugString::Instance()(_T(__FUNCTION__) L": Error copying %s to %s, Error: %u\n", (LPCWSTR)sTempfile, syncPath.GetWinPath(), GetLastError());
                    }
                    else
                        bRet = true;
                }
                else
                    CTraceToOutputDebugString::Instance()(_T(__FUNCTION__) L": Error closing file %s, Error: %u\n", (LPCWSTR)sTempfile, GetLastError());
            }
            else
                CTraceToOutputDebugString::Instance()(_T(__FUNCTION__) L": Error writing to file %s, Error: %u\n", (LPCWSTR)sTempfile, GetLastError());
        }
        else
            CTraceToOutputDebugString::Instance()(_T(__FUNCTION__) L": Error creating file %s for writing, Error: %u\n", (LPCWSTR)sTempfile, GetLastError());

        if (bSyncAuth)
        {
            // now save all auth data
            CPathUtils::MakeSureDirectoryPathExists(syncFolder.GetWinPathString() + L"\\auth");
            CPathUtils::MakeSureDirectoryPathExists(syncFolder.GetWinPathString() + L"\\auth\\svn.simple");
            CPathUtils::MakeSureDirectoryPathExists(syncFolder.GetWinPathString() + L"\\auth\\svn.ssl.client-passphrase");
            CPathUtils::MakeSureDirectoryPathExists(syncFolder.GetWinPathString() + L"\\auth\\svn.ssl.server");
            CPathUtils::MakeSureDirectoryPathExists(syncFolder.GetWinPathString() + L"\\auth\\svn.username");
            authData.ExportAuthData(syncFolder.GetWinPathString(), password);
        }
    }


    return bRet;
}