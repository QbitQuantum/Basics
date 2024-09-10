/*	erase to the end of current line */
void erase_eol()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (GetFileType(hStdOut) == FILE_TYPE_CHAR) {
		CONSOLE_SCREEN_BUFFER_INFO console_info;

		if (GetConsoleScreenBufferInfo(hStdOut, &console_info)) {
			DWORD result;

			FillConsoleOutputCharacter(
				hStdOut, ' ',
				console_info.dwSize.X - console_info.dwCursorPosition.X,
				console_info.dwCursorPosition,
				&result);
		}
	}
}