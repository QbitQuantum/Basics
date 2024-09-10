TInt CFloggerTest011_01::DoTestWrite()
	{
	TInt ret = KErrNone;
	_LIT(KTestMessage,"TC 11_01: This is test messsage"); //unicode test decriptor

	RFileLogger theFlogger;

	//Just to clear the old log message
	ret = theFlogger.Connect(); 
	if ( ret == KErrNone)
		{
		ret = theFlogger.SetLogTags(KStdSubsysTag8, KStdCompTag8);
		if ( ret == KErrNone)
			{
			ret = theFlogger.ClearLog();
			}
		if ( ret == KErrNone)
			{
			theFlogger.Close();
			}
		}

	
	if ( ret == KErrNone)
		{
		// Test case
		RFileLogger::Write(KStdSubsysTag8, KStdCompTag8,KTestMessage);

		// reconnect so we can flush file buffer for heap check
		ret = theFlogger.Connect();
		if (ret == KErrNone)
			{
			theFlogger.SetLogTags(KStdSubsysTag8, KStdCompTag8);
			ForceLogFlush(theFlogger);
			theFlogger.Close();
			}
		}
	return ret;
	
	}