void BaseTest::MakeRootPath(LPWSTR path, LPCWSTR name)
{
	WCHAR filename[MAX_PATH];

	if (0 == path[0])
	{
		GetModuleFileNameW(NULL, filename, MAX_PATH);
		PathRemoveFileSpecW(filename);
		PathAppendW(filename, L"UnitTests.ini");

		lstrcpynW(path, filename, MAX_PATH);
		PathRemoveFileSpecW(path);		// bin\vc80\debug\tests
		PathRemoveFileSpecW(path);		// bin\vc80\debug
		PathRemoveFileSpecW(path);		// bin\vc80
		PathRemoveFileSpecW(path);		// bin
		PathAppendW(path, name);		// bin\name

		GetPrivateProfileStringW(L"Path", name, path, 
			path, MAX_PATH, filename);
		PathAddBackslashW(path);

		SetFileAttributesW(filename, FILE_ATTRIBUTE_NORMAL);
		WritePrivateProfileStringW(L"Path", name, path, filename);
	}
}