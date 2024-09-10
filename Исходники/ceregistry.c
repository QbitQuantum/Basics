LONG 
XCERegDeleteValueA(
				HKEY hKey,	
				LPSTR lpszValue 	
				)
{
	LONG res;
	int len;
	WCHAR *lpszValueW;

	len = strlen(lpszValue);
	lpszValueW = alloca((len+1) * 2);
	MultiByteToWideChar(CP_ACP, 0, lpszValue, -1, lpszValueW, len+1);
	res = RegDeleteValueW(hKey, lpszValueW);

	return res;
}