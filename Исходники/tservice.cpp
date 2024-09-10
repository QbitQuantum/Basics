void CMyService::ConstructL()
	{
	User::LeaveIfError(iSocketServ.Connect());
	iSCOConnection = new(ELeave) CMySCOService(iSocketServ);
	iSCOConnection->ConstructL();
	User::LeaveIfError(iSdpSession.Connect());
	TBTServiceSecurity sec;
	sec.SetAuthentication(EMitmNotRequired);
	sec.SetAuthorisation(EFalse);
	sec.SetEncryption(EFalse);
	sec.SetDenied(EFalse);
	iBtService = CBtService::NewL(TUUID(KSerialPortUUID), //register as a serial port so we can be easily seen
								iSdpSession,
								iSocketServ,
								*this,
								KRFCOMM,
								&sec);
	iConnection = CBluetoothSocket::NewL(*this, iSocketServ);
	iBtService->AcceptConnection(*iConnection);
	}