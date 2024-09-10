static VOID CALLBACK TrayIconAutoHideTimer(HWND hwnd, UINT, UINT_PTR idEvent, DWORD)
{
	KillTimer(hwnd, idEvent);
	HWND hwndClui = pcli->hwndContactList;
	HWND ActiveWindow = GetActiveWindow();
	if (ActiveWindow == hwndClui) return;
	if (CLUI_CheckOwnedByClui(ActiveWindow)) return;

	CListMod_HideWindow();
	SetProcessWorkingSetSize(GetCurrentProcess(), -1, -1);
}