LOCAL_C void InitL()
	{
	TBuf<80> logFile(KLogFileName);

#if defined(__WINS__) && defined(__WINSCW__)
	logFile.Append(_L(".WINSCW"));
#elif(__WINS__)
	logFile.Append(_L(".WINS"));
#else
	logFile.Append(_L(".MARM"));
#endif

#if defined(_DEBUG)
	logFile.Append(_L(".DEB"));
#else
	logFile.Append(_L(".REL"));
#endif
	logFile.Append(_L(".LOG"));

	gTest.Printf(_L("\nLog File "));
	gTest.Printf(logFile);
	gTest.Printf(_L("\n"));
	log = CImLog::NewL(logFile, EAppend);
	CleanupStack::PushL(log);
	log->AppendComment(_L8("Test Results"));
	log->AppendComment(_L8("T_GMXMLFAILURE memory leak test in XMLParser"));
	log->AppendComment(_L8("Test 1 Starting"));
	}