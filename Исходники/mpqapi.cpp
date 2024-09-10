bool __fastcall mpqapi_set_hidden(char *pszArchive, bool hidden)
{
	char *v2; // edi
	BOOL v3; // esi
	DWORD v4; // eax
	bool result; // al
	DWORD v6; // esi

	v2 = pszArchive;
	v3 = hidden;
	v4 = GetFileAttributesA(pszArchive);
	if ( v4 == -1 )
		return GetLastError() == ERROR_FILE_NOT_FOUND;
	v6 = v3 != 0 ? FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_HIDDEN : 0;
	if ( v4 == v6 )
		result = 1;
	else
		result = SetFileAttributesA(v2, v6);
	return result;
}