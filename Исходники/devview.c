static LRESULT CALLBACK DevView_EditWndProc(HWND hwndEdit, UINT nMessage, WPARAM wParam, LPARAM lParam)
{
	struct DevViewInfo *pDevViewInfo;
	struct DevViewEntry *pEnt;
	LRESULT rc;
	HWND hwndDevView;
	LONG_PTR l;

	l = GetWindowLongPtr(hwndEdit, GWLP_USERDATA);
	pEnt = (struct DevViewEntry *) l;
	if (IsWindowUnicode(hwndEdit))
		rc = CallWindowProcW(pEnt->pfnEditWndProc, hwndEdit, nMessage, wParam, lParam);
	else
		rc = CallWindowProcA(pEnt->pfnEditWndProc, hwndEdit, nMessage, wParam, lParam);

	if (nMessage == WM_SETTEXT)
	{
		hwndDevView = GetParent(hwndEdit);
		pDevViewInfo = GetDevViewInfo(hwndDevView);
		DevView_TextChanged(hwndDevView, pEnt - pDevViewInfo->pEntries, (LPCTSTR) lParam);
	}
	return rc;
}