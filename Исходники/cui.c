/*
* cuiPrintTextW
*
* Purpose:
*
* Output text to the console or file.
* UNICODE version.
*
*/
VOID cuiPrintTextW(
	_In_ LPWSTR lpText,
	_In_ BOOL UseReturn
	)
{
	SIZE_T consoleIO;
	DWORD bytesIO;
	LPWSTR Buffer;

	if (lpText == NULL)
		return;

	consoleIO = _strlen_w(lpText);
	if ((consoleIO == 0) || (consoleIO > MAX_PATH * 4))
		return;

	consoleIO = consoleIO * sizeof(WCHAR) + 4 + sizeof(UNICODE_NULL);
	Buffer = (LPWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, consoleIO);
	if (Buffer) {

		_strcpy(Buffer, lpText);
		if (UseReturn) _strcat_w(Buffer, TEXT("\r\n"));

		consoleIO = _strlen_w(Buffer);

		if (g_ConsoleOutput != FALSE) {
			WriteConsoleW(g_ConOut, Buffer, (DWORD)consoleIO, &bytesIO, NULL);
		}
		else {
			WriteFile(g_ConOut, Buffer, (DWORD)(consoleIO * sizeof(WCHAR)), &bytesIO, NULL);
		}
		HeapFree(GetProcessHeap(), 0, Buffer);
	}
}