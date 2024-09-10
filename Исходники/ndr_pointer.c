PFORMAT_STRING NdrpEmbeddedRepeatPointerBufferSize(PMIDL_STUB_MESSAGE pStubMsg, unsigned char* pMemory, PFORMAT_STRING pFormat, unsigned char** ppMemory)
{
	ULONG_PTR MaxCount;
	unsigned char* Memory;
	unsigned char* MemoryCopy;
	unsigned char* MemoryPointer;
	PFORMAT_STRING pFormatNext;
	PFORMAT_STRING pFormatPointers;
	unsigned short increment;
	unsigned short pointer_count;
	unsigned short offset_to_array;
	unsigned short number_of_pointers;

	Memory = pStubMsg->Memory;
	MemoryCopy = pStubMsg->Memory;

	if (*pFormat == FC_FIXED_REPEAT)
	{
		pFormat += 2;
		MaxCount = *(unsigned short*) pFormat;
	}
	else
	{
		if (*pFormat != FC_VARIABLE_REPEAT)
		{
			RpcRaiseException(1766);
			return pFormat;
		}

		MaxCount = pStubMsg->MaxCount;

		if (pFormat[1] == FC_VARIABLE_OFFSET)
		{
			pMemory += pStubMsg->Offset * *((unsigned short*) &pFormat[1]);
		}
	}

	pFormat += 2;
	increment = *(unsigned short*) pFormat;

	pFormat += 2;
	offset_to_array = *(unsigned short*) pFormat;
	pStubMsg->Memory = Memory + offset_to_array;

	pFormat += 2;
	number_of_pointers = *(unsigned short*) pFormat;

	pFormat += 2;

	pFormatPointers = pFormat;

	if (MaxCount)
	{
		do
		{
			MaxCount--;
			pFormatNext = pFormatPointers;
			pointer_count = number_of_pointers;

			if (number_of_pointers)
			{
				do
				{
					pointer_count--;
					MemoryPointer = &pMemory[*(unsigned short*) pFormatNext];
					NdrpPointerBufferSize(MemoryPointer, pFormatNext + 4, pStubMsg);
					pFormatNext += 8;
				}
				while (pointer_count);
			}

			pMemory += increment;
			pStubMsg->Memory += increment;
		}
		while (MaxCount);

		Memory = MemoryCopy;
	}

	pFormat = pFormatPointers + (number_of_pointers * 8);
	pStubMsg->Memory = Memory;

	return pFormat;
}