void BOT_INFO::resetSystemInfo()
{
	// CPU type
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	processor = si.dwProcessorType;

	// Windows registration name
	{
		char buffer[40];

		// Get platform
		OSVERSIONINFO osvi;
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(&osvi);
		Uint32 PlatformId = osvi.dwPlatformId;

		// Prepare for registry access
		HKEY key;			// Handle to a session with a registry key
		Uint32 buflen;		// Length of the buffer
		Uint32 type;		// Type will contain type of data transfered

		if (PlatformId != VER_PLATFORM_WIN32_NT)
		{
			// Look up Windows 9x or Windows 3.1 version information
			RegOpenKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion", (HKEY*)&key);
		}
		else
		{
			// Look up Windows NT version information
			RegOpenKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", (HKEY*)&key);
		}

		buflen = 40;
		RegQueryValueEx(key, "RegisteredOwner", NULL, &type, (BYTE*)&buffer, &buflen);
		strncpy(regName, buffer, 40);

		buflen = 40;
		RegQueryValueEx(key, "RegisteredOrganization", NULL, &type, (BYTE*)&buffer, &buflen);
		strncpy(regOrg, buffer, 40);

		RegCloseKey(key);
	}

	// Timezone Bias
	TIME_ZONE_INFORMATION tzi;
	GetTimeZoneInformation(&tzi);
	timeZoneBias = (SHORT)tzi.Bias;

	// Permission ID
	permissionID = getSetting32(HKEY_LOCAL_MACHINE, "SOFTWARE", "D2");

	// Install some SubSpace registry keys
	if (permissionID == -1)
	{
		do
		{
			permissionID = (GetTickCount() ^ 0xAAAAAAAA) * 0x5f346d + 0x5abcdef;
		}
		while (!permissionID || permissionID == 1 || permissionID == -1);

		setSetting32(HKEY_LOCAL_MACHINE, "SOFTWARE", "D2", permissionID);
	}

	// Machine ID
	GetVolumeInformation("C:\\", NULL, 0, &machineID, NULL, NULL, NULL, 0);

	if (!machineID || machineID == 1 || machineID == -1)
	{
		machineID = getSetting32(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion", "ProductCode");

		if (!machineID || machineID == 1 || machineID == -1)
		{
			machineID = permissionID;
			setSetting32(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion", "ProductCode", machineID);
		}
	}

	if (machineID > 0x7fffffff) machineID += 0x7fffffff;

	setSetting32(HKEY_LOCAL_MACHINE, "SOFTWARE", "D1", machineID);
}