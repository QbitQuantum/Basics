u32 CHookFunction_i::GetExportFunctionInfo(CArray<EXPORT_FUN_INFO, EXPORT_FUN_INFO&>& InfoArray, 
                                           const char* pszDllFile)
{
    if(!pszDllFile)
    {
        return 0;
    }
	  
    PLOADED_IMAGE pImage = ::ImageLoad((char*)pszDllFile, NULL);
    if(!pImage)
    {
        return 0;
    }
	
    DWORD dwBase = (DWORD)pImage->MappedAddress;
    PIMAGE_SECTION_HEADER pSections    = (PIMAGE_SECTION_HEADER)((DWORD)pImage->FileHeader + sizeof(IMAGE_NT_HEADERS));
    PIMAGE_EXPORT_DIRECTORY pExportDir = (PIMAGE_EXPORT_DIRECTORY)(RVA2RawAdr(pSections, pImage->FileHeader->OptionalHeader.DataDirectory[0].VirtualAddress) + dwBase);
	
    InfoArray.RemoveAll();
	  
    EXPORT_FUN_INFO info;
	
    DWORD* pFunOffsetAdr = (DWORD*)(RVA2RawAdr(pSections, pExportDir->AddressOfFunctions) + dwBase);
    for(DWORD i = 0; i < pExportDir->NumberOfFunctions; i++)
    {
        info.dwOffset = 0;
        info.strFunName = "";
        info.dwOrdinal = 0;
        
        info.dwOffset = *(pFunOffsetAdr + i);
        info.dwOrdinal =  i + 1;
        InfoArray.Add(info);
    }
	
    DWORD* pFunNamesAdr       = (DWORD*)(RVA2RawAdr(pSections, pExportDir->AddressOfNames) + dwBase);
    WORD* pFunNamesOrdinalAdr = (WORD*)(RVA2RawAdr(pSections, pExportDir->AddressOfNameOrdinals) + dwBase);
	  
    char* pName = NULL;
    for(i = 0; i < pExportDir->NumberOfNames; i++)
    {
        pName = (char*)(RVA2RawAdr(pSections, *(pFunNamesAdr+i)) + dwBase);
        int idx = *(pFunNamesOrdinalAdr+i);
        if(idx < InfoArray.GetSize())
        {
          EXPORT_FUN_INFO& tmpInfo = InfoArray.ElementAt(idx);
          tmpInfo.strFunName = pName;
        }
    }
	  
    ImageUnload(pImage);
    
    return InfoArray.GetSize();
}