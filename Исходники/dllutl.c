/*------------------------------------------------
  the windows is subclassified yet?
--------------------------------------------------*/
BOOL IsSubclassed(HWND hwnd)
{
	LONG_PTR wndproc1, wndproc2;
	
	wndproc1 = GetClassLongPtrW(hwnd, GCLP_WNDPROC);
	wndproc2 = GetWindowLongPtrW(hwnd, GWLP_WNDPROC);
	
	if(wndproc1 != wndproc2) return TRUE;
	return FALSE;
}