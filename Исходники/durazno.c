static
BOOL load_xinput_dll(HINSTANCE instance)
{
	char sysdir[MAX_PATH];
	char modname[MAX_PATH];
	UINT sysdir_len;
	DWORD modname_len;
	DWORD namepos;
	char *dllpath;
	
	sysdir_len = GetSystemDirectoryA(sysdir, MAX_PATH);
	if (sysdir_len == 0 || sysdir_len >= MAX_PATH) return FALSE;
	
	modname_len = GetModuleFileNameA(instance, modname, MAX_PATH);
	if (!modname_len) return FALSE;

	namepos = cheap_find_last_of(modname, '\\');
	dllpath = lstrcatA(sysdir, &modname[namepos]);
	if (!dllpath) return FALSE;

	XInput.dll = LoadLibraryA(dllpath);
	if (!XInput.dll) return FALSE;

	XInput.GetState = (t_XInputGetState)GetProcAddress(XInput.dll, "XInputGetState");
	XInput.SetState = (t_XInputSetState)GetProcAddress(XInput.dll, "XInputSetState");
	XInput.GetCapabilities = (t_XInputGetCapabilities)GetProcAddress(XInput.dll, "XInputGetCapabilities");
	XInput.Enable = (t_XInputEnable)GetProcAddress(XInput.dll, "XInputEnable");
	XInput.GetDSoundAudioDeviceGuids = (t_XInputGetDSoundAudioDeviceGuids)GetProcAddress(XInput.dll, "XInputGetDSoundAudioDeviceGuids");
	XInput.GetBatteryInformation = (t_XInputGetBatteryInformation)GetProcAddress(XInput.dll, "XInputGetBatteryInformation");
	XInput.GetKeystroke = (t_XInputGetKeystroke)GetProcAddress(XInput.dll, "XInputGetKeystroke");
	XInput.GetAudioDeviceIds = (t_XInputGetAudioDeviceIds)GetProcAddress(XInput.dll, "XInputGetAudioDeviceIds");

	XInput.GetStateEx = (t_XInputGetStateEx)GetProcAddress(XInput.dll, (LPCSTR)100);
	XInput.WaitForGuideButton = (t_XInputWaitForGuideButton)GetProcAddress(XInput.dll, (LPCSTR)101);
	XInput.CancelGuideButtonWait = (t_XInputCancelGuideButtonWait)GetProcAddress(XInput.dll, (LPCSTR)102);
	XInput.PowerOffController = (t_XInputPowerOffController)GetProcAddress(XInput.dll, (LPCSTR)103);
	XInput.GetBaseBusInformation = (t_XInputGetBaseBusInformation)GetProcAddress(XInput.dll, (LPCSTR)104);
	XInput.GetCapabilitiesEx = (t_XInputGetCapabilitiesEx)GetProcAddress(XInput.dll, (LPCSTR)108);

	return TRUE;
}