std::vector<unicode_t> GetHomeUriWin()
{
	wchar_t homeDrive[0x100];
	wchar_t homePath[0x100];
	int l1 = GetEnvironmentVariableW( L"HOMEDRIVE", homeDrive, 0x100 );
	int l2 = GetEnvironmentVariableW( L"HOMEPATH", homePath, 0x100 );

	if ( l1 > 0 && l1 < 0x100 && l2 > 0 && l2 < 0x100 )
	{
		return carray_cat<unicode_t>( Utf16ToUnicode( homeDrive ).data(), Utf16ToUnicode( homePath ).data() );
	}

	return std::vector<unicode_t>();
}