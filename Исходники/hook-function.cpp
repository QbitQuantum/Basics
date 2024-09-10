void GetRawInputDevice(bool is_mame_game)
{
	UINT nDevices;
	PRAWINPUTDEVICELIST pRawInputDeviceList;

	char output[256];

	if (GetRawInputDeviceList(NULL, &nDevices, sizeof(RAWINPUTDEVICELIST)) != 0) { 
		ga_error("GetRawInputDeviceList failed.\n");
		exit(-1);
	}

	if ((pRawInputDeviceList = (PRAWINPUTDEVICELIST) malloc(sizeof(RAWINPUTDEVICELIST) * nDevices)) == NULL) {
		ga_error("Memory allocation for RawInputDeviceList failed.\n");
		exit(-1);
	}

	nDevices = GetRawInputDeviceList(pRawInputDeviceList, &nDevices, sizeof(RAWINPUTDEVICELIST));
	if (nDevices <= 0) {
		ga_error("GetRawInputDeviceList failed.\n");
		exit(-1);
	}
	ga_error("[raw input device] number of devices: %d\n", nDevices);

	int device_i = 0; 

//#define SHOW_DEVICE_MSG

	int j;
	RID_DEVICE_INFO rdi;
	rdi.cbSize = sizeof(RID_DEVICE_INFO);
	for (j = 0; j < nDevices; j++) {
		UINT nBufferSize = 256;
		char tBuffer[256] = {0};
		if (GetRawInputDeviceInfo(pRawInputDeviceList[j].hDevice,
							RIDI_DEVICENAME,
							tBuffer,
							&nBufferSize) < 0) {
			ga_error("[device %d] Unable to get device name\n", j);
			continue;
		}
#ifdef SHOW_DEVICE_MSG
		ga_error("[device %d] device name: %s\n", j, tBuffer);
#endif
		//
		
		UINT cbSize = rdi.cbSize;
		if (GetRawInputDeviceInfo(pRawInputDeviceList[j].hDevice, 
							RIDI_DEVICEINFO,
							&rdi,
							&cbSize) < 0) {
			ga_error("[device %d] Unable to get device info\n", j);
			continue;
		}
		if (rdi.dwType == RIM_TYPEMOUSE) {
#ifdef SHOW_DEVICE_MSG
			ga_error("[device %d][Mouse] id: %ld, number of buttons: %ld, sample rate: %ld\n", 
				j, 
				rdi.mouse.dwId, 
				rdi.mouse.dwNumberOfButtons, 
				rdi.mouse.dwSampleRate);
#endif
		} else if (rdi.dwType == RIM_TYPEKEYBOARD) {
#ifdef SHOW_DEVICE_MSG
			ga_error("[device %d][keyboard] mode %ld, number of function keys: %ld, indicators: %ld, keys total: %ld, type: %ld, subtype: %ld\n", 
				j, 
				rdi.keyboard.dwKeyboardMode, 
				rdi.keyboard.dwNumberOfFunctionKeys,
				rdi.keyboard.dwNumberOfIndicators,
				rdi.keyboard.dwNumberOfKeysTotal,
				rdi.keyboard.dwType,
				rdi.keyboard.dwSubType);
#endif
			//char *str_loc; 
			if (strstr(tBuffer, "HID") != NULL) {
				device_i = j;
				tmpRawKeyDevice = pRawInputDeviceList[j].hDevice;
				ga_error("[raw input device] keyboard device is found!\n");
				break;
			}
		} else {
#ifdef SHOW_DEVICE_MSG
			ga_error("[device %d][hid] vender id: %ld, product id: %ld, version no: %ld, usage: %ld, usage page: %ld\n", 
				j, 
				rdi.hid.dwVendorId,
				rdi.hid.dwProductId,
				rdi.hid.dwVersionNumber,
				rdi.hid.usUsage,
				rdi.hid.usUsagePage);
#endif
		}
	}

	//int device_i = 0; 
	if (is_mame_game) {
		ga_error("[RAW INPUT] GetRawInputDevice: MAME device!!");
		//device_i = 3;
	}
	//RAWINPUTDEVICELIST *device = &pRawInputDeviceList[device_i];
	//tmpRawKeyDevice = device->hDevice;
   
	snprintf(output, sizeof(output), "[GetRawInputDevice] keyDevice: %u (%d)", tmpRawKeyDevice, device_i);
	OutputDebugString(output);

	free(pRawInputDeviceList);

	return;
}