void WCharToChar( const wchar_t* pwstrSrc, char pstrDest[] )
{
	int nLen = ( int )wcslen( pwstrSrc );
	wcstombs( pstrDest, pwstrSrc, nLen + 1 );
}