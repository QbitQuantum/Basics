static UINT doNetCfgInit(MSIHANDLE hModule, INetCfg **ppnc, BOOL bWrite)
{
    MSIHANDLE hMsg = NULL;
    UINT uErr = ERROR_GEN_FAILURE;
    int MsgResult;
    int cRetries = 0;

    do
    {
        LPWSTR lpszLockedBy;
        HRESULT hr = VBoxNetCfgWinQueryINetCfg(ppnc, bWrite, VBOX_NETCFG_APP_NAME, 10000, &lpszLockedBy);
        if (hr != NETCFG_E_NO_WRITE_LOCK)
        {
            if (FAILED(hr))
                logStringW(hModule, L"doNetCfgInit: VBoxNetCfgWinQueryINetCfg failed, error = 0x%x", hr);
            uErr = errorConvertFromHResult(hModule, hr);
            break;
        }

        /* hr == NETCFG_E_NO_WRITE_LOCK */

        if (!lpszLockedBy)
        {
            logStringW(hModule, L"doNetCfgInit: lpszLockedBy == NULL, breaking");
            break;
        }

        /* on vista the 6to4svc.dll periodically maintains the lock for some reason,
         * if this is the case, increase the wait period by retrying multiple times
         * NOTE: we could alternatively increase the wait timeout,
         * however it seems unneeded for most cases, e.g. in case some network connection property
         * dialog is opened, it would be better to post a notification to the user as soon as possible
         * rather than waiting for a longer period of time before displaying it */
        if (   cRetries < VBOX_NETCFG_MAX_RETRIES
            && !wcscmp(lpszLockedBy, L"6to4svc.dll"))
        {
            cRetries++;
            logStringW(hModule, L"doNetCfgInit: lpszLockedBy is 6to4svc.dll, retrying %d out of %d", cRetries, VBOX_NETCFG_MAX_RETRIES);
            MsgResult = IDRETRY;
        }
        else
        {
            if (!hMsg)
            {
                hMsg = createNetCfgLockedMsgRecord(hModule);
                if (!hMsg)
                {
                    logStringW(hModule, L"doNetCfgInit: Failed to create a message record, breaking");
                    CoTaskMemFree(lpszLockedBy);
                    break;
                }
            }

            UINT rTmp = MsiRecordSetStringW(hMsg, 2, lpszLockedBy);
            NonStandardAssert(rTmp == ERROR_SUCCESS);
            if (rTmp != ERROR_SUCCESS)
            {
                logStringW(hModule, L"doNetCfgInit: MsiRecordSetStringW failed, error = 0x%x", rTmp);
                CoTaskMemFree(lpszLockedBy);
                break;
            }

            MsgResult = MsiProcessMessage(hModule, (INSTALLMESSAGE)(INSTALLMESSAGE_USER | MB_RETRYCANCEL), hMsg);
            NonStandardAssert(MsgResult == IDRETRY || MsgResult == IDCANCEL);
            logStringW(hModule, L"doNetCfgInit: MsiProcessMessage returned (0x%x)", MsgResult);
        }
        CoTaskMemFree(lpszLockedBy);
    } while(MsgResult == IDRETRY);

    if (hMsg)
        MsiCloseHandle(hMsg);

    return uErr;
}