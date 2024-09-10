BOOL WINAPI GetFileVersionInfoU(
	LPCSTR lpstrFilename,
	DWORD dwHandle,
	DWORD dwLen,
	LPVOID lpData
)
{
	BOOL ret;
	WCHAR_T_DEC(lpstrFilename);
	WCHAR_T_CONV(lpstrFilename);
	ret = GetFileVersionInfoW(lpstrFilename_w, dwHandle, dwLen, lpData);
	WCHAR_T_FREE(lpstrFilename);
	return ret;
}