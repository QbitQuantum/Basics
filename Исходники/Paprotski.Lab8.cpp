void ShowMenuProcessPriority(HWND hWnd, DWORD processID)
{
	HANDLE hProcess;
	HMENU hPopupMenu;

	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, processID);
	if (hProcess == NULL || hWnd == NULL) return;

	saveProcessID = processID;

	DWORD priority = GetPriorityClass(hProcess);
	hPopupMenu = CreatePopupMenu();

	UINT flags;
	for (int i = 0; i < 6; i++)
	{
		flags = MF_BYPOSITION | MF_STRING | (priority == priorityArray[i] ? MF_CHECKED : MF_ENABLED);
		AppendMenu(hPopupMenu, flags, priorityArray[i], szPriorityName[i]);
	}
	SetForegroundWindow(hWnd);

	POINT point;
	GetCursorPos(&point);

	TrackPopupMenu(hPopupMenu, TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, 0, hWnd, NULL);
	DestroyMenu(hPopupMenu);
	CloseHandle(hProcess);
}