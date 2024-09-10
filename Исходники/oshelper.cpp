VDStringW VDGetLocalAppDataPath() {
	int csidl = CSIDL_APPDATA;

	HMODULE hmodShell32 = VDLoadSystemLibraryW32("shell32");

	if (hmodShell32) {
		typedef HRESULT (CALLBACK *tpDllGetVersion)(DLLVERSIONINFO *);

		DLLVERSIONINFO dvi = {sizeof(DLLVERSIONINFO)};

		tpDllGetVersion pDllGetVersion = (tpDllGetVersion)GetProcAddress(hmodShell32, "DllGetVersion");
		if (pDllGetVersion && NOERROR == pDllGetVersion(&dvi)) {
			if (dvi.dwMajorVersion >= 5)
				csidl = CSIDL_LOCAL_APPDATA;
		}

		FreeLibrary(hmodShell32);
	}

	if (VDIsWindowsNT()) {
		wchar_t pathW[MAX_PATH];

		if (!SHGetSpecialFolderPathW(NULL, pathW, csidl, FALSE))
			return VDGetProgramPath();

		return VDStringW(pathW);
	} else {
		char pathA[MAX_PATH];

		if (!SHGetSpecialFolderPathA(NULL, pathA, csidl, FALSE))
			return VDGetProgramPath();

		return VDTextAToW(pathA);
	}
}