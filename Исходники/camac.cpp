ULONG GetSymbolicLink(void)
{		
	//OutputDebugString("GetSymbolicLink\r\n");
	int found_index = 0;
    HDEVINFO hDevInfo;

    // obtain a handle to device information set for all
    // kernel streaming audio devices present on the system
    hDevInfo = SetupDiGetClassDevs(
                        &CamacGuid,
                        NULL,
                        NULL,
                        DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);

    if (hDevInfo == INVALID_HANDLE_VALUE)
    { // function returned 0
      // No audio devices are present on the system
        return 0;
    }
    else
    {
        TCHAR HardwareID[512];
        USHORT found_index = 0;
	
        // Enumerate first device of our class. 

        SP_DEVICE_INTERFACE_DATA ifdata;
		ifdata.cbSize = sizeof(ifdata);

		for ( DWORD devindex = 0;
				SetupDiEnumInterfaceDevice(hDevInfo, NULL,&CamacGuid, devindex, &ifdata);
				++devindex )
		{

			// Determine the symbolic link name for this device instance. Since
			// this is variable in length, make an initial call to determine
			// the required length.

			DWORD needed;
			SetupDiGetDeviceInterfaceDetail(hDevInfo, &ifdata, NULL, 0, &needed, NULL);
				// this call determines the size of memory to allocate

			PSP_INTERFACE_DEVICE_DETAIL_DATA detail = (PSP_INTERFACE_DEVICE_DETAIL_DATA) malloc(needed);
				// zero the structure
				memset (detail,0,needed);

				// set the size of the structure without the string at the end
			detail->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);

			SP_DEVINFO_DATA did = {sizeof(SP_DEVINFO_DATA)};
			SetupDiGetDeviceInterfaceDetail(hDevInfo, &ifdata, detail, needed, NULL, &did);
			
			// Determine the device's link name
			SetupDiGetDeviceRegistryProperty(hDevInfo, &did,SPDRP_HARDWAREID, NULL, (PBYTE) HardwareID, sizeof(HardwareID), NULL);

			memset(symbolic_link, 0, sizeof(symbolic_link));
			strncpy(symbolic_link, detail->DevicePath, sizeof(symbolic_link));

			free((PVOID) detail);
			ifdata.cbSize = sizeof(ifdata); // reinitialize for next use
		}

		SetupDiDestroyDeviceInfoList(hDevInfo);
    }

    return found_index;
}