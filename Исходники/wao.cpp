BOOL WinAPIOverride32Init(HINSTANCE hInst) {
	TCHAR psz[MAX_PATH+32];
	TCHAR pszPID[32];
	SYSTEM_INFO siSysInfo;

	DisableThreadLibraryCalls(hInst);

	dwCurrentProcessID = GetCurrentProcessId();

	wsprintf(pszPID, "0x%X", dwCurrentProcessID);
	lstrcpy(psz, APIOVERRIDE_MUTEX);
	lstrcat(psz, pszPID);

	pSingleInstance = new CSingleInstance(psz);
	if (pSingleInstance->IsAnotherInstanceRunning()) {
		delete pSingleInstance;
		return FALSE;
	}

	GetSystemInfo(&siSysInfo); 
	dwSystemPageSize = siSysInfo.dwPageSize;

	ApiOverrideHeap = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_GROWABLE, dwSystemPageSize, 0);

	pLinkListAPIInfos = new CLinkList(sizeof(API_INFO));
	pLinkListAPIInfos->SetHeap(ApiOverrideHeap);

	return TRUE;
}