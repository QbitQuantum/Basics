BOOL KCallInfocSend::_CheckFileFromReg( OUT std::wstring& strFilePath )
{
	WCHAR szInstallPath[MAX_PATH] = {0};
	if (!_ReadOneRegKey(szInstallPath, MAX_PATH))
		return FALSE;

	wcscat_s(szInstallPath, MAX_PATH, L"\\operation\\cas\\");
	wcscat_s(szInstallPath, MAX_PATH, defUPDATANAME);

	if (_waccess_s(szInstallPath, 0) == ENOENT)
		return FALSE;

	strFilePath = szInstallPath;
	return TRUE;
}