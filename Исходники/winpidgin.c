static void winpidgin_add_stuff_to_path() {
	wchar_t perl_path[MAX_PATH + 1];
	wchar_t *ppath = NULL;
	wchar_t mit_kerberos_path[MAX_PATH + 1];
	wchar_t *mpath = NULL;
	DWORD plen;

	printf("%s", "Looking for Perl... ");

	plen = sizeof(perl_path) / sizeof(wchar_t);
	if (read_reg_string(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Perl", L"",
			    (LPBYTE) &perl_path, &plen)) {
		/* We *could* check for perl510.dll, but it seems unnecessary. */
		wprintf(L"found in '%s'.\n", perl_path);

		if (perl_path[wcslen(perl_path) - 1] != L'\\')
			wcscat(perl_path, L"\\");
		wcscat(perl_path, L"bin");

		ppath = perl_path;
	} else
		printf("%s", "not found.\n");

	printf("%s", "Looking for MIT Kerberos... ");

	plen = sizeof(mit_kerberos_path) / sizeof(wchar_t);
	if (read_reg_string(HKEY_LOCAL_MACHINE, L"SOFTWARE\\MIT\\Kerberos", L"InstallDir",
			    (LPBYTE) &mit_kerberos_path, &plen)) {
		/* We *could* check for gssapi32.dll */
		wprintf(L"found in '%s'.\n", mit_kerberos_path);

		if (mit_kerberos_path[wcslen(mit_kerberos_path) - 1] != L'\\')
			wcscat(mit_kerberos_path, L"\\");
		wcscat(mit_kerberos_path, L"bin");

		mpath = mit_kerberos_path;
	} else
		printf("%s", "not found.\n");

	if (ppath != NULL || mpath != NULL) {
		const wchar_t *path = _wgetenv(L"PATH");
		BOOL add_ppath = ppath != NULL && (path == NULL || !wcsstr(path, ppath));
		BOOL add_mpath = mpath != NULL && (path == NULL || !wcsstr(path, mpath));
		wchar_t *newpath;
		int newlen;

		if (add_ppath || add_mpath) {
			/* Enough to add "PATH=" + path + ";"  + ppath + ";" + mpath + \0 */
			newlen = 6 + (path ? wcslen(path) + 1 : 0);
			if (add_ppath)
				newlen += wcslen(ppath) + 1;
			if (add_mpath)
				newlen += wcslen(mpath) + 1;
			newpath = malloc(newlen * sizeof(wchar_t));

			_snwprintf(newpath, newlen, L"PATH=%s%s%s%s%s%s",
				  path ? path : L"",
				  path ? L";" : L"",
				  add_ppath ? ppath : L"",
				  add_ppath ? L";" : L"",
				  add_mpath ? mpath : L"",
				  add_mpath ? L";" : L"");

			wprintf(L"New PATH: %s\n", newpath);

			_wputenv(newpath);
			free(newpath);
		}
	}
}