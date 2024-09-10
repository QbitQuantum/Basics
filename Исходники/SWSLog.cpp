void CSingletonLog::FlashLog(const char *msg, ...)
{
	if (!msg)
	{
		return;
	}
	va_list args;

	SYSTEMTIME tm;
	GetLocalTime(&tm);
	char LogTime[100];
	sprintf_s(LogTime, "%02d-%02d %02d:%02d:%02d:%03d ", tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);
	
	cs.lock();
	fopen_s(&fp, logName, "a");
	if (!fp)
	{
		return;
	}
	fprintf_s(fp, LogTime);
	va_start(args, msg);
	vfprintf_s(fp, msg, args);
	va_end(args);
//	fprintf_s(fp, "\n");
	fflush(fp);
	fclose(fp);
	fp = NULL;
	cs.unlock();
}