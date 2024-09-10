// Each test step must supply a implementation for doTestStepL
enum TVerdict CTestAppLoaderEndTask::doTestStepL( void )
	{
	// Printing to the console and log file
	INFO_PRINTF1(_L("TEST-> END TASK"));

	TPtrC	program;
	if ( !GetStringFromConfig(ConfigSection(), KProgram, program) )
		{
		ERR_PRINTF2(KErrMissingParameter, &KProgram());
		SetTestStepResult(EFail);
		}
	else
		{
		RApaLsSession	apaLsSession;
		User::LeaveIfError(apaLsSession.Connect());
		CleanupClosePushL(apaLsSession);
	    User::LeaveIfError(apaLsSession.GetAllApps());

		RWsSession	ws;
		User::LeaveIfError(ws.Connect());
		CleanupClosePushL(ws);
		
	    TInt					numWindowGroups = ws.NumWindowGroups();
	    CArrayFixFlat<TInt>*	windowGroupList = new(ELeave) CArrayFixFlat<TInt>(numWindowGroups);
	    CleanupStack::PushL(windowGroupList);

	    // Populate array with current group list ids
	    User::LeaveIfError(ws.WindowGroupList(windowGroupList));

	    CApaWindowGroupName*	windowGroupName = CApaWindowGroupName::NewLC(ws);

	    /* Note: we use windowGroupList->Count() instead of numWindowGroups, as in the middle of the
	     * update the list could change in length (or worse, be reduced) thus producing an out of bounds
	     * error if numWindowGroups were used
	     */
	    TBool	searching=ETrue;
	    for ( TInt i=0; (i<windowGroupList->Count()) && searching; ++i )
	    	{
	        TInt	wgId = windowGroupList->At(i);
	        windowGroupName->ConstructFromWgIdL(wgId);

	        TUid	appUid = windowGroupName->AppUid();

	        TApaAppInfo	appInfo;
	        HBufC* 		appCaption = NULL;
	        // Some applications, like midlets, may not provide any info
	        if (apaLsSession.GetAppInfo(appInfo, appUid) == KErrNone)
	        	{
	            appCaption = appInfo.iCaption.AllocL();
	        	}
	        else
	        	{
	            appCaption = windowGroupName->Caption().AllocL();
	        	}
            CleanupStack::PushL(appCaption);

	        // Only list 'visible' applications
	        if ( appCaption->Length() )
	        	{
	            TPtrC	caption=*appCaption;
		        INFO_PRINTF2(KLogTask, &caption);

		        if ( program.CompareC(caption)==0 )
		        	{
					searching=EFalse;
					TApaTask	task(ws);
					task.SetWgId(wgId);
					if (task.Exists())
						{
						task.EndTask();
						}
					else
						{
						ERR_PRINTF2(KErrTaskNotFound, &program);
						SetTestStepResult(EFail);
						}
		        	}
				}
            CleanupStack::Pop(1, appCaption); // taskEntry, appCaption
	    	}

	    if ( searching )
	    	{
			ERR_PRINTF2(KErrTaskNotFound, &program);
			SetTestStepResult(EFail);
	    	}
	    CleanupStack::PopAndDestroy(4, &apaLsSession);    // windowGroupName, windowGroupList
		}

	// test steps return a result
	return TestStepResult();
	}