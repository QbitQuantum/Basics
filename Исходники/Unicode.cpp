CString Utf32ToUtf16( UChar32 const wch ) {
	UChar wchDest = L'\0';
	int cchDest = 1;

	UErrorCode errorCode = U_ZERO_ERROR;
	u_strFromUTF32( &wchDest, 1, &cchDest, &wch, 1, &errorCode );
	if ( U_STRING_NOT_TERMINATED_WARNING != errorCode ) {
		debug( L"Utf32ToUtf16/1: u_strFromUTF32 failed, errorCode=%d\n", errorCode );
		return CString( );
	} else {
		return CString( wchDest );
	}
}