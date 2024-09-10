//
//This heap failure member function is used to ensure correct operation in low-memory
// situations. It requires the flogger server to be started in order to inform the server
// on each loop iteration as to the new memory requirement. Thus, this harness is no
// good for cases where the flogger server must be shut down and restarted or
// when server is not meant to be running before the test case commences.
//
TInt CTestStepFlogger::doTestStepWithHeapFailureL( CTestStepFlogger& aTestStep, TInt lowMemory, TInt highMemory, TInt aReturnValue, TBool bypassChecks)
/**
 @param bypassChecks allows a parameter to be passed to the executeStep to let it know that the
 case is being used for heap checking. This is needed because most flogger methods do
 not return an error code when they fail to write due to no memory. Thus, when running
 the heap test the part of the test case which ensures the data was written to disk
 may fail to find the data, and thus we need to bypass these checks.
 @param aReturnValue - expected return value if everything works
 @param lowMemory - amount of memory to start testing at - must be at least 10 lower than highMemory and test must fail due to low memory at this level
 @param highMemory - amount of memory to stop testing at - if we reach this, test has failed.
 */
	{
	TInt ret=0;
	TInt loop;
	TPtrC8 ptrSubSystemTmp;
	TPtrC8 ptrComponentTmp;
	ptrSubSystemTmp.Set(_L8("SubSystem"));
	ptrComponentTmp.Set(_L8("Component"));

	RFileLogger logger;
	User::LeaveIfError(logger.Connect());
	CleanupClosePushL(logger);
	logger.SetLogTags(KStdSubsysTag8, KStdCompTag8);
	// clear the log so that any previous test data is gone and not detected
	logger.ClearLog();
	User::After(KTimeToLog);

	for (loop = lowMemory; loop < highMemory ; loop++)
		{
		INFO_PRINTF2(_L("%d"),loop);
		logger.__DbgSetHeapFailure(loop);

		ret = aTestStep.executeStep(bypassChecks);

		if ( ret == KErrNoMemory)
			{
			//The heap failure has been trapped correctly
			continue;
			}
		else if (( ret == aReturnValue ) && (loop != lowMemory))
			{
			//Test step normal behaviour
			INFO_PRINTF4(_L("%S PASSED heap failure test, loop = %d return code==%d"), 
			&aTestStep.TestStepName(), loop, ret );
			SetTestStepResult(EPass);			break;
			}
		else
			{
			// test step has not returned the exepected error value ( which was either KErrNoMemory or aReturnValue )
			INFO_PRINTF5(_L("%S *FAILED* heap failure test, loop=%d return code:%d expected:%d"), 
				&aTestStep.TestStepName(), loop, ret, aReturnValue );
			SetTestStepResult(EFail);			break;
			}

		}
	// shutdown flogger server so we can see if any memory leaks - flogger svr will panic if there are
	// This also means the next test does not get any residuals in the log buffers.
	logger.ClearLog();
	logger.__DbgShutDownServer();
	CleanupStack::PopAndDestroy();	//logger
	if (loop == highMemory)
		{
		// often the return code isn't checked, so make sure the test harness sees that it failed.
		SetTestStepResult(EFail);		return KErrGeneral;
		}
	if ( ret != aReturnValue )
		{
		// often the return code isn't checked, so make sure the test harness sees that it failed.
		SetTestStepResult(EFail);		return KErrGeneral;
		}
	return KErrNone;
	}