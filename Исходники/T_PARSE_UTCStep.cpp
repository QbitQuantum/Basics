void CTestUTCParse::ReadDataL(CImRecvConvert* aRecvConvert, TFileName aFileName)
	{
	// open the file
	RFile file;

	TInt error = file.Open(iTestUtils->FileSession(), aFileName, EFileShareAny);
	if(error != KErrNone)
		{
		ERR_PRINTF2(TRefByValue<const TDesC>_L("\r\nFile open error %d"), error);
		User::Leave(KErrNotFound);
		}

	INFO_PRINTF2(TRefByValue<const TDesC>_L("Data from %s...\r\n"), aFileName.PtrZ());		

	// read the file into the conversion object
	HBufC8* lineBuffer = HBufC8::NewLC(1024);
	TPtr8 line = lineBuffer->Des();

	TBuf8<1> theChar;
	TBool finished = EFalse;

	aRecvConvert->ResetL();
	// supply a new attachment path since previous one is discarded by call to Reset()

	do {
		line.FillZ();
		line.SetLength(0);
		// compile a line one char at a time
		do {
			file.Read(theChar, 1);
			if(theChar.Length())
				line.Append(theChar);
			else
				finished = ETrue;
			// stop at the end of line or no more data
			} while(theChar.Length() && theChar[0] != 0x0A);
			if(!line.Length())
				break;
			
			aRecvConvert->ParseNextField(line); // This function doesnt actually leave, any leaves are relayed to the MessageCompleteL() function

		} while(!finished);

	TRAPD(err, aRecvConvert->MessageCompleteL());
	if(err!=KErrNone)
		{
		// At this point the message should be deleted and CImRecvConvert should be Reset()
		ERR_PRINTF3(TRefByValue<const TDesC>_L("\r\nError %d occured during the conversion of Message %d"), err, aRecvConvert->EntryId());
		}
	CleanupStack::PopAndDestroy(lineBuffer); 

	file.Close();
	}