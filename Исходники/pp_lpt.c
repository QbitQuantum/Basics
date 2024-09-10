UINT
LptEnactPortNameChanges(
    IN HWND             ParentHwnd,
    IN PLPT_PROP_PARAMS LptPropParams,
    IN HKEY             hDeviceKey,
    IN UINT             NewLptNum)
{
    HANDLE  hLpt;
    DWORD   dwError, dwNewLptNameLen;
    BYTE    portUsage[MAX_LPT_PORT];
    TCHAR   charBuffer[LINE_LEN],
            friendlyNameFormat[LINE_LEN],
            deviceDesc[LINE_LEN],
            buffer[BUFFER_SIZE],
            szNewLptName[20];

    //
    // Check if we're trying to rename the port to the same name.
    //
    StringCchPrintf(szNewLptName, ARRAYSIZE(szNewLptName), _T("\\DosDevices\\LPT%d"), NewLptNum);
    if (wcscmp(szNewLptName, LptPropParams->szLptName) == 0) {
        return ERROR_SUCCESS;
    }

    //
    // Check if a valid port number has been passed in
    //
    if (MAX_LPT_PORT < NewLptNum) {
        //
        // Get out of here - exceeding array bounds
        // This should never happen in the property page since it is a hardcoded
        // selection box.  The user can't simply type a number.
        //
        MyMessageBox(ParentHwnd, IDS_LPT_NUM_ERROR, IDS_LPT_PROPERTIES,
            MB_OK | MB_ICONINFORMATION);
        return ERROR_SUCCESS;
    }

    //
    // Get an array of used ports
    //
    LptEnumerateUsedPorts(ParentHwnd,
                          portUsage,
                          MAX_LPT_PORT);
    if (portUsage[NewLptNum-1]) {
        //
        // Port name is taken by another port.  Check if user wants system to
        // get into inconsistent state.
        //
        if (IDNO == MyMessageBox(ParentHwnd, IDS_LPT_PORT_INUSE,
                                 IDS_LPT_PROPERTIES, MB_YESNO |
                                 MB_ICONINFORMATION)) {
            return ERROR_SUCCESS;
        }
    }

    //
    // Make sure that the port has not been opened by another application
    //
    StringCchPrintf(buffer, ARRAYSIZE(buffer), L"\\\\.\\%ws", LptPropParams->szLptName);
    hLpt = CreateFile(buffer, GENERIC_READ, 0, NULL, OPEN_EXISTING,
                      FILE_ATTRIBUTE_NORMAL, NULL);

    //
    // If the file handle is invalid, then the Lpt port is open, warn the user
    //
    if (hLpt == INVALID_HANDLE_VALUE &&
        MyMessageBox(ParentHwnd, IDS_PORT_OPEN, IDS_LPT_PROPERTIES,
                     MB_YESNO | MB_ICONINFORMATION) == IDNO) {
        return GetLastError();
    }
    CloseHandle(hLpt);

    StringCchPrintf(szNewLptName, ARRAYSIZE(szNewLptName), _T("LPT%d"), NewLptNum);

    //
    // Open the device key for the source device instance, and write its
    // new "PortName" value.
    //
    hDeviceKey = SetupDiOpenDevRegKey(LptPropParams->DeviceInfoSet,
                                      LptPropParams->DeviceInfoData,
                                      DICS_FLAG_GLOBAL,
                                      0,
                                      DIREG_DEV,
                                      KEY_READ | KEY_WRITE);

    if (INVALID_HANDLE_VALUE == hDeviceKey) {
        return GetLastError();
    }

    dwNewLptNameLen = ByteCountOf((DWORD)wcslen(szNewLptName) + 1);

    dwError = RegSetValueEx(hDeviceKey,
                            m_szPortName,
                            0,
                            REG_SZ,
                            (PBYTE) szNewLptName,
                            dwNewLptNameLen);
    if (ERROR_SUCCESS == dwError) {
        StringCchCopy(LptPropParams->szLptName, ARRAYSIZE(LptPropParams->szLptName), szNewLptName);
    } else {
        return dwError;
    }

    // Now generate a string, to be used for the device's friendly name, that
    // incorporates both the INF-specified device description, and the port
    // name.  For example,
    //
    //     ECP Printer Port (LPT1)
    //

    // If we can load the device description and the localized friendly format,
    // then compose the two
    // If we can only load the device description, then use that as the friendly name
    // If we can't load either, put a non localized string in there

    charBuffer[0] = L'\0';
    if( SetupDiGetDeviceRegistryProperty(LptPropParams->DeviceInfoSet,
                                         LptPropParams->DeviceInfoData,
                                         SPDRP_DEVICEDESC,
                                         NULL,
                                         (PBYTE)deviceDesc,
                                         sizeof(deviceDesc),
                                         NULL))
    {
        if (LoadString(g_hInst,
                       IDS_FRIENDLY_FORMAT,
                       friendlyNameFormat,
                       ARRAYSIZE(friendlyNameFormat)))
        {
            
            StringCchPrintf(charBuffer,
                            ARRAYSIZE(charBuffer),
                            friendlyNameFormat,
                            deviceDesc,
                            szNewLptName);
        }
        else
        {
            StringCchCopy(charBuffer, ARRAYSIZE(charBuffer), deviceDesc);
        }
    }
    else
    {
        //
        // Simply use LPT port name.
        //
        StringCchCopy(charBuffer, ARRAYSIZE(charBuffer), szNewLptName);
    }

    SetupDiSetDeviceRegistryProperty(LptPropParams->DeviceInfoSet,
                                     LptPropParams->DeviceInfoData,
                                     SPDRP_FRIENDLYNAME,
                                     (PBYTE)charBuffer,
                                     ByteCountOf(lstrlen(charBuffer) + 1)
                                    );

    return ERROR_SUCCESS;

} // LptEnactPortNameChanges