void IDebugLog::Open(const char * path)
{
	logFile = _fsopen(path, "w", _SH_DENYWR);

	if(!logFile)
	{
		UInt32	id = 0;
		char	name[1024];

		do
		{
			sprintf_s(name, sizeof(name), "%s%d", path, id);
			id++;

			logFile = NULL;
			logFile = _fsopen(name, "w", _SH_DENYWR);
		}
		while(!logFile && (id < 5));
	}
}