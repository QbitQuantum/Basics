enum TVerdict CTestIdna01::doTestStepL()
	{

	INFO_PRINTF1(_L(" Testing GetByName(IDN) 	without IDN Enabled     "));
	INFO_PRINTF1(_L("****************************************************"));
	
	SetTestStepResult(EFail); // By default start the test case with failure.	
	
	RSocketServ pSocketServ;
	User::LeaveIfError(pSocketServ.Connect());
	RConnection myConnection;
	myConnection.Open(pSocketServ, KAfInet);

	TRequestStatus myStatus=KErrNone;
	myConnection.Start(myStatus);
	User::WaitForRequest(myStatus);

	_LIT(KTestName1,"räksmörgås.josefsson.org");
		
	TName myHostName = KTestName1();
	TNameEntry myResolvedName;
	RHostResolver hr;
	hr.Open(pSocketServ,KAfInet,KProtocolInetUdp);

	hr.GetByName(myHostName,myResolvedName,myStatus);
		
	User::WaitForRequest(myStatus);
	TInt err = myStatus.Int();
	
	if(err == KErrDndNameNotFound)
		{
		INFO_PRINTF2(_L(" GetByName(%S) 	without IDN Enabled   returned KErrDndNameNotFound "),&myHostName);
		SetTestStepResult(EPass);
		}
	
	hr.Close();
	myConnection.Close();
	pSocketServ.Close();

	return TestStepResult();

	}