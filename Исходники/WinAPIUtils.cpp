bool ExploreToFile(CString path)
{
	bool success = false;
	HRESULT res = CoInitialize(NULL);

	if (res == S_OK || res == S_FALSE) {
		PIDLIST_ABSOLUTE pidl;

		if (SHParseDisplayName(path, NULL, &pidl, 0, NULL) == S_OK) {
			success = SUCCEEDED(SHOpenFolderAndSelectItems(pidl, 0, NULL, 0));
			CoTaskMemFree(pidl);
		}

		CoUninitialize();
	}

	return success;
}