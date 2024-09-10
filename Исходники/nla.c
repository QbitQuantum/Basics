rdpNla* nla_new(freerdp* instance, rdpTransport* transport, rdpSettings* settings)
{

	rdpNla* nla = (rdpNla*) calloc(1, sizeof(rdpNla));

	if (!nla)
		return NULL;

	nla->identity = calloc(1, sizeof(SEC_WINNT_AUTH_IDENTITY));
	if (!nla->identity)
	{
		free (nla);
		return NULL;
	}

	nla->instance = instance;
	nla->settings = settings;
	nla->server = settings->ServerMode;
	nla->transport = transport;
	nla->sendSeqNum = 0;
	nla->recvSeqNum = 0;
	nla->version = 3;

	ZeroMemory(&nla->negoToken, sizeof(SecBuffer));
	ZeroMemory(&nla->pubKeyAuth, sizeof(SecBuffer));
	ZeroMemory(&nla->authInfo, sizeof(SecBuffer));
	SecInvalidateHandle(&nla->context);

	if (nla->server)
	{
		LONG status;
		HKEY hKey;
		DWORD dwType;
		DWORD dwSize;

		status = RegOpenKeyExA(HKEY_LOCAL_MACHINE, SERVER_KEY,
					  0, KEY_READ | KEY_WOW64_64KEY, &hKey);

		if (status != ERROR_SUCCESS)
			return nla;

		status = RegQueryValueEx(hKey, _T("SspiModule"), NULL, &dwType, NULL, &dwSize);
		if (status != ERROR_SUCCESS)
		{
			RegCloseKey(hKey);
			return nla;
		}

		nla->SspiModule = (LPTSTR) malloc(dwSize + sizeof(TCHAR));
		if (!nla->SspiModule)
		{
			RegCloseKey(hKey);
			free(nla);
			return NULL;
		}

		status = RegQueryValueEx(hKey, _T("SspiModule"), NULL, &dwType,
								 (BYTE*) nla->SspiModule, &dwSize);

		if (status == ERROR_SUCCESS)
			WLog_INFO(TAG, "Using SSPI Module: %s", nla->SspiModule);

		RegCloseKey(hKey);
	}

	return nla;
}