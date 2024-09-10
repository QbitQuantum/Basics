BOOL I4C3DCursor::SetTransparentCursor(LPCTSTR szFilePath)
{
	HCURSOR hCursor = NULL;

	hCursor = LoadCursorFromFile(szFilePath);
	if (hCursor == NULL) {
		LoggingMessage(Log_Error, _T(MESSAGE_ERROR_CURSOR_MISSING), GetLastError(), g_FILE, __LINE__);

		return FALSE;
	}

	if (SetSystemCursor(hCursor, 32512)) {
		return TRUE;
	} else {
		RestoreCursor();
	}
	DestroyCursor(hCursor);	// 現在使用中のカーソルはDestroyすることはできない。

	return FALSE;
}