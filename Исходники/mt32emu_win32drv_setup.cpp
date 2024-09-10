void UnregisterDriver() {
	HKEY hReg;
	if (RegOpenKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Drivers32", &hReg)) {
		MessageBoxA(NULL, "Cannot open registry key", "Registry error", MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	char str[255];
	char drvName[] = "MIDI0";
	DWORD len, res;
	int mt32emuDriver = -1;
	for (int i = 0; i < 10; i++) {
		len = 255;
		if (i) {
			drvName[4] = '0' + i;
		} else {
			drvName[4] = 0;
		}
		res = RegQueryValueExA(hReg, drvName, NULL, NULL, (LPBYTE)str, &len);
		if (res != ERROR_SUCCESS) {
			continue;
		}
		if (!_stricmp(str, mt32emuDriverName)) {
			mt32emuDriver = i;
			res = RegDeleteValueA(hReg, drvName);
			if (res != ERROR_SUCCESS) {
				MessageBoxA(NULL, "Cannot uninstall MT32Emu MIDI driver", "Registry error", MB_OK | MB_ICONEXCLAMATION);
				RegCloseKey(hReg);
				return;
			}
		}
	}
	if (mt32emuDriver == -1) {
		MessageBoxA(NULL, "Cannot uninstall MT32Emu MIDI driver. There is no driver found.", "Error", MB_OK | MB_ICONEXCLAMATION);
		RegCloseKey(hReg);
		return;
	}
	MessageBoxA(NULL, "MT32Emu MIDI Driver successfully uninstalled.", "Information", MB_OK | MB_ICONINFORMATION);
	RegCloseKey(hReg);
}