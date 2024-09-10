int 
message(int id)
{
    if (!silent) {
	LPVOID lpMessageBuffer = NULL;
	TCHAR buf[256];
	TCHAR mess[256];
	DWORD error = GetLastError();
	LoadString(phInstance, id, mess, sizeof(mess)/sizeof(TCHAR)-1);
	wsprintf(buf, mess, error);

	if (error)
	    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, error, /* user default language */
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMessageBuffer, 0, NULL);
	if (lpMessageBuffer) {
	    lstrcat(buf, "\n");
	    lstrcat(buf, lpMessageBuffer);
	    LocalFree(LocalHandle(lpMessageBuffer));
	}

        MessageBox(HWND_DESKTOP, buf, title, MB_OK);
    }
    return 1; 
}