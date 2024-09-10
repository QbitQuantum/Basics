BOOL MyMoveFileA(LPCSTR lpszFileFrom, LPCSTR lpszFileto)
{
	if( !PathFileExistsA(lpszFileFrom) )
		return FALSE;
	if( PathFileExistsA(lpszFileto) )
		SetFileAttributesA(lpszFileto, FILE_ATTRIBUTE_NORMAL);
	
	DWORD dwFlags = GetFileAttributesA( lpszFileFrom );
	SetFileAttributesA(lpszFileFrom, FILE_ATTRIBUTE_NORMAL);
	BOOL bRet = MoveFileExA(lpszFileFrom, lpszFileto, MOVEFILE_REPLACE_EXISTING|MOVEFILE_COPY_ALLOWED);
	if(bRet)
		SetFileAttributesA(lpszFileto, dwFlags);
	return bRet;
}