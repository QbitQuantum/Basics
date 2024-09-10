BOOL LoadInstallableVDD(VOID)
{
#define ERROR_MEMORYVDD L"Insufficient memory to load installable Virtual Device Drivers."
#define ERROR_REGVDD    L"Virtual Device Driver format in the registry is invalid."
#define ERROR_LOADVDD   L"An installable Virtual Device Driver failed Dll initialization."

    BOOL  Success = TRUE;
    LONG  Error   = 0;
    DWORD Type    = 0;
    DWORD BufSize = 0;

    HKEY    hVDDKey;
    LPCWSTR VDDKeyName   = L"SYSTEM\\CurrentControlSet\\Control\\VirtualDeviceDrivers";
    LPWSTR  VDDValueName = L"VDD";
    LPWSTR  VDDList      = NULL;

    HANDLE hVDD;

    /* Try to open the VDD registry key */
    Error = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                          VDDKeyName,
                          0,
                          KEY_QUERY_VALUE,
                          &hVDDKey);
    if (Error == ERROR_FILE_NOT_FOUND)
    {
        /* If the key just doesn't exist, don't do anything else */
        return TRUE;
    }
    else if (Error != ERROR_SUCCESS)
    {
        /* The key exists but there was an access error: display an error and quit */
        DisplayMessage(ERROR_REGVDD);
        return FALSE;
    }

    /*
     * Retrieve the size of the VDD registry value
     * and check that it's of REG_MULTI_SZ type.
     */
    Error = RegQueryValueExW(hVDDKey,
                             VDDValueName,
                             NULL,
                             &Type,
                             NULL,
                             &BufSize);
    if (Error == ERROR_FILE_NOT_FOUND)
    {
        /* If the value just doesn't exist, don't do anything else */
        Success = TRUE;
        goto Quit;
    }
    else if (Error != ERROR_SUCCESS || Type != REG_MULTI_SZ)
    {
        /*
         * The value exists but there was an access error or
         * is of the wrong type: display an error and quit.
         */
        DisplayMessage(ERROR_REGVDD);
        Success = FALSE;
        goto Quit;
    }

    /* Allocate the buffer */
    BufSize = (BufSize < 2*sizeof(WCHAR) ? 2*sizeof(WCHAR) : BufSize);
    VDDList = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, BufSize);
    if (VDDList == NULL)
    {
        DisplayMessage(ERROR_MEMORYVDD);
        Success = FALSE;
        goto Quit;
    }

    /* Retrieve the list of VDDs to load */
    if (RegQueryValueExW(hVDDKey,
                         VDDValueName,
                         NULL,
                         NULL,
                         (LPBYTE)VDDList,
                         &BufSize) != ERROR_SUCCESS)
    {
        DisplayMessage(ERROR_REGVDD);
        Success = FALSE;
        goto Quit;
    }

    /* Load the VDDs */
    VDDValueName = VDDList;
    while (*VDDList)
    {
        DPRINT1("Loading VDD '%S'...", VDDList);
        hVDD = LoadLibraryW(VDDList);
        if (hVDD == NULL)
        {
            DbgPrint("Failed\n");
            DisplayMessage(ERROR_LOADVDD);
        }
        else
        {
            DbgPrint("Succeeded\n");
        }
        /* Go to next string */
        VDDList += wcslen(VDDList) + 1;
    }
    VDDList = VDDValueName;

Quit:
    if (VDDList) HeapFree(GetProcessHeap(), 0, VDDList);
    RegCloseKey(hVDDKey);
    return Success;
}