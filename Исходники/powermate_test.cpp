int _tmain(int argc, _TCHAR* argv[])
{
	BOOL b;
	UINT size = 0, i;
	RAWINPUTDEVICELIST *pRawInputDeviceList;

	b = GetRawInputDeviceList(NULL, &size, sizeof(RAWINPUTDEVICELIST));
	printf("b ==> %d, size ==> %d\n", b, size);

	pRawInputDeviceList = (RAWINPUTDEVICELIST *)malloc(sizeof(RAWINPUTDEVICELIST)* size);
	b = GetRawInputDeviceList(pRawInputDeviceList, &size, sizeof(RAWINPUTDEVICELIST));
	printf("b ==> %d, size ==> %d\n", b, size);
	for (i = 0; i < size; ++i)
	{
		WCHAR buffer[MAX_PATH + 1];

		printf("device.type ==> 0x%x\n", pRawInputDeviceList[i].dwType);
		printf("device.handle ==> 0x%p\n", pRawInputDeviceList[i].hDevice);

		UINT BufferSize = ARRAYSIZE(buffer);
		UINT retval = GetRawInputDeviceInfoW(pRawInputDeviceList[i].hDevice, RIDI_DEVICENAME, &buffer[0], &BufferSize);
		printf("retval ==> %d\n", retval);
		printf("buffer ==> %ws\n", buffer);

		RID_DEVICE_INFO DeviceInfo = { 0 };
		BufferSize = sizeof(DeviceInfo);
		retval = GetRawInputDeviceInfoW(pRawInputDeviceList[i].hDevice, RIDI_DEVICEINFO, &DeviceInfo, &BufferSize);
		printf("Device info.dwType ==> 0x%x\n", DeviceInfo.dwType);
		if (DeviceInfo.dwType == RIM_TYPEHID)
		{
			printf("usage page ==> 0x%x, usage ==> 0x%x\n", DeviceInfo.hid.usUsagePage, DeviceInfo.hid.usUsage);
		}
	}

	return 0;
}