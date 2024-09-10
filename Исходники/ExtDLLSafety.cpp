bool ExtDLL_CheckSafety()
{
	// check #1: NP validity
	NPAsync<NPGetPublisherFileResult>* async = NP_GetPublisherFile("hello_world.txt", (uint8_t*)helloWorld, sizeof(helloWorld));
	NPGetPublisherFileResult* result = async->Wait();

	if (result->result != GetFileResultOK)
	{
		MessageBoxA(NULL, "The IW4M extension DLL failed to load due to the master server lacking support for the functionality provided by this DLL.", "IW4M", MB_OK);
		return false;
	}

	// check #2: DLL signature
	if (!GAME_FLAG(GAME_FLAG_DEDICATED))
	{
		HMODULE iw4m = GetModuleHandleA("iw4m.dll");

		if (!iw4m)
		{
			return false;
		}

		wchar_t filename[MAX_PATH];
		GetModuleFileNameW(iw4m, filename, sizeof(filename) / 2);

		WINTRUST_FILE_INFO info;
		memset(&info, 0, sizeof(info));

		info.cbStruct = sizeof(info);
		info.pcwszFilePath = filename;
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
			MessageBoxA(NULL, va("The IW4M extension DLL failed to load due to a trust chain error. The specific error was 0x%x.", status), "IW4M", MB_OK);
			return false;
		}
	}

	return true;
}