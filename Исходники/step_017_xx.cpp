TInt CFloggerTest017_05::DoTestWrite()
	{	
	RFileLogger theFlogger;
	TInt ret = KErrNone;
	
	ret = theFlogger.Connect(); //Just to clear the old log message
	if (ret == KErrNone)
		ret = theFlogger.SetLogTags(KStdSubsysTag8,KStdCompTag8);
		if (ret == KErrNone)
			ret = theFlogger.ClearLog();
			if (ret == KErrNone)
				theFlogger.Close();

	if (ret == KErrNone)
		{
		//Write the test datas in the hexa format
		RFileLogger::HexDump(KStdSubsysTag8,KStdCompTag8, KNullDesC8);
		return KErrNone;
		}
	return ret;
	}