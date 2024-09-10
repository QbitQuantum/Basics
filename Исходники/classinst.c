static DWORD
RemovePort(IN HDEVINFO DeviceInfoSet,
           IN PSP_DEVINFO_DATA DeviceInfoData)
{
    PORT_TYPE PortType;
    HCOMDB hComDB = HCOMDB_INVALID_HANDLE_VALUE;
    HKEY hKey;
    LONG lError;
    DWORD dwPortNumber;
    DWORD dwPortNameSize;
    WCHAR szPortName[8];

    /* If we are removing a serial port ... */
    PortType = GetPortType(DeviceInfoSet, DeviceInfoData);
    if (PortType == SerialPort)
    {
        /* Open the port database */
        if (ComDBOpen(&hComDB) == ERROR_SUCCESS)
        {
            /* Open the device key */
            hKey = SetupDiOpenDevRegKey(DeviceInfoSet,
                                        DeviceInfoData,
                                        DICS_FLAG_GLOBAL,
                                        0,
                                        DIREG_DEV,
                                        KEY_READ);
            if (hKey != INVALID_HANDLE_VALUE)
            {
                /* Query the port name */
                dwPortNameSize = sizeof(szPortName);
                lError = RegQueryValueEx(hKey,
                                         L"PortName",
                                         NULL,
                                         NULL,
                                         (PBYTE)szPortName,
                                         &dwPortNameSize);

                /* Close the device key */
                RegCloseKey(hKey);

                /* If we got a valid port name ...*/
                if (lError == ERROR_SUCCESS)
                {
                    /* Get the port number */
                    dwPortNumber = _wtoi(szPortName + wcslen(pszCom));

                    /* Release the port */
                    ComDBReleasePort(hComDB, dwPortNumber);
                }
            }

            /* Close the port database */
            ComDBClose(hComDB);
        }
    }

    /* Remove the device */
    if (!SetupDiRemoveDevice(DeviceInfoSet, DeviceInfoData))
        return GetLastError();

    return ERROR_SUCCESS;
}