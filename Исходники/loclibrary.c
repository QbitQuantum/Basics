int PathForResourceWithPathW (const wchar_t *path, const wchar_t *nm, 
								wchar_t *locFile, int locFileLen) {

	wchar_t tmpBuffer[TMP_BUF_SIZE];

	// build the path to the executable in the generic
	// resources folder, check there first
	swprintf(tmpBuffer, TMP_BUF_SIZE, L"%ls.Resources\\%ls", path, nm);

	if (!PathFileExistsW(tmpBuffer)) {
		// didn't hit generic resource folder, so need to get language codes
		_setLanguageIfNeeded();

		// test to see if localized directory exists, 
		// if so, we don't fall back if we don't find the file.
		swprintf(tmpBuffer, TMP_BUF_SIZE, 
				  L"%ls.Resources\\%S.lproj", path, isoLangCode);

		if (PathFileExistsW(tmpBuffer)) {
			swprintf(tmpBuffer, TMP_BUF_SIZE, L"%ls\\%ls", tmpBuffer, nm);

			if (!PathFileExistsW(tmpBuffer)) return 0;

			wcsncpy(locFile, tmpBuffer, locFileLen);
			return (int) wcslen(locFile);
		}

		// fall back on DEFAULT_LANG_CODE if still no good
		swprintf(tmpBuffer, TMP_BUF_SIZE, L"%ls.Resources\\%S.lproj\\%ls", 
			path, DEFAULT_LANG_CODE, nm);

		// we can't find the resource, so return 0
		if (!PathFileExistsW(tmpBuffer)) return 0;
	}
	
	wcsncpy(locFile, tmpBuffer, locFileLen);
	return (int) wcslen(locFile);


}