/* Read console events until there is a key event.  Also returns on any error. */
static void wait_for_console_key(void)
{
	HANDLE hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);

	if (!ELEM(hConsoleInput, NULL, INVALID_HANDLE_VALUE) && FlushConsoleInputBuffer(hConsoleInput)) {
		for (;;) {
			INPUT_RECORD buffer;
			DWORD ignored;

			if (!ReadConsoleInput(hConsoleInput, &buffer, 1, &ignored)) {
				break;
			}

			if (buffer.EventType == KEY_EVENT) {
				break;
			}
		}
	}
}