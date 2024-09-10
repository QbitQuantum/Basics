/**
 * Checks if the 3D Mouse is connected
 * @return  returns 1 if the device is connected, 0 if the device is not connected, -1 if there is an error.
 */
int isDeviceConnected()
{
	UINT nDevices;
	PRAWINPUTDEVICELIST pRawInputDeviceList;

	if (GetRawInputDeviceList(NULL, &nDevices, sizeof(RAWINPUTDEVICELIST)) != 0) 
	{ 
		return -1;
	}

	if(nDevices<1)
	{
		return 0;
	}

	pRawInputDeviceList = new RAWINPUTDEVICELIST[nDevices];
	
	if (GetRawInputDeviceList(pRawInputDeviceList, &nDevices, sizeof(RAWINPUTDEVICELIST)) == (UINT) -1)
	{
		return -1;
	}

	bool found=false;

	for(int i=0;i<nDevices;i++)
	{
		RID_DEVICE_INFO rdi;
		rdi.cbSize= sizeof(rdi);
        UINT cbSize = sizeof(rdi);
		if(GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice, RIDI_DEVICEINFO, &rdi, &cbSize) > 0)
		{
			if (rdi.dwType == RIM_TYPEHID || rdi.hid.dwVendorId == LOGITECH_VENDOR_ID)
			{
				found=true;
				break;
			}
		}
	}


	delete[] pRawInputDeviceList;

	if(found)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}