int simple_get_pass(char* passwd, size_t max_size){
    int ret = 0;
#if defined HAVE_TERMIOS_H
    struct termios old_term, new_term;
    FILE* stream = stdin;

    /* Turn echoing off and fail if we can't. */
    if (tcgetattr (fileno (stream), &old_term) != 0)
      return -1;
    new_term = old_term;
    new_term.c_lflag &= ~ECHO;
    if (tcsetattr (fileno (stream), TCSAFLUSH, &new_term) != 0)
      return -1;

    /* Read the password. */
    std::cin.getline(passwd, max_size);
    ret = strlen(passwd);

    /* Restore terminal. */
    (void) tcsetattr (fileno (stream), TCSAFLUSH, &old_term);

#elif HAVE_SETCONSOLEMODE
	HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	
	if (!GetConsoleMode(hstdin, &mode))
		return -1;

	if (hstdin == INVALID_HANDLE_VALUE || !(SetConsoleMode(hstdin, 0)))
		return -1; 
    std::cin.getline(passwd, max_size);
    ret = strlen(passwd);
	
	if (!SetConsoleMode(hstdin, mode))
		return -1;		
#else
    char* p;
    if((p = getpass("")) == NULL)
        return -1;
    *passwd = strdup(p);
    ret = strlen(p);
#endif
    return ret;

}