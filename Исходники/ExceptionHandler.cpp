bool OverrideRPTDirectory(char *newPath)
{
# if defined(WZ_CC_MINGW)
	wchar_t buf[MAX_PATH];

	if (!MultiByteToWideChar(CP_UTF8, 0, newPath, -1, buf, MAX_PATH))
	{
		//conversion failed-- we won't use the user's directory.

		LPVOID lpMsgBuf;
		DWORD dw = GetLastError();
		TCHAR szBuffer[4196];

		FormatMessage(
		    FORMAT_MESSAGE_ALLOCATE_BUFFER |
		    FORMAT_MESSAGE_FROM_SYSTEM |
		    FORMAT_MESSAGE_IGNORE_INSERTS,
		    NULL,
		    dw,
		    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		    (LPTSTR) &lpMsgBuf,
		    0, NULL);

		wsprintf(szBuffer, _T("Exception handler failed setting new directory with error %d: %s\n"), dw, lpMsgBuf);
		MessageBox((HWND)MB_ICONEXCLAMATION, szBuffer, _T("Error"), MB_OK);

		LocalFree(lpMsgBuf);

		return false;
	}
	PathRemoveFileSpecW(buf);
	wcscat(buf, L"\\logs\\"); // stuff it in the logs directory
	wcscat(buf, L"Warzone2100.RPT");
	ResetRPTDirectory(buf);
#elif defined(WZ_OS_UNIX) && !defined(WZ_OS_MAC)
	sstrcpy(WritePath, newPath);
#endif
	return true;
}