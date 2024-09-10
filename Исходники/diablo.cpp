HWND __fastcall diablo_find_window(LPCSTR lpClassName)
{
	HWND result; // eax
	HWND v2; // esi
	HWND v3; // eax
	HWND v4; // edi

	result = FindWindowA(lpClassName, 0);
	v2 = result;
	if ( result )
	{
		v3 = GetLastActivePopup(result);
		if ( v3 )
			v2 = v3;
		v4 = GetTopWindow(v2);
		if ( !v4 )
			v4 = v2;
		SetForegroundWindow(v2);
		SetFocus(v4);
		result = (HWND)1;
	}
	return result;
}