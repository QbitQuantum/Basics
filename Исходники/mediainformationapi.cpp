// from MRemConInterfaceIf
void CRemConMediaInformationTarget::MrcibNewMessage(TUint aOperationId, const TDesC8& aData )
	{
	LOG1(_L("\taOperationId = 0x%02x"), aOperationId);
	LOG1(_L("\taData.Length = %d"), aData.Length());

	(void) aOperationId; // ignore warning about this variable being unused
	
	if (!iInProgress && iMsgQueue.IsEmpty())
		{
		ProcessMessage(aData);
		}
	else
		{
		CRemConMediaInformationQueuedMessage* msg = NULL;
		TRAPD(err, msg = CRemConMediaInformationQueuedMessage::NewL(aData));
		if (err == KErrNone)
			{
			iMsgQueue.AddLast(*msg);
			}
		}
	}