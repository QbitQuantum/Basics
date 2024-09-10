bool OpenLog()
{
	// open
	sLogFileName = C4CFN_Log; int iLog = 2;
#ifdef _WIN32
	while (!(C4LogFile = _fsopen(Config.AtUserDataPath(sLogFileName.getData()), "wt", _SH_DENYWR)))
#elif defined(HAVE_SYS_FILE_H)
	int fd = 0;
	while (!(fd = open(Config.AtUserDataPath(sLogFileName.getData()), O_WRONLY | O_CREAT, 0644)) || flock(fd, LOCK_EX|LOCK_NB))
#else
	while (!(C4LogFile = fopen(Config.AtUserDataPath(sLogFileName.getData()), "wb")))
#endif
	{
		// Already locked by another instance?
#if !defined(_WIN32) && defined(HAVE_SYS_FILE_H)
		if (fd) close(fd);
#else
		if (C4LogFile) fclose(C4LogFile);
#endif
		// If the file does not yet exist, the directory is r/o
		// don't go on then, or we have an infinite loop
		if (access(Config.AtUserDataPath(sLogFileName.getData()), 0))
			return false;
		// try different name
		sLogFileName.Format(C4CFN_LogEx, iLog++);
	}
#if !defined(_WIN32) && defined(HAVE_SYS_FILE_H)
	ftruncate(fd, 0);
	C4LogFile = fdopen(fd, "wb");
#endif
	// save start time
	time(&C4LogStartTime);
	return true;
}