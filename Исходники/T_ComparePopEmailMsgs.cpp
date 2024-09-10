/**
CheckIfFooterMessageExistsL()
Checks the email for the presence of the footer string

@param aRecvBodyText
Reference to a descriptor holding the body text

@param aFooterSize
The expected number of KB remaining on the server which has been inserted into the footer string

@return
ETrue if footer string found otherwise EFalse 
*/
TBool CT_MsgComparePopEmailMsgs::CheckIfFooterMessageExistsL(TPtrC& aRecvBodyText , TInt& aFooterSize)
	{
	RResourceFile resFile;
	CT_MsgUtils ::OpenResourceFileL(resFile, iFs, KImEngineResourceFile);	// NB leaves if file not found
	TCleanupItem close(CT_MsgUtils ::CloseResourceFile, &resFile);
	CleanupStack::PushL(close);
	
	HBufC8* buf = NULL;
	buf = resFile.AllocReadLC(PARTIAL_DOWNLOAD_FOOTER_MESSAGE);
	TResourceReader reader;
	reader.SetBuffer(buf);

	HBufC* resourceBuf = (reader.ReadTPtrC()).AllocL();
	CleanupStack::PushL(resourceBuf);

	TInt len = resourceBuf->Find(_L("%d"));
	const TInt KBufLen = 256;
	TBuf<KBufLen> findBuf;

	if(len == KErrNotFound)
		{
		len = resourceBuf->Length();
		}

	if(len > KBufLen)
		{
		len = KBufLen;
		}
	
	findBuf.Copy(resourceBuf->Ptr(), len);
	len = aRecvBodyText.Find(findBuf);

	if(len>=0)
		{
		TPtrC rest=aRecvBodyText.Right(aRecvBodyText.Length()-len-findBuf.Length());
		TLex lex(rest.Left(rest.Locate(TChar(' '))));
		lex.Val(aFooterSize);
		}
	else
		{
		aFooterSize=0;
		}

	CT_MsgUtils ::CloseResourceFile(&resFile);
	CleanupStack::PopAndDestroy(3); // buf, resourceBuf, close
	return (len != KErrNotFound);
	}