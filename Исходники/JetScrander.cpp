void sendMessage(LPCSTR lpszMessage) {
	HANDLE hMailSlot;
	WCHAR achUser[1024];
	WCHAR ach[1512];
	DWORD userSize = sizeof achUser;
	DWORD dwWritten;
	GetUserNameW(achUser, &userSize);
	CharLowerW(achUser);
	wsprintfW(ach, L"\\\\.\\mailslot\\MAZINGER_LAUNCHER_%s", achUser);
	hMailSlot = CreateFileW(ach, GENERIC_WRITE, FILE_SHARE_READ
			| FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	WriteFile(hMailSlot, lpszMessage, strlen(lpszMessage), &dwWritten,
			NULL);
	CloseHandle(hMailSlot);
}