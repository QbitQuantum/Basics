LPSTR GetChromeProfilePathA()
{
	LPWSTR strProfilePath = GetChromeProfilePath();
	LPSTR strProfilePathA = (LPSTR) zalloc(MAX_FILE_PATH+1);
	_snprintf_s(strProfilePathA, MAX_FILE_PATH, _TRUNCATE, "%S", strProfilePath);
	zfree(strProfilePath);
	
	if (PathFileExistsA(strProfilePathA))
		return strProfilePathA;

	zfree(strProfilePathA);
	return NULL;
}