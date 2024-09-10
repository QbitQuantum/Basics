__declspec(dllexport) bool TITCALL ExporterBuildExportTable(ULONG_PTR StorePlace, ULONG_PTR FileMapVA)
{

    unsigned int i = NULL;
    unsigned int j = NULL;
    LPVOID expBuildExportDataOld;
    PIMAGE_DOS_HEADER DOSHeader;
    PIMAGE_NT_HEADERS32 PEHeader32;
    PIMAGE_NT_HEADERS64 PEHeader64;
    LPVOID expBuildExportData;
    DynBuf expBuildExportDyn;
    LPVOID expBuildExportDataCWP;
    DWORD StorePlaceRVA = (DWORD)ConvertFileOffsetToVA(FileMapVA, StorePlace, false);
    ULONG_PTR TempULONG;
    DWORD TempDWORD;
    BOOL FileIs64 = false;

    if(expTableDataCWP != NULL)
    {
        expBuildExportData = expBuildExportDyn.Allocate(ExporterEstimatedSize());
        expBuildExportDataCWP = (LPVOID)((ULONG_PTR)expBuildExportData + sizeof IMAGE_EXPORT_DIRECTORY);

        expExportData.NumberOfNames = expExportNumber;
        expExportData.NumberOfFunctions = expExportNumber;
        for(i = 0; i < expExportNumber; i++)
        {
            for(j = 0; j < expExportNumber; j++)
            {
                if(lstrcmpiA((PCHAR)expNamePointers[i], (PCHAR)expNamePointers[j]) < NULL)
                {
                    TempULONG = expNamePointers[j];
                    expNamePointers[j] = expNamePointers[i];
                    expNamePointers[i] = TempULONG;
                    TempDWORD = expExportAddress[j];
                    expExportAddress[j] = expExportAddress[i];
                    expExportAddress[i] = TempDWORD;
                }
            }
        }

        if(expNamePresent)
        {
            expExportData.Name = StorePlaceRVA + (DWORD)((ULONG_PTR)expBuildExportDataCWP - (ULONG_PTR)expBuildExportData);
            RtlMoveMemory(expBuildExportDataCWP, (LPVOID)expTableData, lstrlenA((PCHAR)expTableData));
            expBuildExportDataCWP = (LPVOID)((ULONG_PTR)expBuildExportDataCWP + lstrlenA((PCHAR)expTableData) + 2);
        }
        for(i = 0; i < expExportNumber; i++)
        {
            RtlMoveMemory(expBuildExportDataCWP, (LPVOID)expNamePointers[i], lstrlenA((PCHAR)expNamePointers[i]));
            expBuildExportDataOld = expBuildExportDataCWP;
            expBuildExportDataCWP = (LPVOID)((ULONG_PTR)expBuildExportDataCWP + lstrlenA((PCHAR)expNamePointers[i]) + 2);
            expSortedNamePointers[i] = (DWORD)((ULONG_PTR)expBuildExportDataOld - (ULONG_PTR)expBuildExportData) + StorePlaceRVA;
        }
        expExportData.AddressOfFunctions = StorePlaceRVA + (DWORD)((ULONG_PTR)expBuildExportDataCWP - (ULONG_PTR)expBuildExportData);
        RtlMoveMemory(expBuildExportDataCWP, &expExportAddress, 4 * expExportNumber);
        expBuildExportDataCWP = (LPVOID)((ULONG_PTR)expBuildExportDataCWP + 4 * expExportNumber);
        expExportData.AddressOfNames = StorePlaceRVA + (DWORD)((ULONG_PTR)expBuildExportDataCWP - (ULONG_PTR)expBuildExportData);
        RtlMoveMemory(expBuildExportDataCWP, &expSortedNamePointers, 4 * expExportNumber);
        expBuildExportDataCWP = (LPVOID)((ULONG_PTR)expBuildExportDataCWP + 4 * expExportNumber);
        expExportData.AddressOfNameOrdinals = StorePlaceRVA + (DWORD)((ULONG_PTR)expBuildExportDataCWP - (ULONG_PTR)expBuildExportData);
        RtlMoveMemory(expBuildExportDataCWP, &expOrdinals, 2 * expExportNumber);
        expBuildExportDataCWP = (LPVOID)((ULONG_PTR)expBuildExportDataCWP + 2 * expExportNumber);
        RtlMoveMemory(expBuildExportData, &expExportData, sizeof IMAGE_EXPORT_DIRECTORY);

        RtlMoveMemory((LPVOID)StorePlace, expBuildExportData, (DWORD)((ULONG_PTR)expBuildExportDataCWP - (ULONG_PTR)expBuildExportData));

        if(FileMapVA != NULL)
        {
            DOSHeader = (PIMAGE_DOS_HEADER)FileMapVA;
            if(EngineValidateHeader(FileMapVA, NULL, NULL, DOSHeader, true))
            {
                PEHeader32 = (PIMAGE_NT_HEADERS32)((ULONG_PTR)DOSHeader + DOSHeader->e_lfanew);
                PEHeader64 = (PIMAGE_NT_HEADERS64)((ULONG_PTR)DOSHeader + DOSHeader->e_lfanew);
                if(PEHeader32->OptionalHeader.Magic == 0x10B)
                {
                    FileIs64 = false;
                }
                else if(PEHeader32->OptionalHeader.Magic == 0x20B)
                {
                    FileIs64 = true;
                }
                else
                {
                    return false;
                }
                if(!FileIs64)
                {
                    PEHeader32->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress = (DWORD)StorePlaceRVA;
                    PEHeader32->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size = (DWORD)((ULONG_PTR)expBuildExportDataCWP - (ULONG_PTR)expBuildExportData);
                }
                else
                {
                    PEHeader64->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress = (DWORD)StorePlaceRVA;
                    PEHeader64->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size = (DWORD)((ULONG_PTR)expBuildExportDataCWP - (ULONG_PTR)expBuildExportData);
                }
            }
        }
        ExporterCleanup();
        return true;
    }
    return false;
}