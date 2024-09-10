extern "C" void __declspec(dllexport) RemoveService(
    HWND hwndParent, 
    int string_size, 
    TCHAR *variables, 
    stack_t **stacktop)
{
    TCHAR ServiceName[100] = {0};

    TCHAR* reason = 0;
    TCHAR* stopString = NULL;
    BOOL okay = FALSE;
    DWORD error = 0;

    g_hwndParent=hwndParent;
    g_stringsize=string_size;
    g_stacktop=stacktop;
    g_variables=variables;

    //MessageBox(hwndParent, TEXT("Enter Remove Service"), TEXT("RemoveService"), MB_OK);

    if (0 == popstring(ServiceName))
    {
        //MessageBox(hwndParent, ServiceName, TEXT("RemoveService"), MB_OK);

        SC_HANDLE hSCM = OpenSCManager(0,0,SC_MANAGER_ALL_ACCESS);
        if (hSCM)
        {
            SC_HANDLE hService = OpenService(hSCM, ServiceName, SERVICE_ALL_ACCESS);
            if (hService)
            {
                SC_LOCK hLock = LockServiceDatabase(hSCM);
                if(hLock)
                {
                    okay = DeleteService(hService);
                    if (!okay)
                    {
                        error = GetLastError();
                    }
                    UnlockServiceDatabase(hLock);
                }
                else
                {
                    error = GetLastError();
                }
                CloseServiceHandle(hService);
            }
            else
            {
                error = GetLastError();
            }
            CloseServiceHandle(hSCM);
        }
        else
        {
            error = GetLastError();
        }
    }
    else
    {
        SetLastError(ERROR_INVALID_PARAMETER);
    }

    if (FALSE == okay)
    {
        if (!reason)
        {
            LPVOID lpMsgBuf = NULL;
            FormatMessage( 
                FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                FORMAT_MESSAGE_FROM_SYSTEM | 
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                error,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                (LPTSTR) &lpMsgBuf,
                0,
                NULL 
                );

            pushstring((TCHAR*)lpMsgBuf);
            LocalFree(lpMsgBuf);
        }
        else
        {
            pushstring(reason);
        }
    }
    else
    {
        pushstring(TEXT("Ok"));
    }

}