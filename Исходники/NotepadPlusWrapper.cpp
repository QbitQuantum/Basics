void NotepadPlusWrapper::flashWindow(UINT count, DWORD milliseconds)
{
	FLASHWINFO flashinfo;
	flashinfo.cbSize = sizeof(flashinfo);
	flashinfo.hwnd = m_nppHandle;
	flashinfo.dwFlags = FLASHW_ALL;
	flashinfo.dwTimeout = milliseconds;
	flashinfo.uCount = count;

	FlashWindowEx(&flashinfo);
}