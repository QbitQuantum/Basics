void ErrorLog::Log(eqLogType type, const char *message, ...)
{
	if(type >= _log_largest_type)
	{
		return;
	}

	va_list argptr;
	char *buffer = new char[4096];
	va_start(argptr, message);
	vsnprintf(buffer, 4096, message, argptr);
	va_end(argptr);

	time_t m_clock;
	struct tm *m_time;
	time(&m_clock);
	m_time = localtime(&m_clock);

	log_mutex->lock();

#ifdef _WINDOWS
	//system("color 0F");
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD color = WHITE;

	if (type == log_debug)			{ color = LIGHTGRAY; }
	if (type == log_error)			{ color = RED; }
	if (type == log_database)		{ color = LIGHTGREEN; }
	if (type == log_database_trace)	{ color = GREEN; }
	if (type == log_database_error)	{ color = LIGHTRED; }
	if (type == log_network)		{ color = YELLOW; }
	if (type == log_network_trace)	{ color = LIGHTBLUE; }
	if (type == log_network_error)	{ color = LIGHTRED; }
	if (type == log_world)			{ color = YELLOW; }
	if (type == log_world_trace)	{ color = LIGHTBLUE; }
	if (type == log_world_error)	{ color = LIGHTRED; }
	if (type == log_client)			{ color = YELLOW; }
	if (type == log_client_trace)	{ color = LIGHTBLUE; }
	if (type == log_client_error)	{ color = LIGHTRED; }

	std::string eqLogConsoleFormat = std::string(eqLogTypes[type]);
	std::string addspace = " ";

	while (eqLogConsoleFormat.length() < 14)
	{
		eqLogConsoleFormat += addspace;
	}

	CONSOLE_FONT_INFOEX info = { 0 };
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = 12; // leave X as zero
	info.FontWeight = FW_NORMAL;
	wcscpy(info.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx(hStdOut, NULL, &info);
	SetConsoleTextAttribute(hStdOut, color);
	printf("[ %s ][ %02d.%02d.%02d - %02d:%02d:%02d ] %s\n",
		eqLogConsoleFormat.c_str(),
		m_time->tm_mon + 1,
		m_time->tm_mday,
		m_time->tm_year % 100,
		m_time->tm_hour,
		m_time->tm_min,
		m_time->tm_sec,
		buffer);
	SetConsoleTextAttribute(hStdOut, color);
#else

	printf("[ %s ][ %02d.%02d.%02d - %02d:%02d:%02d ] %s\n",
		eqLogTypes[type],
		m_time->tm_mon+1,
		m_time->tm_mday,
		m_time->tm_year%100,
		m_time->tm_hour,
		m_time->tm_min,
		m_time->tm_sec,
		buffer);
#endif

	if(error_log)
	{
		fprintf(error_log, "[ %s ] [ %02d.%02d.%02d - %02d:%02d:%02d ] %s\n",
			eqLogTypes[type],
			m_time->tm_mon+1,
			m_time->tm_mday,
			m_time->tm_year%100,
			m_time->tm_hour,
			m_time->tm_min,
			m_time->tm_sec,
			buffer);
		fflush(error_log);
	}

	log_mutex->unlock();
	delete[] buffer;
}