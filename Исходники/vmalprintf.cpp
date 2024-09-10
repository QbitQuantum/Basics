LPWSTR DBGH_vmalprintfW( LPCWSTR pcszFormat, va_list list )
{
  bool  bSuccess = FALSE;

	LPWSTR pszBuffer = reinterpret_cast<LPWSTR>( malloc( g_knDefaultBufferSize * 2 ) );

	int nAllocated = g_knDefaultBufferSize;
	do
  {
		if( _vsnwprintf( pszBuffer, nAllocated - 1, pcszFormat, list ) < 0 )
	  {
			nAllocated *= 2;
			pszBuffer = reinterpret_cast<LPWSTR>( realloc( pszBuffer, nAllocated * 2 ) );
			if( !pszBuffer )
			{
				return NULL;
			}
	  }
    else
		{
      bSuccess = TRUE;
		}
  } while( !bSuccess );

	return pszBuffer;
}