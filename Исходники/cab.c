PVOID SfcabExtractMemory(
	PVOID CabPtr,
	ULONG CabSize,
	PULONG ExtractedBytes
	)
{

	HFDI hfdi;
	ERF erf;
	CHAR text[32];
	CHAR name[1];
	PVOID Buffer = NULL;
	CABDATA Data;
	
	if (ExtractedBytes == NULL)
		return NULL;

	__try {

		RtlSecureZeroMemory(&erf, sizeof(ERF));
		hfdi = FDICreate((PFNALLOC)fdiAlloc, (PFNFREE)fdiFree, (PFNOPEN)fdiOpen, (PFNREAD)fdiRead,
			(PFNWRITE)fdiWrite, (PFNCLOSE)fdiClose, (PFNSEEK)fdiSeek, cpu80386, &erf);

		if (hfdi) {

			g_CabParam.Buffer = CabPtr;
			g_CabParam.Size = CabSize;
			g_CabParam.Offset = 0;

			RtlSecureZeroMemory(&text, sizeof(text));
#ifdef _WIN64
			u64tostr_a((ULONG_PTR)&g_CabParam, text);
#else 
			ultostr_a((ULONG_PTR)&g_CabParam, text);
#endif

			name[0] = 0;

			Data.Size = '_';
			Data.Buffer = NULL;
			Data.Offset = 0;
			if (FDICopy(hfdi, name, text, 0, fdiNotify, 0, &Data)) {
				Buffer = Data.Buffer;
				*ExtractedBytes = Data.Size;
			}
			FDIDestroy(hfdi);
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return NULL;
	}
	return Buffer;
}