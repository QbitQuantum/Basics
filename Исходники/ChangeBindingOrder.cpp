void FillDeviceInstanceId(HDEVINFO hDevHandle, SP_DEVINFO_DATA deviceInfoData, WCHAR *wAdapter)
{
	DWORD i;

	for (i = 0; SetupDiEnumDeviceInfo(hDevHandle, i, &deviceInfoData); i++)
	{
		BYTE buffer[BUFFER_SIZE];
		WCHAR deviceInfo[BUFFER_SIZE];
		DWORD dwProperty = 0; 

		memset(buffer, 0, BUFFER_SIZE);

		if (SetupDiGetDeviceRegistryProperty(hDevHandle, &deviceInfoData,
			SPDRP_DEVICEDESC , &dwProperty, buffer, BUFFER_SIZE, NULL) == TRUE)
		{
			wcscpy_s(deviceInfo, BUFFER_SIZE, (LPWSTR)buffer);

			if (wcscmp(wAdapter, deviceInfo) == 0)
			{
				RtlZeroMemory(wDeviceInstanceId, MAX_PATH);

				SetupDiGetDeviceInstanceId(hDevHandle, &deviceInfoData, wDeviceInstanceId, MAX_PATH, 0);
			}
		}
	}
} 