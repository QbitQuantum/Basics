/* Retrieves the decimal point
 * Returns the decimal point string or -1 on error
 */
int libcstring_locale_get_decimal_point(
     void )
{
	int decimal_point         = -1;
#if defined( WINAPI )
	DWORD locale_data         = 0;
#else
	struct lconv *locale_data = NULL;
#endif

#if defined( WINAPI )
#if WINVER >= 0x0600
	if( GetLocaleInfoEx(
	     LOCALE_NAME_USER_DEFAULT,
	     LOCALE_SDECIMAL,
	     (LPWSTR) &locale_data,
	     sizeof( DWORD ) / sizeof( wchar_t ) ) == 0 )
	{
		return( -1 );
	}
#elif WINVER >= 0x0500
	if( GetLocaleInfoA(
	     LOCALE_USER_DEFAULT,
	     LOCALE_SDECIMAL,
	     (LPSTR) &locale_data,
	     sizeof( DWORD ) / sizeof( char ) ) == 0 )
	{
		return( -1 );
	}
#else
	if( libcstring_GetLocaleInfoA(
	     LOCALE_USER_DEFAULT,
	     LOCALE_SDECIMAL,
	     (LPSTR) &locale_data,
	     sizeof( DWORD ) / sizeof( char ) ) == 0 )
	{
		return( -1 );
	}
#endif
	decimal_point = (int) locale_data;
#else
	locale_data = localeconv();

	if( locale_data == NULL )
	{
		return( -1 );
	}
	if( locale_data->decimal_point == NULL )
	{
		return( -1 );
	}
	decimal_point = ( locale_data->decimal_point )[ 0 ];
#endif
	return( decimal_point );
}