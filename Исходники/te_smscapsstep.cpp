TVerdict CSmsCapsWapWrite::doTestStepL()
	{

	RSocket wapsock;
	TRequestStatus status;
	TInt ret=wapsock.Open(iSocketServer,KWAPSMSAddrFamily,KSockDatagram,KWAPSMSDatagramProtocol);
	User::LeaveIfError(ret);
	CleanupClosePushL(wapsock);

	TWapAddr wapAddr;

	wapAddr.SetWapPort(TWapPortNumber(9204));
	ret=wapsock.Bind(wapAddr);
	if(RProcess().HasCapability(ECapabilityNetworkServices))
		{
		TESTL(ret != KErrPermissionDenied);
		}
	else
		{
		// skip this one
		CleanupStack::PopAndDestroy(&wapsock);
		return TestStepResult() ;
		}


	_LIT(KText,"This is a simple SMS!");
	TBuf8<200> data;
	data.Copy(KText);

	wapsock.SendTo(data, wapAddr, 0, status);
	User::WaitForRequest(status);

	TEST(status.Int() != KErrPermissionDenied);

	CleanupStack::PopAndDestroy(&wapsock);

	return	TestStepResult() ;
	}