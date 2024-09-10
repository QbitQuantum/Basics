INT countProcs(CONST std::wstring user) 
{
	if (debug)
		std::wcout << L"Counting all processes of user" << user << '\n';

	CONST WCHAR *wuser = user.c_str();
	INT numProcs = 0;

	HANDLE hProcessSnap, hProcess = NULL, hToken = NULL;
	PROCESSENTRY32 pe32;
	DWORD dwReturnLength, dwAcctName, dwDomainName;
	PTOKEN_USER pSIDTokenUser = NULL;
	SID_NAME_USE sidNameUse;
	LPWSTR AcctName, DomainName;

	if (debug)
		std::wcout << L"Creating snapshot" << '\n';

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
		goto die;

	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (debug)
		std::wcout << L"Grabbing first proccess" << '\n';

	if (!Process32First(hProcessSnap, &pe32))
		goto die;

	if (debug)
		std::wcout << L"Counting processes..." << '\n';

	do {
		if (debug)
			std::wcout << L"Getting process token" << '\n';

		//get ProcessToken
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pe32.th32ProcessID);
		if (!OpenProcessToken(hProcess, TOKEN_QUERY, &hToken)) 
			//Won't count pid 0 (system idle) and 4/8 (Sytem)
			continue;

		//Get dwReturnLength in first call
		dwReturnLength = 1;
		if (!GetTokenInformation(hToken, TokenUser, NULL, 0, &dwReturnLength)
			&& GetLastError() != ERROR_INSUFFICIENT_BUFFER) 
			continue;

		pSIDTokenUser = reinterpret_cast<PTOKEN_USER>(new BYTE[dwReturnLength]);
		memset(pSIDTokenUser, 0, dwReturnLength);

		if (debug)
			std::wcout << L"Received token, saving information" << '\n';

		//write Info in pSIDTokenUser
		if (!GetTokenInformation(hToken, TokenUser, pSIDTokenUser, dwReturnLength, NULL))
			continue;

		AcctName = NULL;
		DomainName = NULL;
		dwAcctName = 1;
		dwDomainName = 1;
		
		if (debug)
			std::wcout << L"Looking up SID" << '\n';

		//get dwAcctName and dwDomainName size
		if (!LookupAccountSid(NULL, pSIDTokenUser->User.Sid, AcctName,
			(LPDWORD)&dwAcctName, DomainName, (LPDWORD)&dwDomainName, &sidNameUse)
			&& GetLastError() != ERROR_INSUFFICIENT_BUFFER)
			continue;
		
		AcctName = reinterpret_cast<LPWSTR>(new WCHAR[dwAcctName]);
		DomainName = reinterpret_cast<LPWSTR>(new WCHAR[dwDomainName]);

		if (!LookupAccountSid(NULL, pSIDTokenUser->User.Sid, AcctName,
			(LPDWORD)&dwAcctName, DomainName, (LPDWORD)&dwDomainName, &sidNameUse))
			continue;

		if (debug)
			std::wcout << L"Comparing " << AcctName << L" to " << wuser << '\n';
		if (!wcscmp(AcctName, wuser)) {
			++numProcs;
			if (debug)
				std::wcout << L"Is process of " << wuser << L" (" << numProcs << L")" << '\n';
		}
		
		delete[] reinterpret_cast<LPWSTR>(AcctName);
		delete[] reinterpret_cast<LPWSTR>(DomainName);

	} while (Process32Next(hProcessSnap, &pe32));

die:
	if (hProcessSnap)
		CloseHandle(hProcessSnap);
	if (hProcess)
		CloseHandle(hProcess);
	if (hToken)
		CloseHandle(hToken);
	if (pSIDTokenUser)
		delete[] reinterpret_cast<PTOKEN_USER>(pSIDTokenUser);
	return numProcs;
}