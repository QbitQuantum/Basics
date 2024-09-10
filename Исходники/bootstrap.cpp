bool Bootstrap_UpdateEXE(int exeSize)
{
	const char* fn = _tempnam(NULL, "cup");
	CL_QueueDownload(va(CONTENT_URL "/%s/bootstrap/CitizenFX.exe.xz", GetUpdateChannel()), fn, exeSize, true);

	UI_DoCreation();

	if (!DL_RunLoop())
	{
		UI_DoDestruction();
		return false;
	}

	UI_DoDestruction();

	// verify the signature on the EXE
	wchar_t wfn[512];
	MultiByteToWideChar(CP_ACP, 0, fn, -1, wfn, 512);

	WINTRUST_FILE_INFO info;
	memset(&info, 0, sizeof(info));

	info.cbStruct = sizeof(info);
	info.pcwszFilePath = wfn;
	info.hFile = NULL;
	info.pgKnownSubject = NULL;

	GUID WVTPolicyGUID = WINTRUST_ACTION_GENERIC_VERIFY_V2;

	WINTRUST_DATA data;
	memset(&data, 0, sizeof(data));

	data.cbStruct = sizeof(data);
	data.pPolicyCallbackData = NULL;
	data.pSIPClientData = NULL;
	data.dwUIChoice = WTD_UI_NONE;
	data.fdwRevocationChecks = WTD_REVOKE_NONE;
	data.dwUnionChoice = WTD_CHOICE_FILE;
	data.dwStateAction = 0;
	data.hWVTStateData = NULL;
	data.pwszURLReference = NULL;
	data.dwUIContext = 0;
	data.pFile = &info;

	LONG status = WinVerifyTrust(NULL, &WVTPolicyGUID, &data);

	if (status != ERROR_SUCCESS)
	{
		//MessageBox(NULL, va(L"A trust chain error occurred in the downloaded rtcg.exe. The specific error code is 0x%08x.", status), L"O\x448\x438\x431\x43A\x430", MB_OK | MB_ICONSTOP);
		//return false;
	}

	wchar_t exePath[512];
	GetModuleFileName(GetModuleHandle(NULL), exePath, sizeof(exePath) / 2);

	STARTUPINFO startupInfo;
	memset(&startupInfo, 0, sizeof(startupInfo));
	startupInfo.cb = sizeof(startupInfo);
	startupInfo.wShowWindow = SW_HIDE;
	startupInfo.dwFlags |= STARTF_USESHOWWINDOW;

	PROCESS_INFORMATION processInfo;

	CreateProcess(wfn, (LPWSTR)va(L"%s -bootstrap \"%s\"", wfn, exePath), NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo);

	return false;
}