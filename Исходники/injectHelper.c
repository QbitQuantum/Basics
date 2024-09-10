int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nShowCmd)
{
    LPWSTR pCommandLineW = GetCommandLineW();
    int retVal = 0;
    DWORD id = 0;
    int numArgs = 0;
    bool safe = false;

#ifdef _WIN64
    const wchar_t pDLLName[] = L"GraphicsCaptureHook64.dll";
#else
    const wchar_t pDLLName[] = L"GraphicsCaptureHook.dll";
#endif

    /* -------------------------- */

    LPWSTR *pCommandLineArgs = CommandLineToArgvW(pCommandLineW, &numArgs);

    LoadSeDebugPrivilege();

    if (numArgs > 2)
    {
        safe = *pCommandLineArgs[2] == '1';
        id = wcstoul(pCommandLineArgs[1], NULL, 10);
        if (id != 0)
        {
            if (!safe)
            {
                OPPROC pOpenProcess;
                HANDLE hProcess;
                char pOPStr[12];
                int i;

                memcpy(pOPStr, "NpflUvhel{x", 12); //OpenProcess obfuscated
                for (i = 0; i<11; i++) pOPStr[i] ^= i ^ 1;

                pOpenProcess = (OPPROC)GetProcAddress(GetModuleHandle(TEXT("KERNEL32")), pOPStr);

                hProcess = (*pOpenProcess)(PROCESS_ALL_ACCESS, FALSE, id);
                if (hProcess)
                {
                    UINT dirLen = GetCurrentDirectory(0, 0); /* includes null terminator */
                    const UINT fileNameLen = (sizeof(pDLLName) / sizeof(wchar_t)) - 1;
                    UINT len = dirLen + fileNameLen + 1; /* 1 for '/' */
                    wchar_t *pPath;

                    /* -------------------------- */

                    if (dirLen)
                    {
                        pPath = (wchar_t*)malloc(len * sizeof(wchar_t));
                        memset(pPath, 0, len * sizeof(wchar_t));

                        GetCurrentDirectoryW(dirLen, pPath);
                        pPath[dirLen - 1] = '\\';
                        wcsncpy_s(pPath + dirLen, len - dirLen, pDLLName, fileNameLen);

                        if (!InjectLibrary(hProcess, pPath, len - 1))
                        {
                            retVal = GetLastError();
                            if (!retVal)
                                retVal = -5;
                        }

                        free(pPath);
                    }
                    else
                        retVal = -4;

                    CloseHandle(hProcess);
                }
                else
                    retVal = -3;
            }
            else
            {
                UINT dirLen = GetCurrentDirectory(0, 0); /* includes null terminator */
                const UINT fileNameLen = (sizeof(pDLLName) / sizeof(wchar_t)) - 1;
                UINT len = dirLen + fileNameLen + 1; /* 1 for '/' */
                wchar_t *pPath;

                /* -------------------------- */

                if (dirLen)
                {
                    pPath = (wchar_t*)malloc(len * sizeof(wchar_t));
                    memset(pPath, 0, len * sizeof(wchar_t));

                    GetCurrentDirectoryW(dirLen, pPath);
                    pPath[dirLen - 1] = '\\';
                    wcsncpy_s(pPath + dirLen, len - dirLen, pDLLName, fileNameLen);

                    if (!InjectLibrarySafe(id, pPath, len - 1))
                    {
                        retVal = GetLastError();
                        if (!retVal)
                            retVal = -7;
                    }

                    free(pPath);
                }
                else
                    retVal = -6;
            }
        }
        else
            retVal = -2;
    }
    else
        retVal = -1;

    LocalFree(pCommandLineArgs);

    return retVal;
}