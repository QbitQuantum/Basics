	void LFA_Rename ( const char * oldName, const char * newName )
	{
		std::string wideOldName, wideNewName;
		size_t utf8Len = strlen(oldName);
		if ( utf8Len < strlen(newName) ) utf8Len = strlen(newName);
		const size_t maxLen = 2 * (utf8Len+1);
		int wideLen;

		wideOldName.reserve ( maxLen );
		wideOldName.assign ( maxLen, ' ' );
		wideLen = MultiByteToWideChar ( CP_UTF8, 0, oldName, -1, (LPWSTR)wideOldName.data(), (int)maxLen );
		if ( wideLen == 0 ) LFA_Throw ( "LFA_Rename: MultiByteToWideChar failure", kLFAErr_ExternalFailure );

		wideNewName.reserve ( maxLen );
		wideNewName.assign ( maxLen, ' ' );
		wideLen = MultiByteToWideChar ( CP_UTF8, 0, newName, -1, (LPWSTR)wideNewName.data(), (int)maxLen );
		if ( wideLen == 0 ) LFA_Throw ( "LFA_Rename: MultiByteToWideChar failure", kLFAErr_ExternalFailure );

		BOOL ok = MoveFileW ( (LPCWSTR)wideOldName.data(), (LPCWSTR)wideNewName.data() );
		if ( ! ok ) LFA_Throw ( "LFA_Rename: MoveFileW failure", kLFAErr_ExternalFailure );

	}	// LFA_Rename