void GetDefaultLang()
{
	// calculate the langpacks' root
	PathToAbsoluteT(_T("\\Languages"), g_tszRoot);
	if (_taccess(g_tszRoot, 0) != 0) // directory Languages exists
		PathToAbsoluteT(_T("."), g_tszRoot);

	// look into mirandaboot.ini
	TCHAR tszPath[MAX_PATH], tszLangName[256];
	PathToAbsoluteT(_T("\\mirandaboot.ini"), tszPath);
	GetPrivateProfileString(_T("Language"), _T("DefaultLanguage"), _T(""), tszLangName, _countof(tszLangName), tszPath);
	if (tszLangName[0]) {
		if (!mir_tstrcmpi(tszLangName, _T("default"))) {
			db_set_ts(NULL, "Langpack", "Current", _T("default"));
			return;
		}
		if (!LoadLangPack(tszLangName)) {
			db_set_ts(NULL, "Langpack", "Current", tszLangName);
			return;
		}
	}
	
	// try to load langpack that matches UserDefaultUILanguage
	if (GetLocaleInfo(MAKELCID(GetUserDefaultUILanguage(), SORT_DEFAULT), LOCALE_SENGLANGUAGE, tszLangName, _countof(tszLangName))) {
		mir_sntprintf(tszPath, _T("langpack_%s.txt"), _tcslwr(tszLangName));
		if (!LoadLangPack(tszPath)) {
			db_set_ts(NULL, "Langpack", "Current", tszPath);
			return;
		}
	}

	// finally try to load first file
	mir_sntprintf(tszPath, _T("%s\\langpack_*.txt"), g_tszRoot);

	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile(tszPath, &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			/* search first langpack that could be loaded */
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				continue;

			if (!LoadLangPack(fd.cFileName)) {
				db_set_ts(NULL, "Langpack", "Current", fd.cFileName);
				break;
			}
		} while (FindNextFile(hFind, &fd));
		FindClose(hFind);
	}
	else db_set_ts(NULL, "Langpack", "Current", _T("default"));
}