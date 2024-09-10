TVerdict CApStartTestStep::doTestStepL()
	{
	INFO_PRINTF1(_L("CApStartTestStep started....\n"));
	__UHEAP_MARK;
	
	RWsSession wsSession;
	User::LeaveIfError(wsSession.Connect());
	CleanupClosePushL(wsSession);	
	
	TRAPD(err, TestStartAndForgetL(wsSession));
	TESTE(KErrNone == err, err);

	TRAP(err, TestStartAndFollowUpL(wsSession));
	TESTE(KErrNone == err, err);
	
	CleanupStack::PopAndDestroy();	//wsSession.Close();
	
	TRAP(err, TestInitApparcL());
	TESTE(KErrNone == err, err);

	__UHEAP_MARKEND; 
	INFO_PRINTF1(_L(".... CApStartTestStep finished!!"));
	
	return TestStepResult();
	}