BOOL CDisplayAdapterHelper::InjectSpecificDllAndProcessByIdInner(DWORD dwProcessID, LPSTR lpDllName, BOOL bInjectSafeMode)
{
#if defined _M_X64 && _MSC_VER == 1800
	//workaround AVX2 bug in VS2013, http://connect.microsoft.com/VisualStudio/feedback/details/811093
	_set_FMA3_enable(0);
#endif
	
	assert(dwProcessID != 0);
	if (ISZERO(dwProcessID))
	{
		DOLOG("id of target process can't be zero !");
		return FALSE;
	}
	assert(ISNOTNULL(lpDllName));
	if(ISNULL(lpDllName))
	{
		DOLOG("name of dll can't not be null !");
		return FALSE;
	}

	CHAR cbDllPath[MAX_PATH] = { 0 };
	//if (ISZERO(GetCurrentDirectoryA(dirLen, cbDllPath)))
	if(ISZERO(GetModuleFileNameA(GetModuleHandle(NULL), cbDllPath, MAX_PATH)))
	{
		DOLOG("GetCurrentDirectory Failed ! " + GetLastError());
		return FALSE;
	}
	CHAR* lpFullPath = strrchr(cbDllPath, '\\');
	lpFullPath[1] = '\0';
	UINT dirLen = strlen(cbDllPath);
	const size_t fileNameLen = strlen(lpDllName);
	size_t len = dirLen + fileNameLen + 1;
	cbDllPath[dirLen - 1] = '\\';
	strncpy_s(cbDllPath + dirLen, len - dirLen, lpDllName, fileNameLen);

	BOOL result = TRUE;
	LoadSeDebugPrivilege();
	
	CNameEvent nameEvent;
	nameEvent.Init(EVENTNAME, TRUE);
	CNameShareMemory shareMemInst;

	shareMemInst.Init(SHAREMEMNAME, MAX_PATH, TRUE);
	char* lpInfo = shareMemInst.GetBuffer();
	ZeroMemory(lpInfo, MAX_PATH);

	if (!bInjectSafeMode)
	{
		OPPROC pOpenProcess;
		HANDLE hProcess;
		char pOPStr[12];
		int i;

		memcpy(pOPStr, "NpflUvhel{x", 12); //OpenProcess obfuscated
		for (i = 0; i<11; i++) pOPStr[i] ^= i ^ 1;

		pOpenProcess = (OPPROC)GetProcAddress(GetModuleHandle(TEXT("KERNEL32")), pOPStr);

		if (ISNULL(pOpenProcess))
		{
			DOLOG("GetProcAddress failed ! " + GetLastError());
			return FALSE;
		}

		hProcess = (*pOpenProcess)(PROCESS_ALL_ACCESS, FALSE, dwProcessID);

		if (ISNULL(hProcess))
		{
			DOLOG("OpenProcess Failed ! " + GetLastError());
			return FALSE;
		}
		if (ISFALSE(AdjustDllforProcess(hProcess, cbDllPath)))
		{
			DOLOG("AdjustDllforProcess Failed ! " + GetLastError());
			return FALSE;
		}

		if (ISNOTTRUE(InjectLibraryA(hProcess, cbDllPath, (DWORD)(len - 1))))
		{
			result = FALSE;
			DOLOG("Inject Library failed ! " + GetLastError());
		}

		CloseHandle(hProcess);
	}
	else
	{

#ifdef _WIN64
		CHAR cbTempDllPath[MAX_PATH] = { 0 };
		if (ISTRUE(AdjustDllfor64bit(cbTempDllPath, MAX_PATH, cbDllPath)))
		{
			memcpy(cbDllPath, cbTempDllPath, strlen(cbTempDllPath) + 1);
		}
#endif
		if (!InjectLibrarySafeA(dwProcessID, cbDllPath, (DWORD)(len - 1)))
		{
			DOLOG("InjectLibrarySafeA failed ! "+ GetLastError());
			result = FALSE;
		}
	}

	if(ISTRUE(nameEvent.Wait()))
	{
		lpInfo = shareMemInst.GetBuffer();
		if (ISNOTNULL(lpInfo))
		{
			DOLOG(" 得到的信息是>>>>>>" + lpInfo);
			strcpy(m_cbVideoAdapterName, lpInfo);
		}
	}
	nameEvent.Close();
	shareMemInst.Close();

	return result ;
}