void vncVideoDriver::Deactivate_NT50()
{
	HDESK   hdeskInput;
	HDESK   hdeskCurrent;
 
// it is important to us to be able to deactivate
// even what we have never activated. thats why we look it up, all over
//	if (!m_devname[0])
//		return;
// ... and forget the name
	*m_devname = 0;

	DISPLAY_DEVICE dd;
	INT devNum = 0;
	if (!LookupVideoDeviceAlt(szDriverString, szDriverStringAlt, devNum, &dd))
	{
		vnclog.Print(LL_INTERR, VNCLOG("No '%s' or '%s' found.\n"), szDriverString, szDriverStringAlt);
		return;
	}

	DEVMODE devmode;
	FillMemory(&devmode, sizeof(DEVMODE), 0);
	devmode.dmSize = sizeof(DEVMODE);
	devmode.dmDriverExtra = 0;
	BOOL change = EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devmode);
	devmode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	devmode.dmDeviceName[0] = '\0';

	HKEY hKeyDevice = CreateDeviceKey(szMiniportName);
	if (hKeyDevice == NULL)
		return;

    DWORD one = 0;
	if (RegSetValueEx(hKeyDevice,("Attach.ToDesktop"), 0, REG_DWORD, (unsigned char *)&one,4) != ERROR_SUCCESS)
	{
		vnclog.Print(LL_INTERR, VNCLOG("Can't set Attach.ToDesktop to 0x1\n"));
	}

// reverting to default behavior
	RegDeleteValue(hKeyDevice, ("Cap.DfbBackingMode"));
	RegDeleteValue(hKeyDevice, ("Order.BltCopyBits.Enabled"));

	pChangeDisplaySettingsEx pCDS = NULL;
	HINSTANCE  hInstUser32 = LoadNImport("User32.DLL", "ChangeDisplaySettingsExA", pCDS);
	if (!hInstUser32) return;

	// Save the current desktop
	hdeskCurrent = GetThreadDesktop(GetCurrentThreadId());
	if (hdeskCurrent != NULL)
	{
		hdeskInput = OpenInputDesktop(0, FALSE, MAXIMUM_ALLOWED);
		if (hdeskInput != NULL)
			SetThreadDesktop(hdeskInput);
	}
// 24 bpp screen mode is MUNGED to 32 bpp. see vncDesktop::ThunkBitmapInfo()
	if (devmode.dmBitsPerPel==24) devmode.dmBitsPerPel = 32;

	// Add 'Default.*' settings to the registry under above hKeyProfile\mirror\device
	(*pCDS)((TCHAR *)dd.DeviceName, &devmode, NULL, CDS_UPDATEREGISTRY, NULL);

	// Reset desktop
	SetThreadDesktop(hdeskCurrent);
	// Close the input desktop
	CloseDesktop(hdeskInput);
	RegCloseKey(hKeyDevice);
	FreeLibrary(hInstUser32);
}