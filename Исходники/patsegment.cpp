//-------------------------------------------------------------------------------------
LPWSTR Sanitize(LPWSTR szString, WCHAR cReplace = L'-')
{
	//strip off invalid characters for a filename
	static LPCWSTR szInvalidCharacters = L"\\/:*?\"<>|";
	LPWSTR pPos;
	while ((pPos = wcspbrk(szString, szInvalidCharacters)) != NULL)
		*pPos = cReplace;
	//trim trailing spaces
	pPos = szString + wcslen(szString) - 1;
	while (pPos >= szString && (*pPos == L' ' || *pPos == L'\t'))
		*pPos-- = L'\0';
	//trim leading spaces
	pPos = szString;
	while (*pPos == L' ' || *pPos == L'\t')
		pPos++;
	return pPos;
}