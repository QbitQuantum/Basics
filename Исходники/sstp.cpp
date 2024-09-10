BOOL SSTP_Aviutl( HWND hWnd, LPCTSTR lpTitle )
{
#define SSTP_AVIUTL_BUF_SIZE 1024

	if( lstrlen( lpTitle ) > SSTP_AVIUTL_BUF_SIZE / 2 ) return FALSE;

	if( LANG_JAPANESE != PRIMARYLANGID( GetSystemDefaultLangID() ) ) return FALSE;

	SYSTEMTIME st;
	GetSystemTime( &st );
	if( (int) st.wMilliseconds > 350 ) return FALSE;


	char lpSjisStr[ SSTP_AVIUTL_BUF_SIZE ] = "";
	char lpSjisSakuraScript[ SSTP_AVIUTL_BUF_SIZE ] = "";

#ifdef _UNICODE
	BOOL bError = FALSE;
	WideCharToMultiByte(
		CP_SJIS,
		WC_NO_BEST_FIT_CHARS,
		lpTitle,
		-1,
		lpSjisStr,
		SSTP_AVIUTL_BUF_SIZE,
		"",
		&bError
	);
	if( bError ) return FALSE;
#else
	lstrcpyA( lpSjisStr, lpTitle );
#endif


	char * p = strchr( lpSjisStr, '%' );
	char * q = NULL;
	if( p == NULL )
	{
		int len = strlen( lpSjisStr );
		p = strstr( lpSjisStr, " (" );
		if( p == NULL ) return FALSE;
		*p = '\0';
		if( lstrlenA( lpSjisStr ) == len ) return FALSE;
		q = strchr( p + 1 , '/' );
		if( q == NULL ) return FALSE;

		int iFrames = atoi( q + 1 );
		if( iFrames == 0 ) return FALSE;
		int s1 = (int) floor( iFrames * 1001.0 / 30000.0 );
		int m1 = s1 / 60;
		s1 -= ( m1 * 60 );
		int s2 = (int) floor( iFrames * 1001.0 / 24000.0 );
		int m2 = s2 / 60;
		s2 -= ( m2 * 60 );
		sprintf( lpSjisSakuraScript, SSTP_AVIUTL_0, lpSjisStr, iFrames,
			m1, s1, m2, s2
		);
	}
	else
	{
		p = strstr( lpSjisStr, "] " );
		if( p == NULL ) return FALSE;
		q = strchr( lpSjisStr, '/' );
		if( q == NULL )	return FALSE;

		int iFrames = atoi( q + 1 );
		if( iFrames == 0 ) return FALSE;
		sprintf( lpSjisSakuraScript, SSTP_AVIUTL_1, p + 2, iFrames );
	}
	
	return DirectSSTP( hWnd, lpSjisSakuraScript );
}