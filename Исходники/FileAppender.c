int WLog_FileAppender_Open(wLog* log, wLogFileAppender* appender)
{
	DWORD ProcessId;

	ProcessId = GetCurrentProcessId();

	if (!appender->FilePath)
	{
		appender->FilePath = GetKnownSubPath(KNOWN_PATH_TEMP, "wlog");
	}

	if (!PathFileExistsA(appender->FilePath))
	{
		CreateDirectoryA(appender->FilePath, 0);
		UnixChangeFileMode(appender->FilePath, 0xFFFF);
	}

	if (!appender->FileName)
	{
		appender->FileName = (char*) malloc(256);
		sprintf_s(appender->FileName, 256, "%u.log", (unsigned int) ProcessId);
	}

	if (!appender->FullFileName)
	{
		appender->FullFileName = GetCombinedPath(appender->FilePath, appender->FileName);
	}

	appender->FileDescriptor = fopen(appender->FullFileName, "a+");

	if (!appender->FileDescriptor)
		return -1;

	return 0;
}