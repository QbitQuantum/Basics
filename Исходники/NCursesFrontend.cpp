NCursesFrontend::NCursesFrontend()
{
	m_summary = true;
	m_fileList = true;

	m_showNzbname = g_Options->GetCursesNzbName();
	m_showTimestamp = g_Options->GetCursesTime();
	m_groupFiles = g_Options->GetCursesGroup();

	// Setup curses
#ifdef WIN32
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO ConsoleCursorInfo;
	GetConsoleCursorInfo(hConsole, &ConsoleCursorInfo);
	ConsoleCursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsole, &ConsoleCursorInfo);
	if (IsRemoteMode())
	{
		SetConsoleTitle("NZBGet - remote mode");
	}
	else
	{
		SetConsoleTitle("NZBGet");
	}
#else
	m_window = initscr();
	if (m_window == nullptr)
	{
		printf("ERROR: m_pWindow == nullptr\n");
		exit(-1);
	}
	keypad(stdscr, true);
	nodelay((WINDOW*)m_window, true);
	noecho();
	curs_set(0);
	m_useColor = has_colors();
#endif

	if (m_useColor)
	{
#ifndef WIN32
		start_color();
#endif
		init_pair(0,							COLOR_WHITE,	COLOR_BLUE);
		init_pair(NCURSES_COLORPAIR_TEXT,		COLOR_WHITE,	COLOR_BLACK);
		init_pair(NCURSES_COLORPAIR_INFO,		COLOR_GREEN,	COLOR_BLACK);
		init_pair(NCURSES_COLORPAIR_WARNING,	COLOR_MAGENTA,	COLOR_BLACK);
		init_pair(NCURSES_COLORPAIR_ERROR,		COLOR_RED,		COLOR_BLACK);
		init_pair(NCURSES_COLORPAIR_DEBUG,		COLOR_WHITE,	COLOR_BLACK);
		init_pair(NCURSES_COLORPAIR_DETAIL,		COLOR_GREEN,	COLOR_BLACK);
		init_pair(NCURSES_COLORPAIR_STATUS,		COLOR_BLUE,		COLOR_WHITE);
		init_pair(NCURSES_COLORPAIR_KEYBAR,		COLOR_WHITE,	COLOR_BLUE);
		init_pair(NCURSES_COLORPAIR_INFOLINE,	COLOR_WHITE,	COLOR_BLUE);
		init_pair(NCURSES_COLORPAIR_TEXTHIGHL,	COLOR_BLACK,	COLOR_CYAN);
		init_pair(NCURSES_COLORPAIR_CURSOR,		COLOR_BLACK,	COLOR_YELLOW);
		init_pair(NCURSES_COLORPAIR_HINT,		COLOR_WHITE,	COLOR_RED);
	}
}