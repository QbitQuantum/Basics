//----------------------------------------------------------------------------
// NAME: ConvertUTF16ToUTF8
// DESC: Converts Unicode UTF-16 (Windows default) text to Unicode UTF-8
//----------------------------------------------------------------------------
std::string CStringToStdString( IN const wchar_t * utf16 )
{
	//
	// Check input pointer
	//
	ATLASSERT( utf16 != NULL );
	if ( utf16 == NULL )
		AtlThrow( E_POINTER );


	//
	// Handle special case of empty string
	//
	if ( *utf16 == L'\0' )
	{
		return "";
	}


	//
	// Consider wchar_t's count corresponding to total string length,
	// including end-of-string (L'\0') character.
	//
	const int utf16Length = wcslen( utf16 ) + 1;


	//
	// Get size of destination UTF-8 buffer, in chars (= bytes)
	//
	int utf8Size = ::WideCharToMultiByte(
										CP_UTF8,	 // convert to UTF-8
										0,	 // default flags
										utf16,	 // source UTF-16 string
										utf16Length,	// total source string length, in wchar_t's,
										// including end-of-string \0
										NULL,	 // unused - no conversion required in this step
										0,	 // request buffer size
										NULL, NULL	 // unused
	);
	ATLASSERT( utf8Size != 0 );
	if ( utf8Size == 0 )
	{
		AtlThrowLastWin32();
	}


	//
	// Allocate destination buffer for UTF-8 string
	//
	std::vector< char > utf8Buffer( utf8Size );


	//
	// Do the conversion from UTF-16 to UTF-8
	//
	int result = ::WideCharToMultiByte(
										CP_UTF8,	 // convert to UTF-8
										0,	 // default flags
										utf16,	 // source UTF-16 string
										utf16Length,	// total source string length, in wchar_t's,
										// including end-of-string \0
										&utf8Buffer[0],	// destination buffer
										utf8Size,	 // destination buffer size, in bytes
										NULL, NULL	 // unused
										);	
	ATLASSERT( result != 0 );
	if ( result == 0 )
	{
		AtlThrowLastWin32();
	}


	//
	// Build UTF-8 string from conversion buffer
	//
	return std::string( &utf8Buffer[0] );
}