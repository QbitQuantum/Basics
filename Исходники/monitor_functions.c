int Monitor_Setup(void)
{
	EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, 0);

	if (monitor_count == 0)
		return 1;
	
	return 0;
}