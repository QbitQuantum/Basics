LRESULT CALLBACK vmsIeTabsHookFitter::_hookProc(int nCode, WPARAM wp, LPARAM lp)
{
	CWPSTRUCT *p = (CWPSTRUCT*)lp;
	if (p == NULL)
		return 0;

	DWORD dwWndThreadId = GetWindowThreadProcessId (p->hwnd, NULL);
	vmsTab *tab = vmsIeTabsHookFitter::o ().findTabByThreadId (dwWndThreadId);
	assert (tab != NULL);
	if (tab == NULL)
		return 0;

	if (nCode >= 0)
	{
		extern LRESULT CALLBACK _IeServerWndProc (HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
		_IeServerWndProc (p->hwnd, p->message, p->wParam, p->lParam);
	}
	
	return CallNextHookEx (tab->hHook, nCode, wp, lp);
}