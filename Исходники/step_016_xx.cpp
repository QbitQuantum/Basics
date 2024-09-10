TInt CFloggerTest016_01::DoTestWrite()
	{
	_LIT8(KTestMessageOne,"TC 16_01: The value of test integer variable :%d");
	DoTestWriteFormat(KTestMessageOne, 100);  //Write 8 bit formatted test descriptor

	// connect so we can flush file buffer for heap check since timer is killed in heap checks
	RFileLogger theFlogger;
	theFlogger.Connect();
	theFlogger.SetLogTags(KStdSubsysTag8, KStdCompTag8);
	ForceLogFlush(theFlogger);
	theFlogger.Close();
	return KErrNone; 
	}