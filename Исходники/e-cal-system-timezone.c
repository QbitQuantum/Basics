static gchar *
system_timezone_win32_query_registry (void)
{
	DWORD type;
	DWORD size;
	LONG res;
	DWORD i;

	static HKEY reg_key = (HKEY) INVALID_HANDLE_VALUE;
	static HKEY reg_subkey = (HKEY) INVALID_HANDLE_VALUE;
	gchar timeZone[MAX_VALUE_NAME] = "";
	gchar timeZoneStd[MAX_VALUE_NAME] = "";
	gchar subKey[MAX_VALUE_NAME] = "";

	res = RegOpenKeyExA (
		HKEY_LOCAL_MACHINE,
		"SYSTEM\\CurrentControlSet\\Control\\TimeZoneInformation", 0, KEY_READ, &reg_key);
	if (res != ERROR_SUCCESS) {
		g_debug ("Could not find system timezone! (1)\n");
		return NULL;
	}

	/* On Windows Vista, Windows Server 2008 and later, the Windows timezone name is the value of 'TimeZoneKeyName' */

	size = MAX_VALUE_NAME;
	res = RegQueryValueExA (reg_key, "TimeZoneKeyName", 0, &type, (LPBYTE) timeZone, &size);

	if (type == REG_SZ && res == ERROR_SUCCESS) {
		RegCloseKey (reg_key);
		g_debug ("Windows Timezone String (1): %s\n", timeZone);
		return g_strdup (timeZone);
	}

	/* On older Windows, we must first find the value of 'StandardName' */

	res = RegQueryValueExA (reg_key, "StandardName", 0, &type, (LPBYTE) timeZone, &size);

	if (type != REG_SZ || res != ERROR_SUCCESS) {
		RegCloseKey (reg_key);
		g_debug ("Could not find system timezone! (2)\n");
		return NULL;
	}

	RegCloseKey (reg_key);

	/* Windows NT and its family */
	res = RegOpenKeyExA (
		HKEY_LOCAL_MACHINE,
		"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Time Zones",
		0, KEY_READ, &reg_key);
	if (res != ERROR_SUCCESS) {
		g_debug ("Could not find the timezone! (3)\n");
		return NULL;
	}

	for (i = 0, res = ERROR_SUCCESS; res != ERROR_NO_MORE_ITEMS; i++) {
		size = MAX_VALUE_NAME;
		res = RegEnumKeyEx (reg_key, i, subKey, &size, NULL, NULL, NULL, NULL);
		if (res == ERROR_SUCCESS) {
			res = RegOpenKeyExA (reg_key, subKey, 0, KEY_READ, &reg_subkey);
			if (res != ERROR_SUCCESS)
				continue;
			size = MAX_VALUE_NAME;
			res = RegQueryValueExA (
				reg_subkey, "Std", 0, &type,
				(LPBYTE) timeZoneStd, &size);
			RegCloseKey (reg_subkey);
			if (type != REG_SZ || res != ERROR_SUCCESS) {
				continue;
			}
			if (g_strcmp0 (timeZone,timeZoneStd) == 0) {
				RegCloseKey (reg_key);
				g_debug ("Windows Timezone String (2): %s\n", subKey);
				return g_strdup (subKey);
			}
		}
	}

	g_debug ("Could not find system timezone! (3)\n");
	RegCloseKey (reg_key);
	return NULL;
}