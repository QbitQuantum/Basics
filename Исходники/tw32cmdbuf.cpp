/**
* Runs the test in a second thread.
*
* @param aFunctionIndex The drawing function command to be executed. All commands are defined in TestFunctionIndex.
*/
TInt CTW32CmdBuf::DoTestCmdBufFunctionL(TTestFunctionIndex aFunctionIndex)
	{
	RWsSession session;
	User::LeaveIfError(session.Connect());
	CleanupClosePushL(session);
	CWsScreenDevice *device = new(ELeave) CWsScreenDevice(session);
	CleanupStack::PushL(device);
	User::LeaveIfError(device->Construct(CTestBase::iScreenNo));
	CWindowGc* gc;
	User::LeaveIfError(device->CreateContext(gc));
	CleanupStack::PushL(gc);
	RWindowGroup group(session);
	User::LeaveIfError(group.Construct(1, EFalse));
	CleanupClosePushL(group);
	RWindow window(session);
	User::LeaveIfError(window.Construct(group, 2));
	CleanupClosePushL(window);
	window.SetExtent(TPoint(0,0), TSize(200, 200));
	User::LeaveIfError(window.SetRequiredDisplayMode(EColor64K));
	window.Activate();	
	gc->Activate(window);
	session.SetAutoFlush(EFalse);
	window.Invalidate();
	window.BeginRedraw();
	for(TInt i=KMinTestIterations; i<KMaxTestIterations; ++i)
		{
		for(TInt j=0; j<i; ++j)
			{
			gc->Clear();
			}

		CFbsBitmap* bitmap = new(ELeave) CFbsBitmap;
		CleanupStack::PushL(bitmap);
		User::LeaveIfError(bitmap->Create(TSize(100, 100), EColor64K));
		CFbsBitmap* mask = new(ELeave) CFbsBitmap;
		CleanupStack::PushL(mask);
		User::LeaveIfError(mask->Create(TSize(100, 100), EColor64K));
		KTestFunctions[aFunctionIndex](gc, bitmap, mask);
		CleanupStack::PopAndDestroy(2);
		session.Flush();	
		}	
	window.EndRedraw();	
	gc->Deactivate();
	CleanupStack::PopAndDestroy(5);
	return KErrNone;
	}