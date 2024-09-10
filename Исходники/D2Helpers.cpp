void Log(char* szFormat, ...)
{
	va_list vaArgs;

	va_start(vaArgs, szFormat);
	int len = _vscprintf(szFormat, vaArgs);
	char* szString = new char[len+1];
	vsprintf_s(szString, len+1, szFormat, vaArgs);
	va_end(vaArgs);

	time_t tTime;
	time(&tTime);
	char szTime[128] = "";
	struct tm time;
	localtime_s(&time, &tTime);
	strftime(szTime, sizeof(szTime), "%x %X", &time);

	char path[_MAX_PATH+_MAX_FNAME] = "";
	sprintf_s(path, sizeof(path), "%sd2bs.log", Vars.szPath);

#ifdef DEBUG
	FILE* log = stderr;
#else
	FILE* log = _fsopen(path, "a+", _SH_DENYNO);
#endif
	fprintf(log, "[%s] D2BS %d: %s\n", szTime, GetProcessId(GetCurrentProcess()), szString);
#ifndef DEBUG
	fflush(log);
	fclose(log);
#endif
	delete[] szString;
}