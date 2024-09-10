// This function exists because sometimes IsAppThemed lies
BOOL CXpTheme::IsWindowThemed(HWND hWnd)
{_STT();
	if ( !IsAppThemed() ) return FALSE;

	// But sometimes IsAppThemed returns TRUE anyway so...
	CXpTheme xpthm( hWnd, "WINDOW" );
	return xpthm.IsTheme();
}