/**
 * Function that will look at all the devices on the RConnection
 * and update the device array accordingly.
 */		
TInt CPanConnections::UpdateCurrentConnections()
	{
	TInt rerr = KErrNone;
	HBufC8* buffer=0;
	const TInt KAddrLen = sizeof(TBTDevAddr);

	TRAP(rerr, buffer = HBufC8::NewL(7*KAddrLen));// create a buffer to house the device address
	if(rerr == KErrNone)
		{
		TPtr8 ptr = buffer->Des();
		// use RConnection to enumerate all the devices
		rerr = iConnection.Control(KCOLAgent, KCOAgentPanEnumerateDevices, ptr);
		if(rerr == KErrNone)
			{
			iActiveConnections.Reset();
			while(ptr.Length()>=KBTDevAddrSize)
				{
				// inspect the addr's in the descriptor and append them to the array.
				TBTDevAddr parsedAddr(ptr.Mid(ptr.Length()-KAddrLen, KBTDevAddrSize));
				ptr.SetLength(Max(ptr.Length()-KAddrLen, 0));
				iActiveConnections.Append(parsedAddr);
				}
			}
		}
	delete buffer;
	return rerr;
	}