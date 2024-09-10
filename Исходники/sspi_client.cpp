PBYTE VerifyThis(
PBYTE   pBuffer, 
LPDWORD pcbMessage,
struct _SecHandle *hCtxt,
ULONG   cbMaxSignature)
{

	SECURITY_STATUS   ss;
	SecBufferDesc     BuffDesc;
	SecBuffer         SecBuff[2];
	ULONG             ulQop = 0;
	PBYTE             pSigBuffer;
	PBYTE             pDataBuffer;
	
	//-------------------------------------------------------------------
	//  The global cbMaxSignature is the size of the signature
	//  in the message received.

	printf ("data before verifying (including signature):\n");
	PrintHexDump (*pcbMessage, pBuffer);

	//--------------------------------------------------------------------
	//  By agreement with the server, 
	//  the signature is at the beginning of the message received,
	//  and the data that was signed comes after the signature.

	pSigBuffer = pBuffer;
	pDataBuffer = pBuffer + cbMaxSignature;

	//-------------------------------------------------------------------
	//  The size of the message is reset to the size of the data only.

	*pcbMessage = *pcbMessage - (cbMaxSignature);

	//--------------------------------------------------------------------
	//  Prepare the buffers to be passed to the signature verification 
	//  function.

	BuffDesc.ulVersion    = 0;
	BuffDesc.cBuffers     = 2;
	BuffDesc.pBuffers     = SecBuff;

	SecBuff[0].cbBuffer   = cbMaxSignature;
	SecBuff[0].BufferType = SECBUFFER_TOKEN;
	SecBuff[0].pvBuffer   = pSigBuffer;

	SecBuff[1].cbBuffer   = *pcbMessage;
	SecBuff[1].BufferType = SECBUFFER_DATA;
	SecBuff[1].pvBuffer   = pDataBuffer;

	ss = VerifySignature(
	hCtxt,
	&BuffDesc,
	0,
	&ulQop
	);

	if (!SEC_SUCCESS(ss)) 
	{
		fprintf(stderr, "VerifyMessage failed");
	}
	else
	{
		printf("Message was properly signed.\n");
	}

	return pDataBuffer;

}  // end VerifyThis