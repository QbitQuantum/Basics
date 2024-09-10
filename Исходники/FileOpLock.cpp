FileOpLock::~FileOpLock()
{
	if (g_wait)
	{
		SetThreadpoolWait(g_wait, nullptr, nullptr);
		CloseThreadpoolWait(g_wait);
		g_wait = nullptr;
	}

	if (g_o.hEvent)
	{
		CloseHandle(g_o.hEvent);
		g_o.hEvent = nullptr;
	}

	if (g_hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(g_hFile);
		g_hFile = INVALID_HANDLE_VALUE;
	}
}