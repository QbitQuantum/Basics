LOCAL_C void Test4(TDesC& aRoot)
	{
// Clamp tests for non-writable file system
	test.Next(_L("T_DENYCLAMP - Test4()"));

	TBuf<256> pathName;	
#ifdef __WINS__
	if((aRoot[0]=='Z')||(aRoot[0]=='z'))
		pathName=_L("clean.txt");
	else
		pathName=_L("root.txt");
#else
	if((aRoot[0]=='Z')||(aRoot[0]=='z'))
		pathName=_L("UnicodeData.txt");
	else
		pathName=_L("\\Test\\clamp.txt");	// For (non-composite) ROFS drive
#endif
	RFile testFile;
	TInt r=testFile.Open(TheFs, pathName, EFileRead);
	test(r==KErrNone);

	// Attempt to clamp file
	RFileClamp handle;
	r=handle.Clamp(testFile);
	test(r==KErrPermissionDenied);

	// Unclamp file
	// Using an invalid-content cookie is OK - the request should
	// be rejected before the content is examined
	handle.iCookie[0]=MAKE_TINT64(-1,-1);
	handle.iCookie[1]=0;
	r=handle.Close(TheFs);
	test (r==KErrPermissionDenied);

	testFile.Close();
	}