wLogAppender* WLog_Appender_New(wLog* log, DWORD logAppenderType)
{
	wLogAppender* appender = NULL;

	if (logAppenderType == WLOG_APPENDER_CONSOLE)
	{
		appender = (wLogAppender*) WLog_ConsoleAppender_New(log);
	}
	else if (logAppenderType == WLOG_APPENDER_FILE)
	{
		appender = (wLogAppender*) WLog_FileAppender_New(log);
	}
	else if (logAppenderType == WLOG_APPENDER_BINARY)
	{
		appender = (wLogAppender*) WLog_BinaryAppender_New(log);
	}

	if (!appender)
		appender = (wLogAppender*) WLog_ConsoleAppender_New(log);

	appender->Layout = WLog_Layout_New(log);

	InitializeCriticalSectionAndSpinCount(&appender->lock, 4000);

	return appender;
}