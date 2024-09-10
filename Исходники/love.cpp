int w__openConsole(lua_State *L)
{
	static bool is_open = false;

	if (is_open)
	{
		love::luax_pushboolean(L, is_open);
		return 1;
	}

	is_open = true;

	// FIXME: we don't call AttachConsole in Windows XP because it seems to
	// break later AllocConsole calls if it fails. A better workaround might be
	// possible, but it's hard to find a WinXP system to test on these days...
	if (!IsWindowsVistaOrGreater() || !AttachConsole(ATTACH_PARENT_PROCESS))
	{
		// Create our own console if we can't attach to an existing one.
		if (!AllocConsole())
		{
			is_open = false;
			love::luax_pushboolean(L, is_open);
			return 1;
		}

		SetConsoleTitle(TEXT("LOVE Console"));

		const int MAX_CONSOLE_LINES = 5000;
		CONSOLE_SCREEN_BUFFER_INFO console_info;

		// Set size.
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &console_info);
		console_info.dwSize.Y = MAX_CONSOLE_LINES;
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), console_info.dwSize);
	}

	FILE *fp;

	// Redirect stdout.
	fp = freopen("CONOUT$", "w", stdout);
	if (L && fp == NULL)
		return luaL_error(L, "Console redirection of stdout failed.");

	// Redirect stdin.
	fp = freopen("CONIN$", "r", stdin);
	if (L && fp == NULL)
		return luaL_error(L, "Console redirection of stdin failed.");

	// Redirect stderr.
	fp = freopen("CONOUT$", "w", stderr);
	if (L && fp == NULL)
		return luaL_error(L, "Console redirection of stderr failed.");

	love::luax_pushboolean(L, is_open);
	return 1;
}