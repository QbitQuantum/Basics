int battery_init() {
	

	#define GBS_HASBATTERY 0x1
	#define GBS_ONBATTERY  0x2

	DWORD dwResult = GBS_ONBATTERY;
	HDEVINFO hdev = NULL;
	int idev = 0;
	BOOL b;
	DWORD cbRequired = 0;
	SP_DEVICE_INTERFACE_DATA did;

	hdev = SetupDiGetClassDevs(&GUID_DEVCLASS_BATTERY, 
                                0, 
                                0, 
                                DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	if (INVALID_HANDLE_VALUE == hdev) {
		//return hdev;
		printf("GUID_DEVCLASS_BATTERY error\n");
		return -1;
	}

	for (idev = 0; idev < 100; idev++) {
		printf("for\n");
		
		memset(&did, 0, sizeof(did));
		did.cbSize = sizeof(did);

		b = SetupDiEnumDeviceInterfaces(hdev,
                                      0,
                                      &GUID_DEVCLASS_BATTERY,
                                      idev,
                                      &did);
		if (!b) {
			break;
		}

        SetupDiGetDeviceInterfaceDetail(hdev,
                                        &did,
                                        0,
                                        0,
                                        &cbRequired,
                                        0);

		if (ERROR_INSUFFICIENT_BUFFER == GetLastError()) {
			PSP_DEVICE_INTERFACE_DETAIL_DATA pdidd =
			 (PSP_DEVICE_INTERFACE_DETAIL_DATA) LocalAlloc(LPTR, cbRequired);

			if (!pdidd) {
				log_err("battery_init: LocalAlloc failed, size %d", cbRequired);
				SetupDiDestroyDeviceInfoList(hdev);
				return -1;
			}

			pdidd->cbSize = sizeof(*pdidd);
            if (SetupDiGetDeviceInterfaceDetail(hdev,
                                                &did,
                                                pdidd,
                                                cbRequired,
                                                &cbRequired,
                                                0))
            {
				// Enumerated a battery.  Ask it for information.
				HANDLE hBattery = CreateFile(pdidd->DevicePath,
                                 GENERIC_READ | GENERIC_WRITE,
                                 FILE_SHARE_READ | FILE_SHARE_WRITE,
                                 NULL,
                                 OPEN_EXISTING,
                                 FILE_ATTRIBUTE_NORMAL,
                                 NULL);
				if (INVALID_HANDLE_VALUE != hBattery) {
					//printf("battery handle: %d\n", hBattery);
					//_bat[idev] = hBattery;
					_bathandle  = hBattery;
					LocalFree(pdidd);
					break;
				} else {
					log_warn("battery_init: failed to open device file: %s", pdidd->DevicePath);
				}
			} else {
					log_warn("battery_init:SetupDiGetDeviceInterfaceDetail failed");
			}

			LocalFree(pdidd);
		} // end if ERROR_INSUFFICIENT_BUFFER

	} // end for
      
	SetupDiDestroyDeviceInfoList(hdev);

	if (_bathandle != 0) {
		BATTERY_INFORMATION BatteryInfo;

		memset(&BatteryInfo, 0, sizeof(BATTERY_INFORMATION));
	
		if (BatteryQueryInformation(_bathandle,
									BatteryInformation,
									(LPVOID)&BatteryInfo,
									sizeof(BatteryInfo))) {
			_max_capacity = (float) BatteryInfo.FullChargedCapacity;
		} else {
			log_err("battery_info: failed to retrieve the maximum capacity of the battery");
			 CloseHandle(_bathandle);
			 _bathandle = 0;
			return -1;
		}

		battery_print_info(_bathandle);
	}
	printf("battery_init end \n");
	return 0;
}