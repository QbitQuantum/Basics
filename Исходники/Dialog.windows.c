string_t SaveFileDialog(const char *title, const char *filter) {
	OPENFILENAMEA ofn;
	char szPath[MAX_PATH];
	char szFile[MAX_PATH];

	memset(&ofn, 0, sizeof(ofn));
	memset(szPath, 0, sizeof(szPath));
	memset(szFile, 0, sizeof(szFile));

	GetCurrentDirectoryA(MAX_PATH, szPath);

	char *fixuped_filter = fixup_filter(filter);

	ofn.lStructSize = sizeof(OPENFILENAMEA);
	ofn.hwndOwner = NULL;
	ofn.lpstrInitialDir = szPath;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = fixuped_filter;
	ofn.lpstrTitle = title;
	ofn.Flags = OFN_EXPLORER | OFN_OVERWRITEPROMPT;

	if (GetSaveFileNameA(&ofn)) {
		free(fixuped_filter);
		return String.Create(szFile);
	} else {
		free(fixuped_filter);
		return String.Create(NULL);
	}
}