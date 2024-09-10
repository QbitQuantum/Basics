// send a request and resend any continuations - use SDP_DEBUG to dump
TUint testSdpContL(RTest& test, TUint8* aReqData, TUint aReqLen, TUint8 aReqId, /*TUint8* aRespData,*/ TUint aMtu)
{
	TUint8 pduId = aReqId;
	HBufC8* requestHBuf = HBufC8::New(aReqLen + 10 /*KSdpContinuationStateLength*/);
	HBufC8* responseHBuf;
	TPtr8 request = requestHBuf->Des();
	TPtr8 buf(0,0);
	TInt continuationLen = 0;
	TInt partial = 0;
	TInt continutations = 0;

	request.SetLength(0);
	request.Append(aReqData, aReqLen);
	do
		{
		pduId = aReqId;
		responseHBuf = InjectLC(pduId, request, aMtu);
		buf.Set(responseHBuf->Des());

		switch(pduId)
			{
			case 0x03:
				test.Printf(_L("Got SDP_ServiceSearchResponse\n"));
				partial = BigEndian::Get16(&buf[2]);
				partial *= 4;
				partial += 4;
				continuationLen = buf[partial];
				break;
			
			case 0x05:
				test.Printf(_L("Got SDP_ServiceAttributeResponse\n"));
				partial = BigEndian::Get16(&buf[0]);
				partial += 2;
				continuationLen = buf[partial];
				break;
			
			case 0x07:
				test.Printf(_L("Got SDP_ServiceSearchAttributeResponse\n"));
				partial = BigEndian::Get16(&buf[0]);
				partial += 2;
				continuationLen = buf[partial];
				break;
			default:

				test.Printf(_L("Got UnknownResponse (0x%x)\n"), buf[0]);
				continuationLen = 0;	// create a dummy non-continuation
				break;
			}
		continutations++;

		request.Zero();
		request.Append(aReqData, aReqLen-1);
		request.Append(&buf[partial], continuationLen+1);  //1 for continuation len
		CleanupStack::PopAndDestroy(/*responseHBuf*/);
		} while (continuationLen != 0);

	
	delete requestHBuf;
	return continutations;
}