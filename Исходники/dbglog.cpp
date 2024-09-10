HRESULT CDebugLog::DumpDebugLog(DWORD dwDetailLvl, HRESULT hrLog)
{
    HRESULT                                    hr = S_OK;
    HANDLE                                     hFile = INVALID_HANDLE_VALUE;
    LISTNODE                                   pos = NULL;
    LPWSTR                                     wzUrlName=NULL;
    CDebugLogElement                          *pLogElem = NULL;
    WCHAR                                      wzFileName[MAX_PATH];
    WCHAR                                      wzSiteName[MAX_PATH];
    WCHAR                                      wzAppLogDir[MAX_PATH];
    LPWSTR                                     wzResourceName = NULL;
    DWORD                                      dwBytes;
    DWORD                                      dwSize;
    CCriticalSection                           cs(&g_csBindLog);
    BOOL                                       bRet;

    if (!g_dwLogFailures && !g_dwForceLog) {
        return S_FALSE;
    }

    hr = cs.Lock();
    if (FAILED(hr)) {
        return hr;
    }

    pos = _listDbgMsg.GetHeadPosition();
    if (!pos) {
        hr = S_FALSE;
        goto Exit;
    }

    wzUrlName = NEW(WCHAR[MAX_URL_LENGTH+1]);
    if (!wzUrlName)
    {
        hr = E_OUTOFMEMORY;
        goto Exit;
    }

    // Build the log entry URL and Wininet cache file
    
    wnsprintfW(wzUrlName, MAX_URL_LENGTH, L"?FusionBindError!exe=%ws!name=%ws", _wzEXEName, _pwzAsmName);

    {
        wnsprintfW(wzAppLogDir, MAX_PATH, L"%ws\\%ws", _szLogPath, _wzEXEName);

        if (GetFileAttributes(wzAppLogDir) == (DWORD) -1) {
            bRet = CreateDirectory(wzAppLogDir, NULL);
            if (!bRet) {
                hr = HRESULT_FROM_WIN32(GetLastError());
                goto Exit;
            }
        }

        if (PathIsURLW(_pwzAsmName)) {
            // This was a where-ref bind. We can't spit out a filename w/
            // the URL of the bind because the URL has invalid filename chars.
            // The best we can do is show that it was a where-ref bind, and
            // give the filename, and maybe the site.

            dwSize = MAX_PATH;
            hr = UrlGetPartW(_pwzAsmName, wzSiteName, &dwSize, URL_PART_HOSTNAME, 0);
            if (FAILED(hr)) {
                goto Exit;
            }

            wzResourceName = PathFindFileName(_pwzAsmName);

            ASSERT(wzResourceName);

            if (!lstrlenW(wzSiteName)) {
                lstrcpyW(wzSiteName, L"LocalMachine");
            }

            wnsprintfW(wzFileName, MAX_PATH, L"%ws\\FusionBindError!exe=%ws!name=WhereRefBind!Host=(%ws)!FileName=(%ws).HTM",
                       wzAppLogDir, _wzEXEName, wzSiteName, wzResourceName);
        }
        else {
            wnsprintfW(wzFileName, MAX_PATH, L"%ws\\FusionBindError!exe=%ws!name=%ws.HTM", wzAppLogDir, _wzEXEName, _pwzAsmName);
        }
    }

    // Create the and write the log file

    hr = CreateLogFile(&hFile, wzFileName, _wzEXEName, hrLog);
    if (FAILED(hr)) {
        goto Exit;
    }

    pos = _listDbgMsg.GetHeadPosition();
    while (pos) {
        pLogElem = _listDbgMsg.GetNext(pos);
        ASSERT(pLogElem);

        if (pLogElem->_dwDetailLvl <= dwDetailLvl) {
            pLogElem->Dump(hFile);
            WriteFile(hFile, DEBUG_LOG_NEW_LINE, lstrlenW(DEBUG_LOG_NEW_LINE) * sizeof(WCHAR),
                      &dwBytes, NULL);
        }
    }

    // Close the log file and commit the wininet cache entry

    hr = CloseLogFile(&hFile);
    if (FAILED(hr)) {
        goto Exit;
    }


Exit:
    cs.Unlock();
    SAFEDELETEARRAY(wzUrlName);

    return hr;
}