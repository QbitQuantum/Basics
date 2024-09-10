TVerdict CBigSendRecvRtp::doTestStepL()
/**
 * @return - TVerdict code
 */
	{
	SetTestStepResult(EFail);
	if(KErrNone == InitSocketsL())
		{
		iIpAddrDest1.SetPort(9000);
		RBuf8 sendBuf;
		sendBuf.CreateMax(KBufferSize1);
		sendBuf.CleanupClosePushL();
		RBuf8 recvBuf;
		recvBuf.CreateMax(KBufferSize1);
		recvBuf.CleanupClosePushL();
		
		/* Fill the buffer with given character upto its length */
		sendBuf.Fill('Q');
		TRequestStatus status;
		/* do a Send of the data */
		iRtpSocket.SendTo(sendBuf, iIpAddrDest1, NULL, status);
		User::WaitForRequest(status);
		User::LeaveIfError(status.Int());
		/* Now do a Receive */
		recvBuf.FillZ();
		iRtpSocket.RecvFrom(recvBuf,iIpAddrDest1,NULL,status);
		User::WaitForRequest(status);
		User::LeaveIfError(status.Int());
		
		/* Obtain a TPtr of the data excluding the RTP header */
		TPtr8 sendBufPtr = sendBuf.MidTPtr(KRtpHeaderSize);
		TPtr8 recvBufPtr = recvBuf.MidTPtr(KRtpHeaderSize);
		/* Check if the data received is the same as the data sent */
		TInt ret = sendBufPtr.Compare(recvBufPtr);
		if(ret == 0)
			{
			/* Increase the buffer size and fill it up with given data */
			sendBuf.ReAlloc(KBufferSize2);
			recvBuf.ReAlloc(KBufferSize2);
			sendBuf.Fill('Q', KBufferSize2);
			
			/* Send the larger data */
			iRtpSocket.SendTo(sendBuf, iIpAddrDest1, NULL, status);
			User::WaitForRequest(status);
			User::LeaveIfError(status.Int());
			/* Now do a Receive */
			recvBuf.FillZ(KBufferSize2);
			iRtpSocket.RecvFrom(recvBuf,iIpAddrDest1,NULL,status);
			User::WaitForRequest(status);
			User::LeaveIfError(status.Int());
			/* Get pointer to data and compare both of them */
			TPtr8 sendBufPtr = sendBuf.MidTPtr(KRtpHeaderSize);
			TPtr8 recvBufPtr = recvBuf.MidTPtr(KRtpHeaderSize);
			TInt ret = sendBufPtr.Compare(recvBufPtr);
			if(ret == 0)
				{
				SetTestStepResult(EPass);
				}
			}
		CleanupStack::PopAndDestroy(2);
		}
	return TestStepResult();
	}