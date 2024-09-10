GLDEF_C TInt E32Main()
//
// Main entry point - make sure everything is going.
//
/**
 * This method is the main entry point for the GSM TSY Regression Test Harness code.  This
 * code first makes sure the file server is included.  It also loads the comm server if
 * necessary.  After calling a method to create the necessary communications database,
 * this method invokes the user interface for the test harness.
 *
 * @return	KErrNone on Success; Errors returned from either communications database
 *			creation failure or individual tests on failures.
 *
 * @note	This method creates a new instance of the clean up stack.
 *
 */
	{
	// Make sure we're linked to the file server
	RFs s;
	s.Connect();
	s.Close();
	test.Title();

	test.Start(_L("Loading Serial drivers"));

	TInt r;

 	// When bootstrapping C32 we have to avoid the PhBkSyncServer being started, since
 	// it needs a different CommDB
 	_LIT(KPhbkSyncCMI, "phbsync.cmi");
	r = StartC32WithCMISuppressions(KPhbkSyncCMI);
	if((r!=KErrNone)&&(r!=KErrAlreadyExists))
		INFO_PRINTF1(_L("Failed to start C32 %d\n\r"),r);

	CTrapCleanup* cleanup=CTrapCleanup::New(); // get clean-up stack
	TRAP(r,CreateCommDbL());
	if(r==KErrNone)
		{
		TRAP(r,CreateTestReportFileL());
		if(r==KErrNone)
			{
			TRAP(r,PerformTestL());
			if(ReturnValue)
				r=ReturnValue;
			}
		}

	CloseTestReportFile();
	if (r)
		INFO_PRINTF1(TRefByValue<const TDesC>(_L("\nError %d reported")),r);
	else
		INFO_PRINTF1(_L("\nTest Completed Sucessfully"));

	INFO_PRINTF1(_L(", press any key to end"));
	TBool keyPressed=ETrue;
	ShortWaitForKey(10, keyPressed);
	test.End();
	delete cleanup;
//	delete testActiveScheduler;
	return KErrNone;
	}