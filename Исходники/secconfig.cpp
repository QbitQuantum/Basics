BOOL InsertSectionConfigInPE(PVOID pvPEBase,DWORD dwPESize,PVOID pvData,DWORD dwDataSize,PVOID *ppvNewPE,DWORD *pdwNewPESize)
{
	BOOL bRet = FALSE;
	PVOID pvCompressedData;
	DWORD dwCompressedDataSize;
	PVOID pvConfigData;
	DWORD dwConfigDataSize;
	DWORD dwSeed = GetTickCount();
	PIMAGE_SECTION_HEADER pNewSection;
	DWORD dwSize;

	if (CompressBuffer(pvData,dwDataSize,&pvCompressedData,&dwCompressedDataSize))
	{
		dwConfigDataSize = dwCompressedDataSize + sizeof(SECTION_CONFIG_HEADER);

		if (pvConfigData = malloc(dwConfigDataSize))
		{
			PSECTION_CONFIG_HEADER pSecCfgHeader = (PSECTION_CONFIG_HEADER)pvConfigData;

			pSecCfgHeader->dwDecompressedSize = dwDataSize;
			pSecCfgHeader->dwCompressedSize = dwCompressedDataSize;

			for (int i = 0; i < sizeof(pSecCfgHeader->bRc4Key); i++) 
			{
				pSecCfgHeader->bRc4Key[i] = (BYTE)RtlRandom(&dwSeed);
			}

			EncryptRc4(pSecCfgHeader->bRc4Key,sizeof(pSecCfgHeader->bRc4Key),&pSecCfgHeader[1],pvCompressedData,dwCompressedDataSize);

			if (pNewSection = InsertSectionHeader(pvPEBase,SECTION_CONFIG_NAME,dwConfigDataSize,IMAGE_SCN_CNT_INITIALIZED_DATA|IMAGE_SCN_MEM_READ,&dwSize))
			{
				PVOID pvNewPE;
				DWORD dwNewPESize = pNewSection->PointerToRawData + pNewSection->SizeOfRawData;

				if (pvNewPE = malloc(dwNewPESize))
				{
					memcpy(pvNewPE,pvPEBase,dwPESize);

					PIMAGE_NT_HEADERS pNtHeaders = RtlImageNtHeader(pvNewPE);

					++(pNtHeaders->FileHeader.NumberOfSections);

					PIMAGE_SECTION_HEADER pVirtualLastSection = GetVirtualyLastSectionHeader(pNtHeaders);
					pVirtualLastSection[0] = *pNewSection;
					
					pNtHeaders->OptionalHeader.SizeOfImage += dwSize;

					memcpy((PVOID)((DWORD)pvNewPE + pNewSection->PointerToRawData),pvConfigData,dwConfigDataSize);

					DWORD dwHeaderSum, dwCheckSum;

					if (CheckSumMappedFile(pvNewPE,dwNewPESize,&dwHeaderSum,&dwCheckSum))
					{
						pNtHeaders->OptionalHeader.CheckSum = dwCheckSum;

						*ppvNewPE = pvNewPE;
						*pdwNewPESize = dwNewPESize;

						bRet = TRUE;
					}

					if (!bRet) free(pvNewPE);
				}

				free(pNewSection);
			}

			free(pvConfigData);
		}
	
		free(pvCompressedData);
	}

	return bRet;
}