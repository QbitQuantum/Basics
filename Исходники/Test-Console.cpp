int main()
{
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	PWSTR sUserSid = L"";
	HANDLE hToken = NULL;
	if (OpenThreadToken(GetCurrentThread(), TOKEN_QUERY, FALSE, &hToken)
		|| OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
	{
		if (!GetUserSidToken(hToken, &sUserSid))
		{
			printf("GetUserSid error: %d\n", GetLastError());
			return 1;
		}
		CloseHandle(hToken);
	}
	PWSTR sKeyHandle = L"";
	PWSTR sPublicKey = L"";
	PWSTR sChallenge = L"";
	PWSTR sHost = L"";
	PWSTR sPort = L"";
	PWSTR sUrl = L"";
	PWSTR sAppId = CRYSIL_APP_ID;

	std::cout << "Saved values in registry for current user" << std::endl;

	printf("UserSid: %ls\n", sUserSid);

	if (!Helper::Registry::GetRegValue(L"KeyHandle", &sKeyHandle, sUserSid))
	{
		printf("GetKeyHandle error");
		return false;
	}
	printf("KeyHandle: %ls\n", sKeyHandle);
	if (!Helper::Registry::GetRegValue(L"PublicKey", &sPublicKey, sUserSid))
	{
		printf("GetPublicKey error");
		return false;
	}
	if (!Helper::String::HexEncode(&sPublicKey))
	{
		printf("GetPublicKey error");
		return false;
	}
	printf("PublicKey: %ls\n", sPublicKey);
	if (!Helper::Registry::GetRegValue(L"Host", &sHost, sUserSid))
	{
		printf("GetHost error");
		return false;
	}
	printf("Host: %ls\n", sHost);
	if (!Helper::Registry::GetRegValue(L"Port", &sPort, sUserSid))
	{
		printf("GetPort error");
		return false;
	}
	printf("Port: %ls\n", sPort);
	if (!Helper::Registry::GetRegValue(L"URL", &sUrl, sUserSid))
	{
		printf("GetUrl error");
		return false;
	}
	printf("Url: %ls\n", sUrl);

	if (!Helper::Crypto::CreateRandomChallenge(&sChallenge))
	{
		printf("CreateRandomChallenge error");
		return false;
	}
	printf("Random challenge: %ls\n", sChallenge);	

	ConsolePinHandler pinHandler{};
	//WindowsPinHandler pinHandler{};
	//HWND hwndC = GetConsoleWindow();
	//g_hinst = GetModuleHandle(0);
	//pinHandler.setHwndOwner(hwndC);

	if (Helper::CrySIL::PerformU2FRequest(sUserSid, &pinHandler))
		printf("PerformU2FRequest: Success\n");
	else
		printf("PerformU2FRequest: Error\n");

	printf("Press any key to continue ...");
	_CrtDumpMemoryLeaks();
	getchar();
	return 0;
}