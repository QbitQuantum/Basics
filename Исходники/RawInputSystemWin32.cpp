	bool RawInputSystem::init()
	{
		initWinKeyTable();

#ifndef _EDITOR
		RAWINPUTDEVICE device;
		device.usUsagePage = 0x01;
		device.usUsage = 0x02;
		device.dwFlags = 0;
		device.hwndTarget = NULL;
		RegisterRawInputDevices(&device, 1, sizeof(device));
		DWORD error = GetLastError();

		UINT nDevices;
		PRAWINPUTDEVICELIST pRawInputDeviceList = PRAWINPUTDEVICELIST();
		GetRawInputDeviceList(pRawInputDeviceList, &nDevices, sizeof(RAWINPUTDEVICELIST));

		LOG_INFO("Total of " << nDevices << " input devices detected!");

		free(pRawInputDeviceList);
#endif

		return true;
	}