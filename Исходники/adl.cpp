HRESULT CAssemblyDownload::GetNextCodebase(BOOL *pbIsFileUrl, LPWSTR wzFilePath,
                                           DWORD cbLen)
{
    HRESULT                                 hr = S_OK;
    LPWSTR                                  wzNextCodebase = NULL;
    DWORD                                   cbCodebase;
    DWORD                                   dwSize;
    BOOL                                    bIsFileUrl = FALSE;

    ASSERT(pbIsFileUrl && wzFilePath);

    *pbIsFileUrl = FALSE;

    for (;;) {

        cbCodebase = 0;
        hr = _pCodebaseList->GetCodebase(0, NULL, &cbCodebase);
        if (hr != HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER)) {
            // could not get codebase
            hr = HRESULT_FROM_WIN32(ERROR_NO_MORE_ITEMS);
            goto Exit;
        }
    
        wzNextCodebase = NEW(WCHAR[cbCodebase]);
        if (!wzNextCodebase) {
            hr = E_OUTOFMEMORY;
            goto Exit;
        }
    
        hr = _pCodebaseList->GetCodebase(0, wzNextCodebase, &cbCodebase);
        if (FAILED(hr)) {
            goto Exit;
        }
    
        hr = _pCodebaseList->RemoveCodebase(0);
        if (FAILED(hr)) {
            goto Exit;
        }
    
        // Check if we are a UNC or file:// URL. If we are, we don't have
        // to do a download, and can call setup right away.
    
        bIsFileUrl = UrlIsW(wzNextCodebase, URLIS_FILEURL);
        if (bIsFileUrl) {
            dwSize = cbLen;
            if (FAILED(PathCreateFromUrlWrap(wzNextCodebase, wzFilePath, &dwSize, 0))) {
                wzFilePath[0] = L'\0';
            }
    
            if (GetFileAttributes(wzFilePath) == (DWORD) -1) {
                // File doesn't exist. Try the next URL.
                DEBUGOUT1(_pdbglog, 0, ID_FUSLOG_ATTEMPT_NEW_DOWNLOAD, wzNextCodebase);

                ReportProgress(0, 0, 0, ASM_NOTIFICATION_ATTEMPT_NEXT_CODEBASE,
                               (LPCWSTR)wzNextCodebase, _hrResult);

                _hrResult = HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);

                SAFEDELETEARRAY(wzNextCodebase);
                continue;
            }
        }
        else {
            hr = HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);
            goto Exit;
        }

        break;
    }

    *pbIsFileUrl = bIsFileUrl;
    PrepNextDownload(wzNextCodebase);

    
Exit:
    SAFEDELETEARRAY(wzNextCodebase);

    return hr;
}