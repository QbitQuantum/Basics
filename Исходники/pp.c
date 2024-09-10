/*++

Routine Description: FillPortSettingsDlg

    fill in the port settings dlg sheet

Arguments:

    params: the data to fill in
    hDlg:              address of the window

Return Value:

    ULONG: returns error messages

--*/
ULONG
FillPortSettingsDlg(
    IN HWND             DialogHwnd,
    IN PPORT_PARAMS     Params
    )
{
    HKEY  hDeviceKey;
    DWORD dwPortNameSize, dwError;
    TCHAR szCharBuffer[81];

    //
    // Open the device key for the source device instance, and retrieve its
    // "PortName" value.
    //
    hDeviceKey = SetupDiOpenDevRegKey(Params->DeviceInfoSet,
                                      Params->DeviceInfoData,
                                      DICS_FLAG_GLOBAL,
                                      0,
                                      DIREG_DEV,
                                      KEY_READ);

    if (INVALID_HANDLE_VALUE == hDeviceKey) {
        goto RetGetLastError;
    }

    dwPortNameSize = sizeof(Params->PortSettings.szComName);
    dwError = RegQueryValueEx(hDeviceKey,
                              m_szPortName,  // "PortName"
                              NULL,
                              NULL,
                              (PBYTE)Params->PortSettings.szComName,
                              &dwPortNameSize);

    RegCloseKey(hDeviceKey);

    if(ERROR_SUCCESS != dwError) {
        goto RetERROR;
    }

    //
    // create "com#:"
    //
    StringCchCopy(szCharBuffer, ARRAYSIZE(szCharBuffer), Params->PortSettings.szComName);
    StringCchCat(szCharBuffer, ARRAYSIZE(szCharBuffer), m_szColon);

    //
    // get values from system, fills in baudrate, parity, etc.
    //
    GetPortSettings(DialogHwnd, szCharBuffer, Params);

    if (!Params->ChangesEnabled) {
        EnableWindow(GetDlgItem(DialogHwnd, PP_PORT_BAUDRATE), FALSE);
        EnableWindow(GetDlgItem(DialogHwnd, PP_PORT_PARITY), FALSE);
        EnableWindow(GetDlgItem(DialogHwnd, PP_PORT_DATABITS), FALSE);
        EnableWindow(GetDlgItem(DialogHwnd, PP_PORT_STOPBITS), FALSE);
        EnableWindow(GetDlgItem(DialogHwnd, PP_PORT_FLOWCTL), FALSE);
    }

    return 0;

RetERROR:
    return dwError;

RetGetLastError:
   return GetLastError();
} /* FillPortSettingsDlg */