BOOL CDemo_ClipView_VCDlg::GetThreadIdList(CList<int>& tIdList) {
	int pID = _getpid();
	HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
	THREADENTRY32 te32;
	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, pID);
	if (hThreadSnap == INVALID_HANDLE_VALUE) {
		return FALSE;
	}
	te32.dwSize = sizeof(THREADENTRY32);
	BOOL bGetThread = Thread32First(hThreadSnap, &te32);
	while (bGetThread) {
		if (te32.th32OwnerProcessID == pID) {
			tIdList.AddTail(te32.th32ThreadID);
		}
		bGetThread = Thread32Next(hThreadSnap, &te32);
	}
	CloseHandle(hThreadSnap);
	return TRUE;
}