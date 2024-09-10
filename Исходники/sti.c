static HRESULT WINAPI stillimagew_RegisterLaunchApplication(IStillImageW *iface, LPWSTR pwszAppName,
                                                            LPWSTR pwszCommandLine)
{
    static const WCHAR format[] = {'%','s',' ','%','s',0};
    static const WCHAR commandLineSuffix[] = {
        '/','S','t','i','D','e','v','i','c','e',':','%','1',' ',
        '/','S','t','i','E','v','e','n','t',':','%','2',0};
    HKEY registeredAppsKey = NULL;
    DWORD ret;
    HRESULT hr = S_OK;
    stillimage *This = impl_from_IStillImageW(iface);

    TRACE("(%p, %s, %s)\n", This, debugstr_w(pwszAppName), debugstr_w(pwszCommandLine));

    ret = RegCreateKeyW(HKEY_LOCAL_MACHINE, registeredAppsLaunchPath, &registeredAppsKey);
    if (ret == ERROR_SUCCESS)
    {
        WCHAR *value = HeapAlloc(GetProcessHeap(), 0,
            (lstrlenW(pwszCommandLine) + 1 + lstrlenW(commandLineSuffix) + 1) * sizeof(WCHAR));
        if (value)
        {
            sprintfW(value, format, pwszCommandLine, commandLineSuffix);
            ret = RegSetValueExW(registeredAppsKey, pwszAppName, 0,
                REG_SZ, (BYTE*)value, (lstrlenW(value)+1)*sizeof(WCHAR));
            if (ret != ERROR_SUCCESS)
                hr = HRESULT_FROM_WIN32(ret);
            HeapFree(GetProcessHeap(), 0, value);
        }
        else
            hr = E_OUTOFMEMORY;
        RegCloseKey(registeredAppsKey);
    }
    else
        hr = HRESULT_FROM_WIN32(ret);
    return hr;
}