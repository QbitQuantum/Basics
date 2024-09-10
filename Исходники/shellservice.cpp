HRESULT InitShellServices(HDPA * phdpa)
{
    IOleCommandTarget * pOct;
    HKEY    hkey;
    CLSID   clsid;
    WCHAR   name[MAX_PATH];
    WCHAR   value[MAX_PATH];
    DWORD   type;
    LONG    ret;
    HDPA    hdpa;
    HRESULT hr = S_OK;
    int     count = 0;

    *phdpa = NULL;

    TRACE("Enumerating Shell Service Ojbect GUIDs...\n");

    if (RegOpenKey(HKEY_LOCAL_MACHINE,
        L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ShellServiceObjectDelayLoad",
        &hkey))
    {
        ERR("RegOpenKey failed.\n");
        return HRESULT_FROM_WIN32(GetLastError());
    }

    hdpa = DPA_Create(5);

    /* Enumerate */
    do
    {
        DWORD   name_len = MAX_PATH;
        DWORD   value_len = sizeof(value); /* byte count! */

        ret = RegEnumValueW(hkey, count, name, &name_len, 0, &type, (LPBYTE) &value, &value_len);
        if (ret)
            break;

        if (type != REG_SZ)
        {
            WARN("Value type was not REG_SZ.\n");
            continue;
        }

        hr = CLSIDFromString(value, &clsid);
        if (FAILED_UNEXPECTEDLY(hr))
        {
            ERR("CLSIDFromString failed %08x.\n", hr);
            goto cleanup;
        }

        hr = CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARG(IOleCommandTarget, &pOct));
        if (FAILED_UNEXPECTEDLY(hr))
        {
            ERR("CoCreateInstance failed %08x.\n", hr);
            goto cleanup;
        }

        DPA_AppendPtr(hdpa, pOct);

        count++;
    }
    while (1);

    if (ret != ERROR_NO_MORE_ITEMS)
    {
        ERR("RegEnumValueW failed %08x.\n", ret);
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto cleanup;
    }

    RegCloseKey(hkey);

    /* Initialize */
    DPA_EnumCallback(hdpa, InitializeAllCallback, &hr);
    if (FAILED_UNEXPECTEDLY(hr))
        goto cleanup;

    *phdpa = hdpa;
    return count > 0 ? S_OK : S_FALSE;

cleanup:
    *phdpa = NULL;
    ShutdownShellServices(hdpa);
    return hr;
}