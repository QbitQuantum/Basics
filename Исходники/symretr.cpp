VOID _cdecl LogPrintf (char *format, ...)
{
	va_list va;
	char msg[512];
	int MsgLen;

	va_start (va, format);
	MsgLen = _vsnprintf (msg, sizeof(msg), format, va);

	for (char* sp = msg; *sp != 0; sp++)
	{
		if (sp[0] == '\n' && sp[-1] != '\r')
		{
			memmove (&sp[1], sp, strlen(sp)+1);
			sp[0] = '\r';
		}
	}
	MsgLen = strlen(msg);

	if (gszLog == NULL)
	{
		LogSize = 20;
		gszLog = (char*)LocalAlloc (LHND, LogSize);
	}

	if (LogLen + MsgLen + 1 > LogSize)
	{
		LogSize += 20;
		gszLog = (char*)LocalReAlloc ()
	}