void NdrComplexStructBufferSize(PMIDL_STUB_MESSAGE pStubMsg, unsigned char* pMemory, PFORMAT_STRING pFormat)
{
	/**
	 * FC_BOGUS_STRUCT
	 * alignment<1>
	 * memory_size<2>
	 * offset_to_conformant_array_description<2>
	 * offset_to_pointer_layout<2>
	 * member_layout<>
	 * FC_END
	 * [pointer_layout<>]
	 */

	ULONG_PTR MaxCount;
	unsigned long Offset;
	unsigned long ActualCount;
	unsigned char* pMemoryCopy;

	unsigned char type;
	unsigned char alignment;
	unsigned short memory_size;
	unsigned char* pointer_layout;
	unsigned char* conformant_array_description;
	unsigned short offset_to_pointer_layout;
	unsigned short offset_to_conformant_array_description;

	type = pFormat[0];
	pMemoryCopy = pMemory;
	pointer_layout = conformant_array_description = NULL;

	if (type != FC_BOGUS_STRUCT)
	{
		printf("error: expected FC_BOGUS_STRUCT, got 0x%02X\n", type);
		return;
	}

	alignment = pFormat[1] + 1;
	memory_size = *(unsigned short*) &pFormat[2];

	NdrpAlignLength(&(pStubMsg->BufferLength), alignment);

	if (!pStubMsg->IgnoreEmbeddedPointers && !pStubMsg->PointerLength)
	{
		unsigned long BufferLengthCopy = pStubMsg->BufferLength;
		int IgnoreEmbeddedPointersCopy = pStubMsg->IgnoreEmbeddedPointers;

		pStubMsg->IgnoreEmbeddedPointers = 1;
		NdrComplexStructBufferSize(pStubMsg, pMemory, pFormat);
		pStubMsg->IgnoreEmbeddedPointers = IgnoreEmbeddedPointersCopy;

		pStubMsg->PointerLength = pStubMsg->BufferLength;
		pStubMsg->BufferLength = BufferLengthCopy;
	}

	pFormat += 4;

	offset_to_conformant_array_description = *(unsigned short*) &pFormat[0];

	if (offset_to_conformant_array_description)
		conformant_array_description = (unsigned char*) pFormat + offset_to_conformant_array_description;
	pFormat += 2;

	offset_to_pointer_layout = *(unsigned short*) &pFormat[0];

	if (offset_to_pointer_layout)
		pointer_layout = (unsigned char*) pFormat + offset_to_pointer_layout;
	pFormat += 2;

	pStubMsg->Memory = pMemory;

	if (conformant_array_description)
	{
		ULONG size;
		unsigned char array_type;

		array_type = conformant_array_description[0];
		size = NdrComplexStructMemberSize(pStubMsg, pFormat);

		printf("warning: NdrComplexStructBufferSize array_type: 0x%02X unimplemented\n", array_type);

		NdrpComputeConformance(pStubMsg, pMemory + size, conformant_array_description);
		NdrpComputeVariance(pStubMsg, pMemory + size, conformant_array_description);

		MaxCount = pStubMsg->MaxCount;
		ActualCount = pStubMsg->ActualCount;
		Offset = pStubMsg->Offset;
	}

	if (conformant_array_description)
	{
		unsigned char array_type;

		array_type = conformant_array_description[0];

		pStubMsg->MaxCount = MaxCount;
		pStubMsg->ActualCount = ActualCount;
		pStubMsg->Offset = Offset;

		printf("warning: NdrComplexStructBufferSize array_type: 0x%02X unimplemented\n", array_type);
	}

	pStubMsg->Memory = pMemoryCopy;

	if (pStubMsg->PointerLength > 0)
	{
		pStubMsg->BufferLength = pStubMsg->PointerLength;
		pStubMsg->PointerLength = 0;
	}
}