TInt CFloggerTest025_BuildTestUrel4::executeStepL()
	{
	
	TInt ret;
	RFileLogger theFlogger;
	
	ret = theFlogger.Connect();
	
	if ( ret == KErrNone)
		{
		theFlogger.SetLogTags(KStdSubsysTag8, KStdCompTag8);
		theFlogger.ClearLog();
		theFlogger.Close();
	
		TestLog4::Test();
		ret = DoTestCheckWriteL();
		}

	return ret;		

	}