CString CDlgDialbox::EnumComPort() {
	CString sRtn = "";
	//161229 list bluetooth com port

	BLUETOOTH_FIND_RADIO_PARAMS btFindRadioParams = {sizeof(BLUETOOTH_FIND_RADIO_PARAMS)};
	BLUETOOTH_RADIO_INFO btRadioInfo = {sizeof(BLUETOOTH_RADIO_INFO), 0};
	BLUETOOTH_DEVICE_SEARCH_PARAMS btDeviceSearchParams = {
		sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS), 
		TRUE,	//BOOL fReturnAuthenticated;
		TRUE,	//BOOL fReturnRemembered;
		TRUE,	//BOOL fReturnUnknown;
		TRUE,	//BOOL fReturnConnected;
		FALSE,	//BOOL fIssueInquiry;
		10,		//UCHAR cTimeoutMultiplier;
		NULL	//HANDLE hRadio;
	};

	BLUETOOTH_DEVICE_INFO btDeviceInfo = {sizeof(BLUETOOTH_DEVICE_INFO), 0};

	HANDLE hRadio = NULL;
	HBLUETOOTH_DEVICE_FIND hbtDeviceFind = NULL;

	HBLUETOOTH_RADIO_FIND hbtRadioFind = BluetoothFindFirstRadio(&btFindRadioParams, &hRadio);
	if (hbtRadioFind) {
		do {
			if (BluetoothGetRadioInfo(hRadio, &btRadioInfo) == ERROR_SUCCESS) {
				btDeviceSearchParams.hRadio = hRadio;
				ZeroMemory(&btDeviceInfo, sizeof(BLUETOOTH_DEVICE_INFO));
				btDeviceInfo.dwSize = sizeof(BLUETOOTH_DEVICE_INFO);

				hbtDeviceFind = BluetoothFindFirstDevice(&btDeviceSearchParams, &btDeviceInfo);
				if (hbtDeviceFind) {
					do {
						CString sDeviceName(btDeviceInfo.szName);
						CString sAddr;
						sAddr.Format("%02x%02x%02x%02x%02x%02x", 
							btDeviceInfo.Address.rgBytes[5],btDeviceInfo.Address.rgBytes[4], btDeviceInfo.Address.rgBytes[3],
									btDeviceInfo.Address.rgBytes[2], btDeviceInfo.Address.rgBytes[1], btDeviceInfo.Address.rgBytes[0]);
						sAddr.MakeUpper();
						CString sComPort = GetBthComPort(sAddr);
						if (!sComPort.IsEmpty() && (sDeviceName.Find(BLUETOOTH_DEVICENAME_KEY) >= 0)) {
							sRtn += sComPort + "\r" + sDeviceName + "\r";
						}

					} while (BluetoothFindNextDevice(hbtDeviceFind, &btDeviceInfo));
				}
				BluetoothFindDeviceClose(hbtDeviceFind);
			}
			CloseHandle(hRadio);
		} while (BluetoothFindNextRadio(hbtRadioFind, &hRadio));
		BluetoothFindRadioClose(hbtRadioFind);
	}

	//list other serial ports
	HKEY hKey = NULL;
	TCHAR tcName[256];
	BYTE cData[256];
	DWORD dwNameBuffSize = sizeof(tcName);
	DWORD dwDataBuffSize = sizeof(cData);
	if (!RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("HARDWARE\\DEVICEMAP\\SERIALCOMM" ), NULL, KEY_READ, &hKey)) {
		int i = 0;
		while (RegEnumValue(hKey, i, tcName, &dwNameBuffSize, NULL, NULL, cData, &dwDataBuffSize) == ERROR_SUCCESS) {
			if (!strstr(tcName, "BthModem")) {
				CString sPortName;
				sPortName.Format("%s\r%s\r", (char*)cData, tcName);
				sRtn += sPortName;
			}
			dwNameBuffSize = sizeof(tcName);
			dwDataBuffSize = sizeof(cData);
			i++;
		}
	}
	return sRtn;
}