TInt CFloggerTest012_01::DoTestWrite()
	{
	_LIT16(KTestMessageOne,"TEST 12.01: The value of test integer variable :%d"); //unicode test decriptor
	RFileLogger::WriteFormat(KStdSubsysTag8, KStdCompTag8, KTestMessageOne, 100);

	// connect so we can flush file buffer for heap check
	RFileLogger theFlogger;
	theFlogger.Connect();
	theFlogger.SetLogTags(KStdSubsysTag8, KStdCompTag8);
	ForceLogFlush(theFlogger);
	theFlogger.Close();	
	
	return KErrNone; 
	}