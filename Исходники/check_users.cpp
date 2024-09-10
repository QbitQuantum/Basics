INT check_users(printInfoStruct& printInfo) 
{
	DOUBLE users = 0;
	WTS_SESSION_INFOW *pSessionInfo = NULL;
	DWORD count;
	DWORD index;

	if (debug) 
		std::wcout << L"Trying to enumerate terminal sessions" << '\n';
	
	if (!WTSEnumerateSessions(WTS_CURRENT_SERVER_HANDLE, 0, 1, &pSessionInfo, &count)) {
		std::wcout << L"Failed to enumerate terminal sessions" << '\n';
		die();
		if (pSessionInfo)
			WTSFreeMemory(pSessionInfo);
		return 3;
	}

	if (debug)
		std::wcout << L"Got all sessions (" << count << L"), traversing and counting active ones" << '\n';

	for (index = 0; index < count; index++) {
		LPWSTR name;
		DWORD size;
		INT len;

		if (debug)
			std::wcout << L"Querrying session number " << index << '\n';

		if (!WTSQuerySessionInformation(WTS_CURRENT_SERVER_HANDLE, pSessionInfo[index].SessionId,
										WTSUserName, &name, &size))
			continue;

		if (debug)
			std::wcout << L"Found \"" << name << L"\". Checking whether it's a real session" << '\n';

		len = lstrlenW(name);

		WTSFreeMemory(name);

		if (!len)
			continue;
		
		if (pSessionInfo[index].State == WTSActive || pSessionInfo[index].State == WTSDisconnected) {
			users++;
			if (debug)
				std::wcout << L"\"" << name << L"\" is a real session, counting it. Now " << users << '\n';
		}
	}

	if (debug)
		std::wcout << "Finished coutning user sessions (" << users << "). Freeing memory and returning" << '\n';

	WTSFreeMemory(pSessionInfo);
	printInfo.users = users;
	return -1;
}