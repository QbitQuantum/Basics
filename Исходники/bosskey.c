BOOL is_mozclass(HWND hwnd)
{
	WCHAR m_temp[VALUE_LEN+1] = {0};
	GetClassNameW(hwnd,m_temp,VALUE_LEN);
	return ( _wcsnicmp(m_temp,L"MozillaWindowClass",VALUE_LEN) ==0 ||
			 _wcsnicmp(m_temp,L"MozillaDialogClass",VALUE_LEN) ==0 ) ;
}