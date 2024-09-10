EXPORT_C TInt RRtaContent::GetStringAttributeSetL(const TDesC& aUniqueId, RStringAttributeSet &aStringAttributeSet) const
	{
	TInt err = KErrOverflow;
	TInt length = 0;
	TPckg <TInt> lengthPckg(length);
	
	// Write the object out to a buffer, send to client
	CBufFlat* buf = CBufFlat::NewL(50);
	CleanupStack::PushL(buf);
	
	// create write stream
	RBufWriteStream writeStream(*buf);
	CleanupClosePushL(writeStream);

	// write the directory to the stream
	aStringAttributeSet.ExternalizeL(writeStream);
	CleanupStack::PopAndDestroy(&writeStream);
	
	
	TPtr8 bufPtr = buf->Ptr(0);
	// allocate arbitary receive buffer much larger than the size of the source buffer
	length = bufPtr.Length() * 15;
	
	while(err == KErrOverflow)
		{
		HBufC8* transferBuffer = HBufC8::NewLC(length);
		transferBuffer->Des().Copy(bufPtr);
		TPtr8 transferPtr = transferBuffer->Des();
	
		// attempt to retrieve the attributes
		err = SendReceive(EGetStringAttributeSet, TIpcArgs(&aUniqueId, &transferPtr));	
		if(err == KErrOverflow)
			{
			// Find out the length required to receive the resulting attribute set
			lengthPckg.Copy(transferPtr.Left(lengthPckg.MaxLength()));	
			}
		else if(err == KErrNone)
			{
			// read in the attribute values from the buffer
			RDesReadStream readStream(transferPtr);
			CleanupClosePushL(readStream);
			aStringAttributeSet.InternalizeL(readStream);
			CleanupStack::PopAndDestroy(&readStream);
			}
		CleanupStack::PopAndDestroy(transferBuffer);	
		}

	CleanupStack::PopAndDestroy(buf);
	return err;
	}