VOID
WINAPI
StreamingDeviceSetupW(IN HWND hwnd, 
                     IN HINSTANCE hinst, 
                     IN LPWSTR lpszCmdLine, 
                     IN int nCmdShow)
{
    DWORD Length, dwResult;
    LPWSTR pCmdLine;
    LPWSTR pStr; 
    GUID Guids[2];
    WCHAR DevicePath[MAX_PATH];
    HRESULT hResult;
    DWORD Index;

    Length = (wcslen(lpszCmdLine) + 1) * sizeof(WCHAR);

    pCmdLine = (LPWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, Length);
    if (pCmdLine == NULL)
    {
        // no memory
        return;
    }

    hResult = StringCbCopyExW(pCmdLine, Length, lpszCmdLine, NULL, NULL, STRSAFE_NULL_ON_FAILURE);
    if (hResult != S_OK)
    {
        // failed
        HeapFree(GetProcessHeap(), 0, pCmdLine);
        return;
    }

    pStr = wcstok(pCmdLine, L",\t\"");
    Index = 0;
    do
    {
        if (pStr == NULL)
        {
            // invalid parameter
            HeapFree(GetProcessHeap(), 0, pCmdLine);
            return;
        }

        hResult = IIDFromString(pStr, &Guids[Index]);
        if (hResult != S_OK)
        {
            // invalid parameter
            HeapFree(GetProcessHeap(), 0, pCmdLine);
            return;
        }

        Index++;
        pStr = wcstok(NULL, L",\t\"");


    }while(Index < 2);


    dwResult = InstallSoftwareDeviceInterface(&Guids[0], &Guids[1], pStr);
    if (dwResult == ERROR_SUCCESS)
    {
        pStr = wcstok(NULL, L",\t\"");
        if (pStr != NULL)
        {
            wcscpy(DevicePath, pStr);
            pStr = wcstok(NULL, L",\t\"");
            if (pStr != NULL)
            {
                dwResult = InstallSoftwareDeviceInterfaceInf(DevicePath, pStr);
            }
        }
    }
}