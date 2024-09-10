BOOL DumpSectionHeaders(IMAGE_NT_HEADERS *pNTHeaders)
{
    ASSERT(pNTHeaders != NULL);

    PIMAGE_SECTION_HEADER pFirstSecHeader = (PIMAGE_SECTION_HEADER)((DWORD)pNTHeaders +
        (DWORD)sizeof(pNTHeaders->Signature) +
        (DWORD)IMAGE_SIZEOF_FILE_HEADER +
        (DWORD)pNTHeaders->FileHeader.SizeOfOptionalHeader);

#ifdef _DEBUG
    PIMAGE_SECTION_HEADER pFirstSecHeader_Verify = IMAGE_FIRST_SECTION(pNTHeaders);

    if (!(pFirstSecHeader == pFirstSecHeader_Verify))
    {
        wprintf_s(L"Error calculating address of first section header.\n");
        return FALSE;
    }
#endif

    PIMAGE_SECTION_HEADER pCurSecHeader = pFirstSecHeader;

    // 
    wprintf_s(L"\n* IMAGE_SECTION_HEADER *\n");
    wprintf_s(L"%-8s  %10s  %10s  %11s  %8s\n", L"Name", L"VirtAddr", L"PtrRawData", L"RawDataSize", L"VirtSize");
    for (DWORD i = 0; i < pNTHeaders->FileHeader.NumberOfSections; ++i, ++pCurSecHeader)
    {
        wprintf_s(L"%-8S  0x%08x  0x%08x  0x%08x  0x%08x\n", pCurSecHeader->Name, pCurSecHeader->VirtualAddress,
            pCurSecHeader->PointerToRawData, pCurSecHeader->SizeOfRawData, pCurSecHeader->Misc.VirtualSize);
    }// for i

    return TRUE;
}// DumpSectionHeaders()