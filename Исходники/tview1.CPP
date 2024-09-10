void CTestAppUi::TestWaitOnAppStartL()
	{
	RDebug::Print(_L("TVIEW1 : Test Wait On App Start"));

	RThread appThread;
	TRequestStatus status;
	TThreadId threadId;

	RApaLsSession ls;
	CleanupClosePushL(ls);
	User::LeaveIfError(ls.Connect());
	TApaAppInfo info;
	User::LeaveIfError(ls.GetAppInfo(info,KUidViewAppTwo));
	CleanupStack::PopAndDestroy();	// ls 

	CApaCommandLine* cmdLine=CApaCommandLine::NewLC();	
	cmdLine->SetExecutableNameL(info.iFullName);
	cmdLine->SetCommandL(EApaCommandViewActivate);
	TFileName fName=_L("c:\\Documents\\");
	TParsePtrC parse(info.iFullName);
	fName.Append(parse.Name());
	cmdLine->SetDocumentNameL(fName);

	RApaLsSession lsSession;
  	User::LeaveIfError(lsSession.Connect());
  	CleanupClosePushL(lsSession);
  	threadId=User::LeaveIfError(lsSession.StartApp(*cmdLine, threadId));
  	CleanupStack::PopAndDestroy(&lsSession);
	CleanupStack::PopAndDestroy(); // cmdLine
	User::LeaveIfError(appThread.Open(threadId));
	appThread.Logon(status);
	User::WaitForRequest(status);
	}