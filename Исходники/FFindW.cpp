// ---
WCHAR *CAvpFileFindW::GetFileTitle() const {
	CAPointer<WCHAR> strFullName = GetFileName();
	CPathStrW strResult(_MAX_PATH);

#if defined(_UNICODE)
	_tsplitpath(strFullName, NULL, NULL, strResult, NULL);
#else
	if ( g_bUnicodePlatform )
		_wsplitpath(strFullName, NULL, NULL, strResult, NULL);
	else {
		CAPointer<char> pConverted =::UnicodeToMbcs( strFullName );
		CPathStr strAResult(_MAX_PATH);
		_splitpath(pConverted, NULL, NULL, strAResult, NULL);
		::MbcsToUnicode( strAResult, strResult, _MAX_PATH );
	}
#endif
	
	return strResult.Relinquish();
}