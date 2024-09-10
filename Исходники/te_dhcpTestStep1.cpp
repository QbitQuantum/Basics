TVerdict CDhcpTestStep1_5::doTestStepL()
/**
* @return - TVerdict code only ever returns EPass, else leaves with error!
* Override of base class pure virtual
* Get Remaining Lease Time (test case 4.1.5)
*/
	{
	SetTestStepResult(EFail);
	
	RSocketServ eSock;
	TInt err = eSock.Connect();
	TESTEL(err == KErrNone, err);
	CleanupClosePushL(eSock);
#ifdef _DEBUG
	User::LeaveIfError(RProperty::Set(KMyPropertyCat, KMyPropertyDestPortv4, 67));
#endif		
	
	RConnection connNET1;
	err = connNET1.Open(eSock);
	TESTEL(err == KErrNone, err);
	CleanupClosePushL(connNET1);
	
	err = connNET1.Start(iConnPrefs); // see test script for IAP used
	TESTEL(err == KErrNone, err);
	
	TConnectionLeaseInfoBuf leaseTime1;
	leaseTime1().iAddressFamily = IpAddressFamilyL();
	TRequestStatus stat;
	connNET1.Ioctl(KCOLConfiguration, KConnGetAddrLeaseTimeRemain, stat, &leaseTime1);
	User::WaitForRequest(stat);
	TESTEL(stat == KErrNotSupported, stat.Int());

	err = connNET1.Stop();
	TESTEL(err == KErrNone, err);

	CleanupStack::PopAndDestroy(&connNET1);
	CleanupStack::PopAndDestroy(&eSock);
	
	SetTestStepResult(EPass);
	return TestStepResult();
	}