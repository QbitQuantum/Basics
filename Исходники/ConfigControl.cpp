void CConfigControl::InitializeConnectionL(
	const TConnectionInfo& aInfo)
/**
 * Sets up the ESOCK connection, retrieves the interface name and the hardware address.
 *
 * @internalComponent
 * 
 * @leave System errors - if any of the called methods leaves.
 */
	{	
	__FLOG_STATIC(KConfigLoggingTag1(), KConfigLoggingTag2(), _L("CConfigControl::InitializeConnectionL - Start"));				

	TInt rc = iEsock.Connect();
	if (KErrNone != rc)
		{
		__FLOG_STATIC1(KConfigLoggingTag1(), KConfigLoggingTag2(), _L("CConfigControl::InitializeConnectionL - Failed to connect to the ESOCK server [%d]"), rc);				
		User::Leave(rc);				
		}
	
	rc = iConnection.Open(iEsock);
	if (KErrNone != rc)
		{
		__FLOG_STATIC1(KConfigLoggingTag1(), KConfigLoggingTag2(), _L("CConfigControl::InitializeConnectionL - Failed to open connection [%d]"), rc);				
		User::Leave(rc);				
		}
	
	// start the connection, this will bring up everything
	TConnectionInfoBuf infoBuf = aInfo;
	
	// Attach as Monitor - we need access to the interface for control purposes only, and don't want to affect Nifman idle timers. 
	// If we attach with EAttachTypeNormal, we prevent Nifman from ever switching to Short (Last Session Closed) Idle Timer.
	rc = iConnection.Attach(infoBuf,RConnection::EAttachTypeMonitor);
	if (KErrNone != rc)
		{
		__FLOG_STATIC1(KConfigLoggingTag1(), KConfigLoggingTag2(), _L("CConfigControl::InitializeConnectionL - Failed to start connection [%d]"), rc);				
		User::Leave(rc);				
		}
		
	rc = iSocket.Open(iEsock, KAfInet, KSockDatagram, KProtocolInetUdp, iConnection);
	if (rc != KErrNone)
		{
		__FLOG_STATIC1(KConfigLoggingTag1(), KConfigLoggingTag2(), _L("CConfigControl::InitializeConnectionL - Failed to open socket [%d]"), rc);
		User::Leave(rc);
		}
		
	// retrieve the connection information		
	rc = GetInterfaceName(aInfo, iInterfaceName);
	if (KErrNone != rc)
		{
		__FLOG_STATIC1(KConfigLoggingTag1(), KConfigLoggingTag2(), _L("CConfigControl::InitializeConnectionL - Failed to get the interface name [%d]"), rc);				
		User::Leave(rc);
		}
		
	TSoInetInterfaceInfo info;
	rc = GetInterfaceInfo(iInterfaceName, info);
	if (KErrNone != rc)
		{
		__FLOG_STATIC1(KConfigLoggingTag1(), KConfigLoggingTag2(), _L("CConfigControl::InitializeConnectionL - Failed to get the interface info [%d]"), rc);				
		User::Leave(rc);
		}
	
	iHardwareAddr = info.iHwAddr;
		
	__FLOG_STATIC(KConfigLoggingTag1(), KConfigLoggingTag2(), _L("CConfigControl::InitializeConnectionL - End"));				
	}