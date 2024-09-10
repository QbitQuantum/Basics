static BOOL RegisterForRawInputs()
{
	BOOL result = FALSE;
	PRAWINPUTDEVICELIST pRawInputDeviceList = NULL;
	do
	{
		BYTE data[2048];
		UINT dataSize;
		UINT nDevices;
		TCHAR vidStr[10];
		RAWINPUTDEVICE rawInputDevice;	
		
		if (GetRawInputDeviceList(NULL, &nDevices, sizeof(RAWINPUTDEVICELIST)) < 0)
		{
			printf("GetRawInputDeviceList failed to get device count. Error code 0x%08X.\n", GetLastError());		
			break;
		}

		pRawInputDeviceList = (PRAWINPUTDEVICELIST)malloc(sizeof(RAWINPUTDEVICELIST) * nDevices);
		if (NULL == pRawInputDeviceList)
		{
			printf("Malloc failed for pRawInputDeviceList.\n");	
			break;
		}

		nDevices = GetRawInputDeviceList(pRawInputDeviceList, (PUINT)&nDevices, sizeof(RAWINPUTDEVICELIST));
		if (nDevices < 0)
		{
			printf("GetRawInputDeviceList failed to get device list. Error code 0x%08X.\n", GetLastError());	
			break;
		}

		_stprintf_s(vidStr, sizeof(vidStr) / sizeof(TCHAR), _T("%04X"), HARDWARE_VID);
		for (UINT i = 0; i < nDevices; i++)
		{
			dataSize = 0;
			GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice, RIDI_DEVICENAME, data, &dataSize);
			GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice, RIDI_DEVICENAME, data, &dataSize);
			data[dataSize] = '\0';
			if ((_tcsstr((TCHAR*)data, vidStr) > 0))
			{	
				memcpy(&rawInputDeviceList, &pRawInputDeviceList[i], sizeof(rawInputDeviceList));
				break;
			}
		}

		memset(&rawInputDevice, 0, sizeof(rawInputDevice));
		rawInputDevice.dwFlags = RIDEV_INPUTSINK;
		rawInputDevice.hwndTarget = hWnd;
	
		/* Set "Usage" and "Usage Page" for mouse
         * https://msdn.microsoft.com/en-us/library/windows/hardware/ff543477(v=vs.85).aspx
		 */
		rawInputDevice.usUsagePage = DEVICE_USAGE_PAGE;
		rawInputDevice.usUsage     = DEVICE_USAGE;

		if (RegisterRawInputDevices(&rawInputDevice, 1, sizeof(rawInputDevice)))
		{
			result = TRUE;
			printf("Registered for raw inputs\n");
		}
		else
		{			
			printf("Registered for raw inputs failed. Error code 0x%08X.\n", GetLastError());
		}

	} while (false);

	if (NULL != pRawInputDeviceList)
	{
		free(pRawInputDeviceList);
	}
	
	return result;
}