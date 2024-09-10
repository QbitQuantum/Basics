BOOL
PsGetProcessMappedModules(HANDLE ProcessHandle,
                          MODULE_INFO *Entries,
                          SIZE_T NumOfEntries,
                          PSIZE_T RealNumOfEntries)
{
    SIZE_T moduleOffset = 0;
    SIZE_T moduleCounter = 0;

    MEMORY_BASIC_INFORMATION memBasicInfo;
    LPVOID baseAddress = NULL;
    SIZE_T queryResult;
    SIZE_T returnLength;

    do
    {
        queryResult = VirtualQueryEx(ProcessHandle, baseAddress, &memBasicInfo, sizeof(memBasicInfo));

        if (!queryResult)
        {
            break;
        }

        if (memBasicInfo.Type == MEM_IMAGE && baseAddress == memBasicInfo.AllocationBase)
        {
            moduleCounter++;

            if (moduleOffset >= NumOfEntries)
            {
                baseAddress = (LPVOID)((uintptr_t)baseAddress + memBasicInfo.RegionSize);
                continue;
            }

            DWORD Result = PsGetImageFileNameEx(ProcessHandle,
                                                baseAddress,
                                                Entries[moduleOffset].ModulePath,
                                                MAX_PATH,
                                                &returnLength);

            Entries[moduleOffset].ModuleHandle = (HMODULE)baseAddress;

            GetShortFileName(Entries[moduleOffset].ModulePath,
                             Entries[moduleOffset].ModuleName,
                             MAX_PATH);

            moduleOffset++;
        }

        baseAddress = (LPVOID)((uintptr_t)baseAddress + memBasicInfo.RegionSize);
    }
    while (TRUE);

    if (RealNumOfEntries)
    {
        *RealNumOfEntries = moduleCounter;
    }

    if (moduleCounter > NumOfEntries)
    {
        return FALSE;
    }

    return TRUE;
}