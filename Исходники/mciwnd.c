/***********************************************************************
 *		MCIWndCreateW				[MSVFW32.@]
 */
HWND VFWAPIV MCIWndCreateW(HWND hwndParent, HINSTANCE hInstance,
			   DWORD dwStyle, LPCWSTR szFile)
{
   FIXME("%x %x %lx %s\n", hwndParent, hInstance, dwStyle, debugstr_w(szFile));

   MCIWndRegisterClass(hInstance);

   return 0;
}