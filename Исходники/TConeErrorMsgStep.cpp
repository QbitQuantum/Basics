/**
	Utility function to setup and start TErrMsgApp for the display of the 
	error dialogs when the App leaves due to a call to CCoeEnv::LeaveWithErrorText()
 */
void CConeErrorMsgTestAppUi::TestErrorDialogL(const TDesC8& aTestCaseName,
			const TDesC& aTestCompareMbm,
			const TDesC* aDbgBmp,
			const TDesC* aDbgConvBmp,
			const TDesC* aDbgConvCompBmp,
			const TDesC* aDbgMbm)
	{
	_LIT(KExeName,"z:\\sys\\bin\\TErrMsgApp.EXE");
	RProcess process; 
	TRequestStatus status;
	TPtrC8 tailEnd;
	tailEnd.Set(aTestCaseName); 
	
	// create and configure command line, with test case name in
	// the tail end to be used by TErrMsgApp to determine what
	// information is displayed in the error dialog
 	CApaCommandLine* cmdLine=CApaCommandLine::NewLC();
	User::LeaveIfError(process.Create(KExeName, KNullDesC));
	CleanupClosePushL(process);
	cmdLine->SetExecutableNameL(KExeName);
	cmdLine->SetTailEndL(tailEnd);
	cmdLine->SetProcessEnvironmentL(process);
	status =  KRequestPending;
	process.Logon(status);
	process.Resume();
	
	// allow the host process to start and display a dialog
	User::After(1000000);
	
	// screen capture
	CFbsBitmap* screenBitmap=new(ELeave) CFbsBitmap();
	CleanupStack::PushL(screenBitmap);
	User::LeaveIfError(iWs.Connect());
	CWsScreenDevice *actualScreen;
	actualScreen=new(ELeave) CWsScreenDevice(iWs);
	CleanupStack::PushL(actualScreen);
	User::LeaveIfError(actualScreen->Construct(0));
	TSize screenSize=actualScreen->SizeInPixels();
	TDisplayMode screenDisplayMode = actualScreen->DisplayMode();
	User::LeaveIfError(screenBitmap->Create(screenSize, screenDisplayMode));
	User::LeaveIfError(actualScreen->CopyScreenToBitmap(screenBitmap));
	screenBitmap->Save(_L("c:\\screen.mbm"));

	// load in expected bmp for comparison
	CFbsBitmap* compareBitmap=new(ELeave) CFbsBitmap();
	CleanupStack::PushL(compareBitmap);
	TInt loadErr = compareBitmap->Load(aTestCompareMbm);
	INFO_PRINTF3(_L("Load Error: %d Expected Error: %d"), loadErr, KErrNone);
	TEST(loadErr==KErrNone);
		
	// compare expected and actual bitmaps
	TInt lengthInBytes=screenBitmap->ScanLineLength(screenSize.iWidth, screenDisplayMode);
	HBufC8* lineBufBitmap=HBufC8::NewLC(lengthInBytes);
	TPtr8 lineBufBitmapPtr(lineBufBitmap->Des());
	HBufC8* lineBufScreenBitmap=HBufC8::NewLC(lengthInBytes);
	TPtr8 lineBufScreenBitmapPtr(lineBufScreenBitmap->Des());

	// in the case of the emulator the colour palette used by
	// windows can differ and therefore causes false failures to
	// be reported. e.g. although the dialog is displayed it is
	// subtly different shade of blue (techview), hence for 
	// emulator test runs we purposely do not run a comparison
	// of the screen.
#ifndef __WINS__
	INFO_PRINTF1(_L("Comparing expected vs actual screen bitmap"));
	for (TInt index=0; index<screenSize.iHeight; index++)
		{
		compareBitmap->GetScanLine(lineBufBitmapPtr, TPoint(0,index), screenSize.iWidth, screenDisplayMode);
		screenBitmap->GetScanLine(lineBufScreenBitmapPtr, TPoint(0,index), screenSize.iWidth, screenDisplayMode);
		INFO_PRINTF2(_L("Scanline: %d"),index);
		TEST(lineBufBitmapPtr.Compare(lineBufScreenBitmapPtr)==0);
		}
#endif

	if (aDbgMbm)
		{
		// for debug purposes store the screen capture
		// in c:\appfwk\test\cone\...
		User::LeaveIfError(iFs.Connect());
		iFs.MkDirAll(*aDbgBmp);
		screenBitmap->Save(*aDbgBmp);
		const TDesC* bmpArray[1];
		bmpArray[0] = aDbgBmp;
		TInt32 bmpIds[1];
		bmpIds[0]=0;
		CFbsBitmap::StoreL(*aDbgMbm,1,bmpArray,bmpIds);
		// convert CFbsBitmap of screen capture to standard bmp to ease debug
		ConvertToBmpL(screenBitmap, aDbgConvBmp);
		// convert CFbsBitmap of expected bmp to standard bmp to ease debug
		ConvertToBmpL(compareBitmap, aDbgConvCompBmp);
		iFs.Close();
		}
	
	// terminate the host process
	process.Terminate(KErrNone);
	
	CleanupStack::PopAndDestroy(7);
	iWs.Close();
	
	// send signal to close a dialog
	CloseDialogsL();
	// wait the host process for a termination
	User::WaitForRequest(status);
	
	}