/** Performs time conversions (in OOM conditions) to local/universal times either using system or specified time zone
*/
void CTestTZServer::OOMTimeConversionsL()
	{
	CActiveScheduler* scheduler;
	scheduler = new CActiveScheduler();
	CleanupStack::PushL(scheduler);  
	CActiveScheduler::Install(scheduler);
		
	_LIT8(KEuropeLondon, "Europe/London");
	CTzId* zoneId = CTzId::NewL(KEuropeLondon);
	
	CleanupStack::PushL(zoneId);

	RTz tz;
	CTzConverter* timeConverter = NULL;
	CleanupClosePushL(tz);
	User::LeaveIfError(tz.Connect());
	
	TRAPD(err, timeConverter = CTzConverter::NewL(tz));
	TESTL( err == KErrNone );
	
	CleanupStack::PushL(timeConverter);	
	
	TPtrC	ptrSystemTime;
	TESTL(GetStringFromConfig(ConfigSection(), KTime, ptrSystemTime));
	TTime	time(ptrSystemTime);
	
	iFailAt = 1;
	for ( ;; )
		{
		StartHeapCheck(iFailAt);
		TInt err = timeConverter->ConvertToLocalTime(time);
		 
		if ( err == KErrNone )
			{
			__UHEAP_RESET;
			INFO_PRINTF1(_L("OOM testing of ConvertToLocalTime Api (using current time zone) is done"));
			break;
			}
				
		if ( ErrorProcess(err) )
			{
			EndHeapCheck();
			}
		else
			{
			break;
			}
		}
		
	iFailAt = 1;
	for ( ;; )
		{
		StartHeapCheck(iFailAt);
		TInt err = timeConverter->ConvertToLocalTime(time, *zoneId);
		 
		if ( err == KErrNone )
			{
			__UHEAP_RESET;
			INFO_PRINTF1(_L("OOM testing of ConvertToLocalTime Api (specifiying time zone) is done"));
			break;
			}
				
		if ( ErrorProcess(err) )
			{
			EndHeapCheck();
			}
		else
			{
			break;
			}
		}	
		
	iFailAt = 1;
	for ( ;; )
		{
		StartHeapCheck(iFailAt);
		TInt err = timeConverter->ConvertToUniversalTime(time);
		 
		if ( err == KErrNone )
			{
			__UHEAP_RESET;
			INFO_PRINTF1(_L("OOM testing of ConvertToUniversalTime Api (using current time zone) is done"));
			break;
			}
				
		if ( ErrorProcess(err) )
			{
			EndHeapCheck();
			}
		else
			{
			break;
			}
		}	
		
	iFailAt = 1;
	for ( ;; )
		{
		StartHeapCheck(iFailAt);
		TInt err = timeConverter->ConvertToUniversalTime(time, *zoneId);
		 
		if ( err == KErrNone )
			{
			__UHEAP_RESET;
			INFO_PRINTF1(_L("OOM testing of ConvertToUniversalTime (specifiying time zone) Api is done"));
			break;
			}
				
		if ( ErrorProcess(err) )
			{
			EndHeapCheck();
			}
		else
			{
			break;
			}
		}	
		
	CleanupStack::PopAndDestroy(timeConverter);
	CleanupStack::PopAndDestroy(&tz);
	CleanupStack::PopAndDestroy(zoneId);
	CleanupStack::PopAndDestroy(scheduler);
	
	CActiveScheduler::Install(NULL);
	}