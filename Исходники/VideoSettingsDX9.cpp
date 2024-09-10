//Imago - 7/28/09 this function will return the adapter's Windows desktop refresh rate setting
				// used to set the maximum refresh rate and avoid any PnP issues (thanks Sgt_Baker)
int GetMaxRate(int index = 0)
{
    DISPLAY_DEVICEA dd;
    dd.cb = sizeof(DISPLAY_DEVICEA);

	if (!EnumDisplayDevicesA(NULL, index, &dd, 0))
    {
		debugf("1: EnumDisplayDevices failed:%d\n", GetLastError());
        return 60;
    }
 
    DISPLAY_DEVICEA monitor;
    monitor.cb = sizeof(DISPLAY_DEVICEA);
    if (!EnumDisplayDevicesA(dd.DeviceName, 0, &monitor, 0))
    {
		debugf("2: EnumDisplayDevices failed:%d\n", GetLastError());
		if (!EnumDisplayDevicesA(NULL, 0, &monitor, 0))	{
			debugf("22: EnumDisplayDevices failed:%d\n", GetLastError());
			return 60;
		}
	}
 
    DEVMODEA dm;
    dm.dmSize = sizeof(DEVMODEA);
 
    if (!EnumDisplaySettingsA(dd.DeviceName, ENUM_CURRENT_SETTINGS, &dm))
    {
		debugf("3: EnumDisplaySettings failed:%d\n", GetLastError());
        return 60;
    }
 
	debugf("Device string: %s\n", dd.DeviceString);
    debugf("Monitor ID: %s\n", monitor.DeviceID);
	debugf("Monitor name: %s\n", monitor.DeviceName);
	debugf("Monitor string: %s\n", monitor.DeviceString);
    debugf("Refresh rate, in hertz: %d\n", dm.dmDisplayFrequency);
    debugf("Color depth: %d\n", dm.dmBitsPerPel);
    debugf("Screen resolution, in pixels: %d x %d\n", 
        dm.dmPelsWidth, dm.dmPelsHeight);

	return dm.dmDisplayFrequency;
}