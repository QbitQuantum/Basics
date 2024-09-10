DBWin::DBWin(DWORD pid = -1)
{
	initialized = false;
	processId = pid;

	hMutex = OpenMutexW(SYNCHRONIZE, FALSE, L"DBWinMutex");
	if (!hMutex)
	{
		std::cerr << "Failed opening DBWinMutex" << std::endl;
		return;
	}

	hBufferReady = OpenEventW(EVENT_ALL_ACCESS, FALSE, L"DBWIN_BUFFER_READY");
	if (!hBufferReady)
	{
		hBufferReady = CreateEventW(nullptr, FALSE, TRUE, L"DBWIN_BUFFER_READY");
		if (!hBufferReady)
		{
			std::cerr << "Failed to open or create DBWIN_BUFFER_READY" << std::endl;
			return;
		}
	}

	hDataReady = OpenEventW(EVENT_ALL_ACCESS, FALSE, L"DBWIN_DATA_READY");
	if (!hDataReady)
	{
		hDataReady = CreateEventW(nullptr, FALSE, FALSE, L"DBWIN_DATA_READY");
		if (!hDataReady)
		{
			std::cerr << "Failed to open or create DBWIN_DATA_READY" << std::endl;
			return;
		}
	}

	hBuffer = OpenFileMappingW(FILE_MAP_READ, FALSE, L"DBWIN_BUFFER");
	if (!hBuffer)
	{
		hBuffer = CreateFileMappingW(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0,
			sizeof(dbwin_buffer), L"DBWIN_BUFFER");
		if (!hBuffer)
		{
			std::cerr << "Failed to open or create DBWIN_BUFFER" << std::endl;
			return;
		}
	}

	dbBuffer = static_cast<dbwin_buffer*>(MapViewOfFile(hBuffer, SECTION_MAP_READ, 0, 0, 0));
	if (!dbBuffer)
	{
		std::cerr << "Failed to map memory to dbBuffer" << std::endl;
		return;
	}

	initialized = true;
}