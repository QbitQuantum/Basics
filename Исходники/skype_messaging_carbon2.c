int
IsSkypeRunning(void)
{
	OSStatus status = noErr;
	ProcessSerialNumber psn = {kNoProcess, kNoProcess};
	unsigned int procNameLength = 32;
	unsigned char procName[procNameLength];
	unsigned int i = 0;
	ProcessInfoRec info;
	info.processInfoLength = sizeof(ProcessInfoRec);
	info.processName = procName;
#if __LP64__
	info.processAppRef = NULL;
#else
	info.processAppSpec = NULL;
#endif
	pid_t pid = 0;
	
	while(status == noErr)
	{
		for(i = 0; i < procNameLength; i++)
			procName[i] = '\0';
		
		status = GetNextProcess(&psn);
		if (status == noErr)
		{
			if (GetProcessInformation(&psn, &info) == noErr)
			{
				//for some reason first character is poisioned
				if (g_str_equal((char *)&procName[1], "Skype"))
				{
					if (GetProcessPID(&psn, &pid) == noErr)
					{
						return (int)pid;
					}
				}
			}
		}
	}
	return 0;
}