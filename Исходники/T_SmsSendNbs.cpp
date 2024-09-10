LOCAL_C void doMainL()
	{
	RSocketServ serv;
	RSocket socket;

	User::LeaveIfError(serv.Connect());
	CleanupClosePushL(serv);
	
	TProtocolDesc protoinfo;
	TProtocolName protocolname(KSmsDatagram);
	User::LeaveIfError(serv.FindProtocol(protocolname,protoinfo));
	User::LeaveIfError(socket.Open(serv,protoinfo.iAddrFamily,protoinfo.iSockType,protoinfo.iProtocol));

	TSmsAddr smsaddr;
	smsaddr.SetSmsAddrFamily(ESmsAddrSendOnly);
	User::LeaveIfError(socket.Bind(smsaddr));

	CleanupClosePushL(socket);

	CActiveScheduler* iScheduler = new (ELeave) CActiveScheduler;
	CleanupStack::PushL(iScheduler);
	CActiveScheduler::Install( iScheduler );

	CSmsTestUtils* smsTest = CSmsTestUtils::NewL(test);
	CleanupStack::PushL(smsTest);
	TInt nextTest = 0;

	smsTest->NotifySaPhoneOnL();
	smsTest->WaitForInitializeL();

	CSmsSendNbsTest* nbsTest = CSmsSendNbsTest::NewL(*smsTest, KNbsScript, nextTest);
	CleanupStack::PushL(nbsTest);

	nbsTest->StartL();

	CleanupStack::PopAndDestroy(3); //SmsTest, iScheduler

	CleanupStack::PopAndDestroy(&socket);
	CleanupStack::PopAndDestroy(&serv);
	}