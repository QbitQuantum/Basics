		BOOL SysConsole::Open( int x, int y, int w, int h )
		{
			BOOL r = AllocConsole();

			if (!r)
				return r;
			AttachConsole(GetCurrentProcessId());
			MoveWindow(GetConsoleWindow(), x, y, w, h, true);
			m_cinbuf = std::cin.rdbuf();
			m_console_cin.open("CONIN$");
			std::cin.rdbuf(m_console_cin.rdbuf());
			m_coutbuf = std::cout.rdbuf();
			m_console_cout.open("CONOUT$");
			std::cout.rdbuf(m_console_cout.rdbuf());
			m_cerrbuf = std::cerr.rdbuf();
			m_console_cerr.open("CONOUT$");
			std::cerr.rdbuf(m_console_cerr.rdbuf());

			FILE *stream;
			freopen_s(&stream, "conin$", "r", stdin);
			freopen_s(&stream, "conout$", "w", stdout);
			freopen_s(&stream, "conout$", "w", stdout);

			return r;
		}