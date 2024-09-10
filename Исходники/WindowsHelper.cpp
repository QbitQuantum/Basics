void EnumSerialPortsWindows(std::vector<SerialPortInfo> &serialports)
{
	// Create a device information set that will be the container for 
	// the device interfaces.
	GUID *guidDev = (GUID*)&GUID_CLASS_COMPORT;

	HDEVINFO hDevInfo = INVALID_HANDLE_VALUE;
	SP_DEVICE_INTERFACE_DETAIL_DATA *pDetData = NULL;

	try {
		hDevInfo = SetupDiGetClassDevs(guidDev,
			NULL,
			NULL,
			DIGCF_PRESENT | DIGCF_DEVICEINTERFACE
			);

		if (hDevInfo == INVALID_HANDLE_VALUE)
		{
			return;
		}

		// Enumerate the serial ports
		BOOL bOk = TRUE;
		SP_DEVICE_INTERFACE_DATA ifcData;
		DWORD dwDetDataSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA) + 256;
		pDetData = (SP_DEVICE_INTERFACE_DETAIL_DATA*) new char[dwDetDataSize];
		// This is required, according to the documentation. Yes,
		// it's weird.
		ifcData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
		pDetData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
		for (DWORD ii = 0; bOk; ii++) {
			bOk = SetupDiEnumDeviceInterfaces(hDevInfo,
				NULL, guidDev, ii, &ifcData);
			if (bOk) {
				// Got a device. Get the details.
				SP_DEVINFO_DATA devdata = { sizeof(SP_DEVINFO_DATA) };
				bOk = SetupDiGetDeviceInterfaceDetail(hDevInfo,
					&ifcData, pDetData, dwDetDataSize, NULL, &devdata);
				if (bOk) {
					std::string strDevPath(pDetData->DevicePath);
					// Got a path to the device. Try to get some more info.
					TCHAR fname[256];
					TCHAR desc[256];
					BOOL bSuccess = SetupDiGetDeviceRegistryProperty(
						hDevInfo, &devdata, SPDRP_FRIENDLYNAME, NULL,
						(PBYTE)fname, sizeof(fname), NULL);
					bSuccess = bSuccess && SetupDiGetDeviceRegistryProperty(
						hDevInfo, &devdata, SPDRP_DEVICEDESC, NULL,
						(PBYTE)desc, sizeof(desc), NULL);
					BOOL bUsbDevice = FALSE;
					TCHAR locinfo[256];
					if (SetupDiGetDeviceRegistryProperty(
						hDevInfo, &devdata, SPDRP_LOCATION_INFORMATION, NULL,
						(PBYTE)locinfo, sizeof(locinfo), NULL))
					{
						// Just check the first three characters to determine
						// if the port is connected to the USB bus. This isn't
						// an infallible method; it would be better to use the
						// BUS GUID. Currently, Windows doesn't let you query
						// that though (SPDRP_BUSTYPEGUID seems to exist in
						// documentation only).
						bUsbDevice = (strncmp(locinfo, "USB", 3) == 0);
					}
					// Open device parameters reg key - Added after fact from post on CodeGuru - credit to Peter Wurmsdobler
					HKEY hKey = SetupDiOpenDevRegKey
						(hDevInfo, &devdata, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_READ);

					TCHAR szPortName[MAX_PATH];
					if (hKey)
					{
						DWORD dwType = REG_SZ;
						DWORD dwReqSize = sizeof(szPortName);

						// Query for portname
						long lRet = RegQueryValueEx
							(hKey, "PortName", 0, &dwType, (LPBYTE)&szPortName, &dwReqSize);
						if (lRet == ERROR_SUCCESS)
							bSuccess &= TRUE;
						else
							bSuccess &= FALSE;
					}
					else
						bSuccess &= FALSE;

					if (bSuccess) {
						// Add an entry to the array
						SerialPortInfo si;
						si.szDevPath = strDevPath;
						si.szFriendlyName = fname;
						si.szPortName = szPortName;
						si.szPortDesc = desc;
						si.bUsbDevice = (bUsbDevice==TRUE);
						serialports.push_back(si);
					}

				}
				else {
					return;
				}
			}
			else {
				DWORD err = GetLastError();
				if (err != ERROR_NO_MORE_ITEMS) {
					return;
				}
			}
		}
	}
	catch (...)
	{
	}

	if (pDetData != NULL)
		delete[](char*)pDetData;
	if (hDevInfo != INVALID_HANDLE_VALUE)
		SetupDiDestroyDeviceInfoList(hDevInfo);
}