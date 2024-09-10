//
// getMouseRawInputDevice
//
// Helper function that searches for a registered mouse raw input device. If
// found, the device parameter is filled with the information for the device
// and the function returns true.
//
bool getMouseRawInputDevice(RAWINPUTDEVICE& device)
{
	device.usUsagePage	= 0;
	device.usUsage		= 0;
	device.dwFlags		= 0;
	device.hwndTarget	= 0;

	// get the number of raw input devices
	UINT num_devices;
	GetRegisteredRawInputDevices(NULL, &num_devices, sizeof(RAWINPUTDEVICE));

	// create a buffer to hold the raw input device info
	RAWINPUTDEVICE* devices = new RAWINPUTDEVICE[num_devices];

	// look at existing registered raw input devices
	GetRegisteredRawInputDevices(devices, &num_devices, sizeof(RAWINPUTDEVICE));
	for (UINT i = 0; i < num_devices; i++)
	{
		// is there already a mouse device registered?
		if (devices[i].usUsagePage == HID_USAGE_PAGE_GENERIC &&
			devices[i].usUsage == HID_USAGE_GENERIC_MOUSE)
		{
			device.usUsagePage	= devices[i].usUsagePage;
			device.usUsage		= devices[i].usUsage;
			device.dwFlags		= devices[i].dwFlags;
			device.hwndTarget	= devices[i].hwndTarget;
			break;
		}
	}

    delete [] devices;

	return device.usUsagePage == HID_USAGE_PAGE_GENERIC &&
			device.usUsage == HID_USAGE_GENERIC_MOUSE;
}