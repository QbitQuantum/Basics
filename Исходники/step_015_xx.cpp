TInt CFloggerTest015_03::DoTestWrite()
	{
	
	TInt ret = KErrNone;
	
	//8 bit test decriptor which is very long
	_LIT8(KTestLongMessage,"TEST 15.03: This is the long message This is the long message This is the long message This is the long message This is the long message This is the long message This is the long message This is the long message This is the long message This is the long message This is the long message"); //8 bit test decriptor
	
	RFileLogger theFlogger;

	ret = theFlogger.Connect(); //Just to clear the old log message
	if ( ret == KErrNone)
		ret = theFlogger.SetLogTags(KStdSubsysTag8, KStdCompTag8);
		if ( ret == KErrNone)
			ret = theFlogger.ClearLog();
			if ( ret == KErrNone)
				theFlogger.Close();

	if (ret == KErrNone)
	
	RFileLogger ::WriteFormat(KStdSubsysTag8, KStdCompTag8, KTestLongMessage);
		
	return KErrNone;
	}