/**
Override of base class pure virtual
Our implementation only gets called if the base class doTestStepPreambleL() did
not leave. That being the case, the current test result value will be EPass.

@return - TVerdict code
*/
TVerdict CAlphaBlendTest::doTestStepL(TBool aIType)
	{	
	RWsSession wsSession;
	User::LeaveIfError(wsSession.Connect());
	CleanupClosePushL(wsSession);

	//
	// Uncomment to debug WSERV redraw problems.
	// wsSession.SetAutoFlush(ETrue); 
	
	CWsScreenDevice* windowDevice = new (ELeave) CWsScreenDevice(wsSession);
	CleanupStack::PushL(windowDevice);
	User::LeaveIfError(windowDevice->Construct());
	CWindowGc* windowGc=NULL;	
	User::LeaveIfError(windowDevice->CreateContext(windowGc)); // create graphics context	
	CleanupStack::PushL(windowGc);	
	
	RWindowGroup group;	
	group  = RWindowGroup(wsSession);
	CleanupClosePushL(group);
	User::LeaveIfError(group.Construct(1, EFalse));
	
	RWindow background;
	background = RWindow(wsSession);
	CleanupClosePushL(background);
	User::LeaveIfError(background.Construct(group, 2));
	
	RWindow window;
	window = RWindow(wsSession);
	CleanupClosePushL(window);
	User::LeaveIfError(window.Construct(group, 3));

	TSize        windowSize = windowDevice->SizeInPixels();
	TDisplayMode windowMode = windowDevice->DisplayMode();

	background.Activate();
	background.Invalidate();

	ClearWindow(wsSession, background, windowGc, BLACK_SEMI_TRANSPARENT);	
	ClearWindow(wsSession, window, windowGc, BLACK_SEMI_TRANSPARENT);
	
	window.SetTransparencyAlphaChannel();	
	window.Activate();
	window.Invalidate();
	if (aIType)
		{
		if (CheckMonoTypeInstalledL())
			DoDrawBlendedTestsL(EBlendTestDrawTextIType,wsSession, KDrawVertTextIterationsToTest);
		else
			{
			INFO_PRINTF1(_L("Monotype fonts not installed, skipping test"));
			}
		}
	else
		{
/*
Test speed of blended draw rects on all modes supporting alpha blending
*/	
		DoDrawBlendedTestsL(EBlendTestDrawRect,wsSession, KDrawRectIterationsToTest);
/*
Test speed of blended draw vertical line calls on all modes supporting alpha blending
*/	
		DoDrawBlendedTestsL(EBlendTestVerticalLine,wsSession, KDrawVertLineIterationsToTest);
/*
Test speed of blended draw text calls on all modes supporting alpha blending
*/	
		DoDrawBlendedTestsL(EBlendTestDrawText,wsSession, KDrawTextIterationsToTest);
		DoDrawBlendedTestsL(EBlendTestDrawTextAntiAliased,wsSession, KDrawVertTextIterationsToTest);
		DoDrawBlendedTestsL(EBlendTestDrawVerticalText,wsSession, KDrawVertTextIterationsToTest);
/**
   @SYMTestCaseID
   GRAPHICS-UI-BENCH-0022

   @SYMTestCaseDesc
   Alphablend test BITBLT with EColor16MA source and EColor16MU destination.

   @SYMTestActions
   Compare the results over time

   @SYMTestExpectedResults
*/
		RDebug::Printf("Alpha Tests: EColor16MU, EColor16MA");
		RDebug::Printf("Alpha Blend");	
		SetTestStepID(_L("GRAPHICS-UI-BENCH-0022"));
		DoAlphaBlendBitmapsBitmapTestL(EColor16MA, EColor16MU, wsSession, window, windowGc, KIterationsToTest);	
		RecordTestResultL();

/**
   @SYMTestCaseID
   GRAPHICS-UI-BENCH-0023

   @SYMTestCaseDesc
   Test BITBLT with EColor16MA source and EColor16MU destination.

   @SYMTestActions
   Compare the results over time

   @SYMTestExpectedResults
*/
		RDebug::Printf("BitBlt Alpha");
		SetTestStepID(_L("GRAPHICS-UI-BENCH-0023"));
		DoBitBltAlphaBitmapTestL(EColor16MA, EColor16MU, wsSession, window, windowGc, KIterationsToTest);
		RecordTestResultL();
	
/**
   @SYMTestCaseID
   GRAPHICS-UI-BENCH-0024

   @SYMTestCaseDesc
   Alpha blend test BITBLT with EColor16MA source and EColor16MA destination.

   @SYMTestActions
   Compare the results over time

   @SYMTestExpectedResults
*/
		RDebug::Printf("Alpha Tests: EColor16MA, EColor16MA");
		RDebug::Printf("Alpha Blend");	
		SetTestStepID(_L("GRAPHICS-UI-BENCH-0024"));
		DoAlphaBlendBitmapsBitmapTestL(EColor16MA,EColor16MA, wsSession, window, windowGc, KIterationsToTest);
		RecordTestResultL();

/**
   @SYMTestCaseID
   GRAPHICS-UI-BENCH-0025

   @SYMTestCaseDesc
   Test BITBLT with EColor16MA source and EColor16MA destination.

   @SYMTestActions
   Compare the results over time

   @SYMTestExpectedResults
*/
		RDebug::Printf("BitBlt Alpha");
		SetTestStepID(_L("GRAPHICS-UI-BENCH-0025"));
		DoBitBltAlphaBitmapTestL(EColor16MA, EColor16MA, wsSession, window, windowGc, KIterationsToTest);
		RecordTestResultL();
/**
	@SYMTestCaseID
	GRAPHICS-UI-BENCH-0063
	
	@SYMTestCaseDesc
	Test BITBLT with EColor16MAP source and EColor16MAP destination.
	
	@SYMTestActions
	Compare the results over several iterations over time.
	
	@SYMTestExpectedResults
*/
		SetTestStepID(_L("GRAPHICS-UI-BENCH-0063"));
		DoNormalBitBltL(EFalse, EColor16MAP,EColor16MAP, wsSession, window, windowGc, KIterationsToTest);
		RecordTestResultL();
	
/**
	@SYMTestCaseID
	GRAPHICS-UI-BENCH-0064
	
	@SYMTestCaseDesc
	Test BITBLT with EColor16MA source and EColor16MA destination.
	
	@SYMTestActions
	Compare the results over several iterations over time.
	
	@SYMTestExpectedResults
*/
		SetTestStepID(_L("GRAPHICS-UI-BENCH-0064"));
		DoNormalBitBltL(EFalse, EColor16MA,EColor16MA, wsSession, window, windowGc, KIterationsToTest);
		RecordTestResultL();
	
/**
	@SYMTestCaseID
	GRAPHICS-UI-BENCH-0065
	
	@SYMTestCaseDesc
	Test BITBLT with EColor16MAP source and EColor16MA destination.
	
	@SYMTestActions
	Compare the results over several iterations over time.
	
	@SYMTestExpectedResults
*/
		SetTestStepID(_L("GRAPHICS-UI-BENCH-0065"));
		DoNormalBitBltL(EFalse, EColor16MAP,EColor16MA, wsSession, window, windowGc, KIterationsToTest);
		RecordTestResultL();
	
/**
	@SYMTestCaseID
	GRAPHICS-UI-BENCH-0066
	
	@SYMTestCaseDesc
	Test BITBLT with EColor16MA source and EColor16MAP destination.
	
	@SYMTestActions
	Compare the results over several iterations over time.
	
	@SYMTestExpectedResults
*/
		SetTestStepID(_L("GRAPHICS-UI-BENCH-0066"));
		DoNormalBitBltL(EFalse, EColor16MA,EColor16MAP, wsSession, window, windowGc, KIterationsToTest);
		RecordTestResultL();
	
/**
	@SYMTestCaseID
	GRAPHICS-UI-BENCH-0067
	
	@SYMTestCaseDesc
	Test BITBLT with EColor16MU source and EColor16MU destination.
	
	@SYMTestActions
	Compare the results over several iterations over time.
	
	@SYMTestExpectedResults
*/
		SetTestStepID(_L("GRAPHICS-UI-BENCH-0067"));
		DoNormalBitBltL(EFalse, EColor16MU,EColor16MU, wsSession, window, windowGc, KIterationsToTest);
		RecordTestResultL();
	
/**
	@SYMTestCaseID
	GRAPHICS-UI-BENCH-0068
	
	@SYMTestCaseDesc
	Test BITBLT with EColor16MAP source and EColor16MU destination.
	
	@SYMTestActions
	Compare the results over several iterations over time.
	
	@SYMTestExpectedResults
*/
		SetTestStepID(_L("GRAPHICS-UI-BENCH-0068"));
		DoNormalBitBltL(EFalse, EColor16MAP,EColor16MU, wsSession, window, windowGc, KIterationsToTest);
		RecordTestResultL();
	
/**
	@SYMTestCaseID
	GRAPHICS-UI-BENCH-0069
	
	@SYMTestCaseDesc
	Test BITBLT with EColor16MU source and EColor16MAP destination.
	
	@SYMTestActions
	Compare the results over several iterations over time.
	
	@SYMTestExpectedResults
*/
		SetTestStepID(_L("GRAPHICS-UI-BENCH-0069"));
		DoNormalBitBltL(EFalse, EColor16MU,EColor16MAP, wsSession, window, windowGc, KIterationsToTest);
		RecordTestResultL();
	
/**
	@SYMTestCaseID
	GRAPHICS-UI-BENCH-0070
	
	@SYMTestCaseDesc
	Test BITBLT with EColor64K source and EColor16MU destination.
	
	@SYMTestActions
	Compare the results over several iterations over time.
	
	@SYMTestExpectedResults
*/
		SetTestStepID(_L("GRAPHICS-UI-BENCH-0070"));
		DoNormalBitBltL(ETrue, EColor64K,EColor16MU, wsSession, window, windowGc, KIterationsToTest);
		
		RecordTestResultL();
/**
	@SYMTestCaseID
	GRAPHICS-UI-BENCH-0071
	
	@SYMTestCaseDesc
	Test DrawBitmap with different sizes (STRETCHED) with EColor16MAP source and EColor16MAP destination.
	
	@SYMTestActions
	Compare the results over several iterations over time.
	
	@SYMTestExpectedResults
*/
		SetTestStepID(_L("GRAPHICS-UI-BENCH-0071"));
		DoDrawBitmapL(EFalse, EColor16MAP, EColor16MAP, wsSession, window, windowGc, KIterationsToTest);
		RecordTestResultL();
	
/**
	@SYMTestCaseID
	GRAPHICS-UI-BENCH-0072
	
	@SYMTestCaseDesc
	Test DrawBitmap with different sizes (STRETCHED) with EColor16MA source and EColor16MA destination.
	
	@SYMTestActions
	Compare the results over several iterations over time.
	
	@SYMTestExpectedResults
*/
	
		SetTestStepID(_L("GRAPHICS-UI-BENCH-0072"));
		DoDrawBitmapL(EFalse, EColor16MA, EColor16MA, wsSession, window, windowGc, KIterationsToTest);
		RecordTestResultL();
	
/**
	@SYMTestCaseID
	GRAPHICS-UI-BENCH-0073
	
	@SYMTestCaseDesc
	Test DrawBitmap (using alpha mask) with different sizes (STRETCHED) with EColor16MU source and EColor16MU destination.
	
	@SYMTestActions
	Compare the results over several iterations over time.
	
	@SYMTestExpectedResults
*/	
		SetTestStepID(_L("GRAPHICS-UI-BENCH-0073"));
		DoDrawBitmapL(ETrue, EColor16MU, EColor16MU, wsSession, window, windowGc, KIterationsToTest);
		RecordTestResultL();
	
/**
	@SYMTestCaseID
	GRAPHICS-UI-BENCH-0057
	
	@SYMTestCaseDesc
	Test DrawBitmap (using alpha mask) with different sizes (STRETCHED) with EColor16MAP source and EColor16MAP destination.
	
	@SYMTestActions
	Compare the results over several iterations over time.
	
	@SYMTestExpectedResults
*/
		SetTestStepID(_L("GRAPHICS-UI-BENCH-0057"));
		DoDrawBitmapL(ETrue, EColor16MAP, EColor16MAP, wsSession, window, windowGc, KIterationsToTest);	
		RecordTestResultL();
		}
	CleanupStack::PopAndDestroy(6, &wsSession);
	return TestStepResult();
	}