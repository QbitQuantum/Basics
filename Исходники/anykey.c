/* Turn off buffering on stdin. */
void add_anykey(void)
{
#ifdef _WIN32
	stdin_handle = GetStdHandle(STD_INPUT_HANDLE);

	if (!GetConsoleMode(stdin_handle, &stdin_mode)) {
		/* TODO: Error handling. */
	}

	SetConsoleMode(stdin_handle, 0);
#else
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	memcpy(&term_orig, &term, sizeof(struct termios));
	term.c_lflag &= ~(ECHO | ICANON | ISIG);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &term);
#endif

	sr_session_source_add(STDIN_FILENO, G_IO_IN, -1, received_anykey, NULL);

	printf("Press any key to stop acquisition.\n");
}