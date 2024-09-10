TInt CFloggerTest028_Sync_ConWriteUni::executeStepL()
	{
	TInt ret;
	
	RFileLogger flogger;
	ret = flogger.Connect();
	
	if ( ret == KErrNone )
		{
		flogger.SetLogTags(KStdSubsysTag8, KStdCompTag8);
		flogger.ClearLog();
		flogger.Write(KTestMessage);
		flogger.Close();
		TRAPD(r, ret = DoTestCheckWriteL());
		if (r != KErrNone)
			ret = r;
		}
	
	return ret;		

	}