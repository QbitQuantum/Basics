// Send a string, specifying the transport-idle timeout to be used
TInt CImapIO::SendWithTimeout(TRequestStatus& aStatus, TInt aTimeout, const TDesC8& aLine)
	{
	// Disconnected?
	if (iState==EIOStateDisconnected)
		return(KErrDisconnected);

	if (iState!=EIOStateConnected)
		{
		return(KErrNotReady);
		}
		
	// We're queuing a send
	iState=EIOStateWriteQueued;

	Queue(aStatus);
	iTXbytes+=aLine.Length();
	iSession->SendWithTimeout(iStatus, aTimeout, aLine);
	SetActive();

	return(KErrNone);
	}