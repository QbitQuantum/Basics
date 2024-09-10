KUSB_HANDLE USBDevice::FindDevice()
{
	KLST_HANDLE DeviceList = NULL;
	KUSB_HANDLE handle = NULL;

	KLST_DEVINFO_HANDLE DeviceInfo = NULL;
	KLST_DEVINFO_HANDLE tmpDeviceInfo = NULL;

	ULONG deviceCount = 0;
	m_errorCode = ERROR_SUCCESS;

	// Get the device list
	if (!LstK_Init(&DeviceList, KLST_FLAG_NONE))
	{
#ifdef _DEBUG
		debugPrintf("ASIOUAC: Error initializing device list.\n");
#endif
		return NULL;
	}

	LstK_Count(DeviceList, &deviceCount);
	if (!deviceCount)
	{
#ifdef _DEBUG
		debugPrintf("ASIOUAC: No devices in device list.\n");
#endif
		SetLastError(ERROR_DEVICE_NOT_CONNECTED);
		// If LstK_Init returns TRUE, the list must be freed.
		LstK_Free(DeviceList);
		return NULL;
	}

#ifdef _DEBUG
	debugPrintf("ASIOUAC: Looking for device with DeviceInterfaceGUID %s\n", _T(_DeviceInterfaceGUID));
#endif
	LstK_MoveReset(DeviceList);
    //
    //
    // Call LstK_MoveNext after a LstK_MoveReset to advance to the first
    // element.
    while(LstK_MoveNext(DeviceList, &tmpDeviceInfo)
		&& DeviceInfo == NULL)
    {
		if(!_stricmp(tmpDeviceInfo->DeviceInterfaceGUID, _DeviceInterfaceGUID) && tmpDeviceInfo->Connected)
		{
			DeviceInfo = tmpDeviceInfo;
			break;
		}
    }

	if (!DeviceInfo)
	{
#ifdef _DEBUG
		debugPrintf("ASIOUAC: Device not found.\n");
#endif
		// If LstK_Init returns TRUE, the list must be freed.
		LstK_Free(DeviceList);
		return NULL;
	}

    // Initialize the device with the "dynamic" Open function
    if (!UsbK_Init(&handle, DeviceInfo))
    {
		handle = NULL;
        m_errorCode = GetLastError();
#ifdef _DEBUG
        debugPrintf("ASIOUAC: UsbK_Init failed. ErrorCode: %08Xh\n",  m_errorCode);
#endif
    }
	LstK_Free(DeviceList);
	return handle;
}