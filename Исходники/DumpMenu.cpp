DWORD Rva2Offset(PIMAGE_NT_HEADERS pNT,VOID* Base,DWORD dwTargetRVA)
{
	PIMAGE_SECTION_HEADER pSech;

	pSech = ImageRvaToSection(pNT,Base,dwTargetRVA);
	if (!pSech)
		return 0;
	return (dwTargetRVA - pSech->VirtualAddress + pSech->PointerToRawData);
}