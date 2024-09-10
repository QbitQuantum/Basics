BOOL wbSetTabControlText(PWBOBJ pwboTab, LPCTSTR pszText)
{
	TCHAR *szTitle = _wcsdup(pszText);
	TCHAR *ptr;

	if(!pwboTab || !pwboTab->hwnd || !IsWindow(pwboTab->hwnd))
		return FALSE;

	if(!pszText || !*pszText)
		return FALSE;

	SendMessage(pwboTab->hwnd, TCM_DELETEALLITEMS, 0, 0);
	ptr = wcstok(szTitle, TEXT("\r\n,"));
	while(ptr) {
		wbCreateTabItem(pwboTab, ptr);
		ptr = wcstok(NULL, TEXT("\r\n,"));
	}
	return TRUE;
}