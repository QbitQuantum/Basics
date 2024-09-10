void CTcpServerTestUPnP40::RecvComplete ( RMBufChain& aData )
	{
	RBuf8 responseBuf;
	responseBuf.CreateMax ( aData.Length () );
	aData.CopyOut ( responseBuf );
	aData.Free ();
	
	if ( responseBuf.FindF ( KExpectedResponse3 ) != KErrNotFound )
		{
		iSocketHandler.Recv ();
		responseBuf.Close ();
		return;
		}
	if ( responseBuf.FindF ( KResponseData ) != KErrNotFound )
		{
		TRAP_IGNORE(iSendChain.CreateL ( KData32 ));
		iSocketHandler.Send ( iSendChain );
		responseBuf.Close ();
		return;
		}
	if ( responseBuf.FindF ( KExpectedResponse32 ) != KErrNotFound )
		{
		iResponse = EPass;	// test case Passed
		}
	else
		{
		iResponse = EFail;	// test case failed
		}
	
	responseBuf.Close ();
	CompleteSelf ( KErrNone );
	}