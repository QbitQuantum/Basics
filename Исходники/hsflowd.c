static bool initialiseProgramDataDir(wchar_t *path, size_t pathLen)
{
	PWSTR programData;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_ProgramData, 0, NULL, &programData))) {
		wcscpy_s(path, pathLen, programData);
		CoTaskMemFree(programData);
		if (initialiseDir(path, HSP_PUBLISHER)) {
			return initialiseDir(path, HSP_PRODUCT_NAME);
		}
	}
	return false;
}