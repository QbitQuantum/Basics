// CDeviceSelect message handlers
BOOL CDeviceSelect::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    HDEVINFO                            hardwareDeviceInfo;
    PSP_DEVICE_INTERFACE_DETAIL_DATA    deviceInterfaceDetailData = NULL;
    ULONG                               predictedLength = 0;
    ULONG                               requiredLength = 0, bytes=0;
	WCHAR								szBda[13] = {0};
	HANDLE								hDevice = INVALID_HANDLE_VALUE;

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

    m_numDevices = 0;

    if ((hardwareDeviceInfo = SetupDiGetClassDevs (NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT)) != INVALID_HANDLE_VALUE)
    {
        SP_DEVINFO_DATA DeviceInfoData;

        memset(&DeviceInfoData, 0, sizeof(DeviceInfoData));
        DeviceInfoData.cbSize = sizeof(DeviceInfoData);

        WCHAR szService[80];
        GUID guid;
        if (m_bWin8)
            guid = GUID_LONG_CHAR_SERVICE;
        else
        {
            guid.Data1 = (GUID_LONG_CHAR_SERVICE.Data4[4]     ) + (GUID_LONG_CHAR_SERVICE.Data4[5] << 8) + (GUID_LONG_CHAR_SERVICE.Data4[6] << 16) + (GUID_LONG_CHAR_SERVICE.Data4[7] << 24);
            guid.Data2 = (GUID_LONG_CHAR_SERVICE.Data4[2]     ) + (GUID_LONG_CHAR_SERVICE.Data4[3] << 8);
            guid.Data3 = (GUID_LONG_CHAR_SERVICE.Data4[0]     ) + (GUID_LONG_CHAR_SERVICE.Data4[1] << 8);
            guid.Data4[0] = (GUID_LONG_CHAR_SERVICE.Data3      ) & 0xff;
            guid.Data4[1] = (GUID_LONG_CHAR_SERVICE.Data3 >> 8 ) & 0xff;
            guid.Data4[2] = (GUID_LONG_CHAR_SERVICE.Data2      ) & 0xff;
            guid.Data4[3] = (GUID_LONG_CHAR_SERVICE.Data2 >> 8 ) & 0xff;
            guid.Data4[4] = (GUID_LONG_CHAR_SERVICE.Data1      ) & 0xff;
            guid.Data4[5] = (GUID_LONG_CHAR_SERVICE.Data1 >> 8 ) & 0xff;
            guid.Data4[6] = (GUID_LONG_CHAR_SERVICE.Data1 >> 16) & 0xff;
            guid.Data4[7] = (GUID_LONG_CHAR_SERVICE.Data1 >> 24) & 0xff;
        }
        UuidToString(szService, 80, &guid);
        ods ("%S\n", szService);
        for (DWORD n = 0; SetupDiEnumDeviceInfo(hardwareDeviceInfo, n, &DeviceInfoData); n++)
        {
            DWORD dwBytes = 0;

            SetupDiGetDeviceInstanceId(hardwareDeviceInfo, &DeviceInfoData, NULL, 0, &dwBytes);

            PWSTR szInstanceId = new WCHAR [dwBytes];
            if (szInstanceId)
            {
                if (SetupDiGetDeviceInstanceId(hardwareDeviceInfo, &DeviceInfoData, szInstanceId, dwBytes, &dwBytes))
                {
                    _wcsupr_s (szInstanceId, dwBytes);
//                    if (wcsstr(szInstanceId, L"BTHENUM"))
//                    {
//                        OutputDebugStringW(szInstanceId);
//                        OutputDebugStringW(L"\n");
                    if (wcsstr(szInstanceId, szService))
                    {
                        OutputDebugStringW(szInstanceId);
                        WCHAR buf[13];
                        wchar_t* pStart;
                        wchar_t* pEnd;
                        if (m_bWin8)
                        {
                            pStart = wcsrchr(szInstanceId, '_');
                            pEnd = wcsrchr(szInstanceId, '\\');
                        }
                        else
                        {
                            pStart = wcsrchr(szInstanceId, '&');
                            pEnd = wcsrchr(szInstanceId, '_');
                        }
                        if (pStart && pEnd)
                        {
                            *pEnd = 0;
                            wcscpy_s(buf, pStart + 1);
                            m_lbDevices.AddString(buf);
                            m_numDevices++;
                        }
//                    }
                    }
                }
                delete[] szInstanceId;
            }
        }
        SetupDiDestroyDeviceInfoList(hardwareDeviceInfo);
    }