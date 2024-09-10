static int VBoxNetFltUninstall()
{
    INetCfg *pnc;
    LPWSTR lpszLockedBy = NULL;
    int r;

    VBoxNetCfgWinSetLogging(winNetCfgLogger);

    HRESULT hr = CoInitialize(NULL);
    if(hr == S_OK)
    {
        int i = 0;
        do
        {
            hr = VBoxNetCfgWinQueryINetCfg(&pnc, TRUE, VBOX_NETCFG_APP_NAME, 10000, &lpszLockedBy);
            if(hr == S_OK)
            {
                hr = VBoxNetCfgWinNetFltUninstall(pnc);
                if(hr != S_OK)
                {
                    wprintf(L"error uninstalling VBoxNetFlt (0x%x)\n", hr);
                    r = 1;
                }
                else
                {
                    wprintf(L"uninstalled successfully\n");
                    r = 0;
                }

                VBoxNetCfgWinReleaseINetCfg(pnc, TRUE);
                break;
            }
            else if(hr == NETCFG_E_NO_WRITE_LOCK && lpszLockedBy)
            {
                if(i < VBOX_NETFLT_RETRIES && !wcscmp(lpszLockedBy, L"6to4svc.dll"))
                {
                    wprintf(L"6to4svc.dll is holding the lock, retrying %d out of %d\n", ++i, VBOX_NETFLT_RETRIES);
                    CoTaskMemFree(lpszLockedBy);
                }
                else
                {
                    wprintf(L"Error: write lock is owned by another application (%s), close the application and retry uninstalling\n", lpszLockedBy);
                    r = 1;
                    CoTaskMemFree(lpszLockedBy);
                    break;
                }
            }
            else
            {
                wprintf(L"Error getting the INetCfg interface (0x%x)\n", hr);
                r = 1;
                break;
            }
        } while(true);

        CoUninitialize();
    }
    else
    {
        wprintf(L"Error initializing COM (0x%x)\n", hr);
        r = 1;
    }

    VBoxNetCfgWinSetLogging(NULL);

    return r;
}