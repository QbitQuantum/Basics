// EnumFontName の Windows 環境依存処理を行う関数
extern int EnumFontName_Win( ENUMFONTDATA *EnumFontData, int CharSet )
{
	HDC			hdc ;
	LOGFONTW	LogFont ;

	// デバイスコンテキストを取得
	hdc = GetDC( NULL );

	// 列挙開始
	memset( &LogFont, 0, sizeof( LOGFONTW ) ) ;
	LogFont.lfCharSet = ( BYTE )( CharSet < 0 ? DEFAULT_CHARSET : CharSetTable[ CharSet ] ) ;
	if( EnumFontData->EnumFontName != NULL )
	{
		CL_strncpy( CODEPAGE_UTF16LE, ( char * )LogFont.lfFaceName, ( char * )EnumFontData->EnumFontName, 31 ) ;
	}
	else
	{
		LogFont.lfFaceName[0] = L'\0' ;
	}
	LogFont.lfPitchAndFamily	= 0 ;
	EnumFontFamiliesExW( hdc, &LogFont, ( FONTENUMPROCW )EnumFontFamExProcEx, ( LPARAM )EnumFontData, 0  ) ;

	// デバイスコンテキストの解放
	ReleaseDC( NULL, hdc ) ;

	// 正常終了
	return 0 ;
}