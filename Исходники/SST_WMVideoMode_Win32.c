static int Win32_GetVideoModeOnScreen(SST_DisplayTarget target, size_t screenIndex, SST_VideoMode* vmodeReturn)
{
	SST_DisplayTarget_Win32* displayTarget = (SST_DisplayTarget_Win32*)target;
	const DISPLAY_DEVICEA* dev = &displayTarget->devs[screenIndex];
	DEVMODEA devMode;
	int ok = 0;

	devMode.dmSize = sizeof(devMode);

	if(EnumDisplaySettingsA(dev->DeviceName, ENUM_CURRENT_SETTINGS, &devMode))
	{
		vmodeReturn->bpp = devMode.dmBitsPerPel;
		vmodeReturn->width = devMode.dmPelsWidth;
		vmodeReturn->height = devMode.dmPelsHeight;
		vmodeReturn->refreshRate = devMode.dmDisplayFrequency;

		if(vmodeReturn->refreshRate == 1)
			vmodeReturn->refreshRate = SST_DEFAULT_REFRESHRATE;

		ok = 1;
	}

	return ok;
}