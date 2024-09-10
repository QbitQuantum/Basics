void CWapDgrmTestStep::_Print(CWapDatagram& aWap)
/**
 *  print a WAP datagram to the console
 */
{
	TBool                IsComplete = EFalse;
	const TPtrC&         ToAddress = aWap.ToAddress();
	const TPtrC&         FromAddress = aWap.FromAddress();
	TInt                 ToPort = 0;
	TInt                 FromPort = 0;
	TInt                 Is16BitPorts = 0;
	TBool                IsPorts = ETrue;
	TSmsDataCodingScheme::TSmsAlphabet Alphabet;

	IsComplete = aWap.IsComplete();
	Alphabet = aWap.Alphabet();

	_Print(_L8("CWapDatagram:: IsComplete: FromAddress: ToAddress: Alphabet\n"));
	_PrintBool(IsComplete);
	_Print(_L8(": "));
	_Print(FromAddress);
	_Print(_L8(": "));
	_Print(ToAddress);
	_Print(_L8(": "));
	_Print(Alphabet);
	_Print(_L8("\n"));

	aWap.Ports(FromPort,ToPort,&Is16BitPorts);
	_Print(_L8("IsPorts: FromPort: ToPort: Is16BitPorts\n"));
	_PrintBool(IsPorts);
	_Print(_L8(": "));
	_Print(FromPort);
	_Print(_L8(": "));
	_Print(ToPort);
	_Print(_L8(": "));
	_PrintBool(Is16BitPorts);
	_Print(_L8("\n"));

   	if (aWap.IsComplete())
   		{
   		// allocate buffer for data
   		HBufC8* DataBuffer = HBufC8::New(aWap.WapDatagramLength());
   		TPtr8 DataBufferPtr(DataBuffer->Des());
 		RMBufChain dgramChain;
 		aWap.WapDatagram(dgramChain, aWap.WapDatagramLength());
 		dgramChain.CopyOut(DataBufferPtr);
   		// Length
   		_Print(DataBuffer->Length());
   		_Print(_L8(": <"));

   		// Data
   		_Print(*DataBuffer);
   		_Print(_L8(">\n"));

   		delete DataBuffer;
   		}
}