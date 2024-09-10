// From MMDXMLParserDataProvided
// TODO: Should GetData be a leaving function? Allows more flexibility to implementations of this funtion?
void CTestDataSupplier::GetData(TPtrC8 &aPtr, TRequestStatus &aStatus)
	{
	// Read the data into the descriptor
	delete iCurrentChunk;
	iCurrentChunk = NULL;
	iCurrentChunk = HBufC8::NewL(iChunkSize);
	TPtr8 chunk = iCurrentChunk->Des();
	iFile.Read(chunk, iChunkSize); // Ignore the error code, assume end of file if we haven't read any data.

	TDataProviderResults result;

	if (iCurrentChunk->Length() != 0)
		{
		aPtr.Set(*iCurrentChunk);
		result = KMoreData;
		}
	else
		{
		// Assume that if we haven't got any data then we're at the end of the stream.
		result = KDataStreamEnd;
		}

//	iChunkSize++;
	TRequestStatus *s = &aStatus;
	User::RequestComplete(s, (TInt)result);
	return;
	}