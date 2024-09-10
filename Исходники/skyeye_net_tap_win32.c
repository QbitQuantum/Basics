static int initDevice(struct net_device *net_dev)
{
	char device_path[256];
	char device_guid[0x100];
	char device_name[1024];

	ULONG tapVer[3];
	ULONG len = 0;

	tap_win32 *dev = (net_dev ? (tap_win32*)(net_dev->priv) : NULL);
	if(dev == NULL) return -1;
	bzero(dev, sizeof(tap_win32));

	if(get_device_guid(device_guid, sizeof(device_guid), device_name, sizeof(device_name)) != 0)
	{
		printm("ERROR: SkyEye requires a TAP-Win32 driver that is at least version %d.%d\n"
		       "Please install from http://prdownloads.sourceforge.net/openvpn/openvpn-2.0_beta2-install.exe\n",
		       TAP_WIN32_MIN_MAJOR, TAP_WIN32_MIN_MINOR);
		return -1;
	}

	if(GetVersion() < 0x80000000)
	{
		char hostip[16];

		sprintf(hostip, "%d.%d.%d.%d",
			net_dev->hostip[0], net_dev->hostip[1], net_dev->hostip[2], net_dev->hostip[3]);

		if(_spawnlp(_P_DETACH, "netsh.exe", "netsh.exe",
			    "interface", "ip", "set", "address", device_name,
			    "static", hostip, "255.255.255.0", NULL) == -1)
		{
			printm("WARNING: Failed to Change IP Address/Mask.\n");
		}
	}

	snprintf(device_path, sizeof(device_path), "%s%s%s", USERMODEDEVICEDIR, device_guid, TAPSUFFIX);

	dev->fHandle = CreateFile(device_path,
				  GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
				  NULL, OPEN_EXISTING,
				  FILE_ATTRIBUTE_SYSTEM | FILE_FLAG_OVERLAPPED, NULL);
	if(dev->fHandle == INVALID_HANDLE_VALUE)
	{
		printm("Opening TAP connection failed\n");
		return -1;
	}

	bzero(&tapVer[0], sizeof(tapVer));
	if(!DeviceIoControl(dev->fHandle, TAP_IOCTL_GET_VERSION,
			    &tapVer[0], sizeof(tapVer), &tapVer[0], sizeof(tapVer), &len, NULL))
	{
		ShowErrorMsg("Could not get driver version info");
		CloseHandle(dev->fHandle);
		return -1;
	}
	if(!(tapVer[0] > TAP_WIN32_MIN_MAJOR || (tapVer[0] == TAP_WIN32_MIN_MAJOR && tapVer[1] >= TAP_WIN32_MIN_MINOR)))
	{
		printm("ERROR: SkyEye requires a TAP-Win32 driver that is at least version %d.%d\n"
		       "Please install an updated version from http://prdownloads.sourceforge.net/openvpn/openvpn-2.0_beta2-install.exe\n",
		       TAP_WIN32_MIN_MAJOR, TAP_WIN32_MIN_MINOR);
		CloseHandle(dev->fHandle);
		return -1;
	}

	tapVer[0] = 1;
	if(!DeviceIoControl(dev->fHandle, TAP_IOCTL_SET_MEDIA_STATUS,
			    &tapVer[0], sizeof(ULONG), &tapVer[0], sizeof(ULONG), &len, NULL))
	{
		ShowErrorMsg("Setting Media Status to connected failed");
		CloseHandle(dev->fHandle);
		return -1;
	}

	InitializeCriticalSection(&dev->fLocker);
	dev->fEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	return 0;
}