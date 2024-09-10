PXCSession* PXCAPI PXCSession_Create(void) {
    LONG err_code;
    HKEY key = 0;
    DWORD type = 0;

    // try LocalRuntime registry key if set
    for (int i = 0; i < (sizeof(void*)/4); i++)
    {
        err_code = RegOpenKeyEx(HKEY_LOCAL_MACHINE, (!i) ? RSSDK_REG_DEV TEXT("\\Dispatch") : RSSDK_REG_DEV32 TEXT("\\Dispatch"), 0, KEY_READ, &key);
        if (err_code != ERROR_SUCCESS) continue;

        pxcCHAR local_path[MAX_PATH] = L"";
        DWORD size = sizeof(local_path);
        err_code = RegGetValue(key, 0, RSSDK_REG_LOCAL, RRF_RT_REG_SZ, &type, local_path, &size);
        RegCloseKey(key);
        if (err_code != ERROR_SUCCESS || !local_path[0]) continue;

        pxcCHAR filepath[MAX_PATH] = L"";
        if (local_path[0] == '.') // relative path
        {
            // get module folder
            HMODULE handle = 0;
            GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)LoadSessionLibrary, &handle);
            GetModuleFileName(handle,filepath,MAX_PATH);
            pxcCHAR *pSlash=wcsrchr(filepath,L'\\');
            if (pSlash) pSlash[1]=0;
            PRINT_INFO((L"The SDK INFO: Application folder: %s\n", filepath));
            wcscat_s<MAX_PATH>(filepath,local_path);
            wcscat_s<MAX_PATH>(filepath,L"\\libpxcsession.dll");
        } else // absolute path
        {
            wcscpy_s<MAX_PATH>(filepath,local_path);
            wcscat_s<MAX_PATH>(filepath,SESSION_RELATIVE_PATH);
        }
        PXCSession *session=LoadSessionLibrary(filepath, 1);
        if (session) return session;

        // try __FILE__ at compilation time
        pxcCHAR filename[MAX_PATH];
        MultiByteToWideChar(CP_UTF8, 0, __FILE__, -1, filename, sizeof(filename));
        pxcCHAR *pSlash=wcsrchr(filename,L'\\');
        if (pSlash) *pSlash=0;
        wcscat_s(filename, MAX_PATH, L"\\..\\..");
        wcscat_s(filename, MAX_PATH, SESSION_RELATIVE_PATH);
        session = LoadSessionLibrary(filename, 1);
        if (session) return session;
    }

    // standard registry key set by SDK installer
    pxcCHAR dll_path[MAX_PATH] = L"";
    err_code = RegOpenKeyEx(HKEY_LOCAL_MACHINE, RSSDK_REG_DISPATCH, 0, KEY_READ, &key);
    if (err_code == ERROR_SUCCESS) {
        DWORD size = sizeof(dll_path);
        RegGetValue(key, 0, RSSDK_REG_MAIN, RRF_RT_REG_SZ, &type, dll_path, &size);
        RegCloseKey(key);
    }
    if (dll_path[0])
    {
        PRINT_INFO((L"The SDK INFO: Loading core library from path specified in %s\n", RSSDK_REG_DISPATCH L"\\" RSSDK_REG_MAIN));
        return LoadSessionLibrary(dll_path, 0);
    } else
    {
        PRINT_INFO((L"The SDK INFO: FAILED to open registry key %s\n", RSSDK_REG_DISPATCH L"\\" RSSDK_REG_MAIN));
        return 0;
    }
}