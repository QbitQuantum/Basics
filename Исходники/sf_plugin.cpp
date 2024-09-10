/** @prototype */
EXPORT_C TInt CFsPlugin::ClientWrite(TFsPluginRequest& aRequest, const TDesC8& aDes, TInt aOffset)
	{
	CFsMessageRequest& msgRequest = * (CFsMessageRequest*) aRequest.Request();
	TMsgOperation& currentOperation = msgRequest.CurrentOperation();
	
	TInt r = KErrNone;
	if (currentOperation.iClientRequest)
		{
		r = msgRequest.Write(0, aDes, aOffset);
		}
	else
		{
		TInt len = aDes.Length();
		if (len > (currentOperation.iReadWriteArgs.iTotalLength - aOffset))
			return KErrArgument;
		memcpy(((TUint8*) currentOperation.iReadWriteArgs.iData) + aOffset, aDes.Ptr(), len);
		currentOperation.iReadWriteArgs.iOffset = aOffset + len;
		}
	return r;
	}