int CUpdateRunner::ExtractUpdaterAndRun(wchar_t* lpCommandLine, bool useFallbackDir)
{
	PROCESS_INFORMATION pi = { 0 };
	STARTUPINFO si = { 0 };
	CResource zipResource;
	wchar_t targetDir[MAX_PATH];
	wchar_t logFile[MAX_PATH];
	std::vector<CString> to_delete;

	if (!useFallbackDir) {
		SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA, NULL, SHGFP_TYPE_CURRENT, targetDir);
	} else {
		wchar_t username[512];
		wchar_t uid[128];
		wchar_t appDataDir[MAX_PATH];
		ULONG unameSize = _countof(username);

		SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, SHGFP_TYPE_CURRENT, appDataDir);
		GetUserName(username, &unameSize);
		DWORD lastError = GetLastError();

		_swprintf_c(targetDir, _countof(targetDir), L"%s\\%s", appDataDir, username);

		if (!CreateDirectory(targetDir, NULL) && GetLastError() != ERROR_ALREADY_EXISTS) {
			wchar_t err[4096];
			_swprintf_c(err, _countof(err), L"Unable to write to %s - IT policies may be restricting access to this folder", targetDir);
			DisplayErrorMessage(CString(err), NULL);

			return -1;
		}
	}

	wcscat_s(targetDir, _countof(targetDir), L"\\SquirrelTemp");

	if (!CreateDirectory(targetDir, NULL) && GetLastError() != ERROR_ALREADY_EXISTS) {
		wchar_t err[4096];
		_swprintf_c(err, _countof(err), L"Unable to write to %s - IT policies may be restricting access to this folder", targetDir);

		if (useFallbackDir) {
			DisplayErrorMessage(CString(err), NULL);
		}

		goto failedExtract;
	}

	swprintf_s(logFile, L"%s\\SquirrelSetup.log", targetDir);

	if (!zipResource.Load(L"DATA", IDR_UPDATE_ZIP)) {
		goto failedExtract;
	}

	DWORD dwSize = zipResource.GetSize();
	if (dwSize < 0x100) {
		goto failedExtract;
	}

	BYTE* pData = (BYTE*)zipResource.Lock();
	HZIP zipFile = OpenZip(pData, dwSize, NULL);
	SetUnzipBaseDir(zipFile, targetDir);

	// NB: This library is kind of a disaster
	ZRESULT zr;
	int index = 0;
	do {
		ZIPENTRY zentry;
		wchar_t targetFile[MAX_PATH];

		zr = GetZipItem(zipFile, index, &zentry);
		if (zr != ZR_OK && zr != ZR_MORE) {
			break;
		}

		// NB: UnzipItem won't overwrite data, we need to do it ourselves
		swprintf_s(targetFile, L"%s\\%s", targetDir, zentry.name);
		DeleteFile(targetFile);

		if (UnzipItem(zipFile, index, zentry.name) != ZR_OK) break;
		to_delete.push_back(CString(targetFile));
		index++;
	} while (zr == ZR_MORE || zr == ZR_OK);

	CloseZip(zipFile);
	zipResource.Release();

	// nfi if the zip extract actually worked, check for Update.exe
	wchar_t updateExePath[MAX_PATH];
	swprintf_s(updateExePath, L"%s\\%s", targetDir, L"Update.exe");

	if (GetFileAttributes(updateExePath) == INVALID_FILE_ATTRIBUTES) {
		goto failedExtract;
	}

	// Run Update.exe
	si.cb = sizeof(STARTUPINFO);
	si.wShowWindow = SW_SHOW;
	si.dwFlags = STARTF_USESHOWWINDOW;

	if (!lpCommandLine || wcsnlen_s(lpCommandLine, MAX_PATH) < 1) {
		lpCommandLine = L"";
	}

	wchar_t cmd[MAX_PATH];
	swprintf_s(cmd, L"\"%s\" --install . %s", updateExePath, lpCommandLine);

	if (!CreateProcess(NULL, cmd, NULL, NULL, false, 0, NULL, targetDir, &si, &pi)) {
		goto failedExtract;
	}

	WaitForSingleObject(pi.hProcess, INFINITE);

	DWORD dwExitCode;
	if (!GetExitCodeProcess(pi.hProcess, &dwExitCode)) {
		dwExitCode = (DWORD)-1;
	}

	if (dwExitCode != 0) {
		DisplayErrorMessage(CString(
			L"There was an error while installing the application. " 
			L"Check the setup log for more information and contact the author."), logFile);
	}

	for (unsigned int i = 0; i < to_delete.size(); i++) {
		DeleteFile(to_delete[i]);
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return (int) dwExitCode;

failedExtract:
	if (!useFallbackDir) {
		// Take another pass at it, using C:\ProgramData instead
		return ExtractUpdaterAndRun(lpCommandLine, true);
	}

	DisplayErrorMessage(CString(L"Failed to extract installer"), NULL);
	return (int) dwExitCode;
}