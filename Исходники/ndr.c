CLIENT_CALL_RETURN NdrClientCall(PMIDL_STUB_DESC pStubDescriptor, PFORMAT_STRING pFormat, void** stackTop, void** fpuStack)
{
	RPC_MESSAGE rpcMsg;
	unsigned short procNum;
	unsigned short stackSize;
	unsigned char numberParams;
	unsigned char handleType;
	MIDL_STUB_MESSAGE stubMsg;
	INTERPRETER_FLAGS flags;
	INTERPRETER_OPT_FLAGS optFlags;
	INTERPRETER_OPT_FLAGS2 extFlags;
	NDR_PROC_HEADER* procHeader;
	NDR_OI2_PROC_HEADER* oi2ProcHeader;
	CLIENT_CALL_RETURN client_call_return;

	procNum = stackSize = numberParams = 0;
	procHeader = (NDR_PROC_HEADER*) &pFormat[0];

	client_call_return.Pointer = NULL;

	handleType = procHeader->HandleType;
	flags = procHeader->OldOiFlags;
	procNum = procHeader->ProcNum;
	stackSize = procHeader->StackSize;
	pFormat += sizeof(NDR_PROC_HEADER);

	/* The Header: http://msdn.microsoft.com/en-us/library/windows/desktop/aa378707/ */
	/* Procedure Header Descriptor: http://msdn.microsoft.com/en-us/library/windows/desktop/aa374387/ */
	/* Handles: http://msdn.microsoft.com/en-us/library/windows/desktop/aa373932/ */

	printf("Oi Header: HandleType: 0x%02X OiFlags: 0x%02X ProcNum: %d StackSize: 0x%04X\n",
			handleType, *((unsigned char*) &flags),
			(unsigned short) procNum, (unsigned short) stackSize);

	if (handleType > 0)
	{
		/* implicit handle */
		printf("Implicit Handle\n");
		oi2ProcHeader = (NDR_OI2_PROC_HEADER*) &pFormat[0];
		pFormat += sizeof(NDR_OI2_PROC_HEADER);
	}
	else
	{
		/* explicit handle */
		printf("Explicit Handle\n");
		oi2ProcHeader = (NDR_OI2_PROC_HEADER*) &pFormat[6];
		pFormat += sizeof(NDR_OI2_PROC_HEADER) + 6;
	}

	optFlags = oi2ProcHeader->Oi2Flags;
	numberParams = oi2ProcHeader->NumberParams;

	printf("Oi2 Header: Oi2Flags: 0x%02X, NumberParams: %d ClientBufferSize: %d ServerBufferSize: %d\n",
			*((unsigned char*) &optFlags),
			(unsigned char) numberParams,
			oi2ProcHeader->ClientBufferSize,
			oi2ProcHeader->ServerBufferSize);

	printf("Oi2Flags: ");
	NdrPrintOptFlags(optFlags);
	printf("\n");

	NdrClientInitializeNew(&rpcMsg, &stubMsg, pStubDescriptor, procNum);

	if (optFlags.HasExtensions)
	{
		NDR_PROC_HEADER_EXTS* extensions = (NDR_PROC_HEADER_EXTS*) pFormat;

		pFormat += extensions->Size;
		extFlags = extensions->Flags2;

		printf("Extensions: Size: %d, flags2: 0x%02X\n",
				extensions->Size, *((unsigned char*) &extensions->Flags2));

#ifdef __x86_64__
		if (extensions->Size > sizeof(*extensions) && fpuStack)
		{
			int i;
			unsigned short fpuMask = *(unsigned short*) (extensions + 1);

			for (i = 0; i < 4; i++, fpuMask >>= 2)
			{
				switch (fpuMask & 3)
				{
					case 1: *(float*) &stackTop[i] = *(float*) &fpuStack[i];
						break;

					case 2: *(double*) &stackTop[i] = *(double*) &fpuStack[i];
						break;
				}
			}
		}