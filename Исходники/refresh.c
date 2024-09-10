HMODULE CustomLoadLibrary(const PWCHAR wszFullDllName, const PWCHAR wszBaseDllName, ULONG_PTR pDllBase)
{
    // File handles
    HANDLE hFile = INVALID_HANDLE_VALUE;
    HANDLE hMap = NULL;
    PCHAR pFile = NULL;

    // PE headers
    PIMAGE_DOS_HEADER pDosHeader;
    PIMAGE_NT_HEADERS pNtHeader;
    PIMAGE_SECTION_HEADER pSectionHeader;

    // Library 
    PCHAR pLibraryAddr = NULL;
    DWORD dwIdx;

    // Relocation
    PIMAGE_DATA_DIRECTORY pDataDir;
    PIMAGE_BASE_RELOCATION pBaseReloc;
    ULONG_PTR pReloc;
    DWORD dwNumRelocs;
    ULONG_PTR pInitialImageBase;
    PIMAGE_RELOC pImageReloc;

    // Import
    PIMAGE_IMPORT_DESCRIPTOR pImportDesc;
    PCHAR szDllName;
    SIZE_T stDllName;
    PWSTR wszDllName = NULL;
    PWCHAR wsRedir = NULL;
    PWSTR wszRedirName = NULL;
    SIZE_T stRedirName;
    SIZE_T stSize;

    HMODULE hModule;
    PIMAGE_THUNK_DATA pThunkData;
    FARPROC* pIatEntry;

	// clr.dll hotpatches itself at runtime for performance reasons, so skip it
	if (wcscmp(L"clr.dll", wszBaseDllName) == 0)
		goto cleanup;

	dprintf("[REFRESH] Opening file: %S", wszFullDllName);

    // ----
    // Step 1: Map the file into memory
    // ----

	hFile = CreateFileW(wszFullDllName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
        goto cleanup;

    hMap = CreateFileMappingW(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    if (hMap == NULL)
        goto cleanup;

    pFile = (PCHAR)MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);
    if (pFile == NULL)
        goto cleanup;

    // ----
    // Step 2: Parse the file headers and load it into memory
    // ----
    pDosHeader = (PIMAGE_DOS_HEADER)pFile;
    pNtHeader = (PIMAGE_NT_HEADERS)(pFile + pDosHeader->e_lfanew);

    // allocate memory to copy DLL into
    dprintf("[REFRESH] Allocating memory for library");
    pLibraryAddr = (PCHAR)VirtualAlloc(NULL, pNtHeader->OptionalHeader.SizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    // copy header
    dprintf("[REFRESH] Copying PE header into memory");
    memcpy(pLibraryAddr, pFile, pNtHeader->OptionalHeader.SizeOfHeaders);

    // copy sections
    dprintf("[REFRESH] Copying PE sections into memory");
    pSectionHeader = (PIMAGE_SECTION_HEADER)(pFile + pDosHeader->e_lfanew + sizeof(IMAGE_NT_HEADERS));
    for (dwIdx = 0; dwIdx < pNtHeader->FileHeader.NumberOfSections; dwIdx++)
    {
        memcpy(pLibraryAddr + pSectionHeader[dwIdx].VirtualAddress,
               pFile + pSectionHeader[dwIdx].PointerToRawData,
               pSectionHeader[dwIdx].SizeOfRawData);
    }

    // update our pointers to the loaded image
    pDosHeader = (PIMAGE_DOS_HEADER)pLibraryAddr;
    pNtHeader = (PIMAGE_NT_HEADERS)(pLibraryAddr + pDosHeader->e_lfanew);

    // ----
    // Step 3: Calculate relocations
    // ----
    dprintf("[REFRESH] Calculating file relocations");

    pDataDir = &pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC];
    pInitialImageBase = pNtHeader->OptionalHeader.ImageBase;
    // set the ImageBase to the already loaded module's base
    pNtHeader->OptionalHeader.ImageBase = pDllBase;

    // check if their are any relocations present
    if (pDataDir->Size)
    {
        // calculate the address of the first IMAGE_BASE_RELOCATION entry
        pBaseReloc = (PIMAGE_BASE_RELOCATION)(pLibraryAddr + pDataDir->VirtualAddress);

        // iterate through each relocation entry
        while ((PCHAR)pBaseReloc < (pLibraryAddr + pDataDir->VirtualAddress + pDataDir->Size) && pBaseReloc->SizeOfBlock)
        {
            // the VA for this relocation block
            pReloc = (ULONG_PTR)(pLibraryAddr + pBaseReloc->VirtualAddress);

            // number of entries in this relocation block
            dwNumRelocs = (pBaseReloc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(IMAGE_RELOC);

            // first entry in the current relocation block
            pImageReloc = (PIMAGE_RELOC)((PCHAR)pBaseReloc + sizeof(IMAGE_BASE_RELOCATION));

            // iterate through each entry in the relocation block
            while (dwNumRelocs--)
            {
                // perform the relocation, skipping IMAGE_REL_BASED_ABSOLUTE as required.
                // we subtract the initial ImageBase and add in the original dll base
                if (pImageReloc->type == IMAGE_REL_BASED_DIR64)
                {
                    *(ULONG_PTR *)(pReloc + pImageReloc->offset) -= pInitialImageBase;
                    *(ULONG_PTR *)(pReloc + pImageReloc->offset) += pDllBase;
                }
                else if (pImageReloc->type == IMAGE_REL_BASED_HIGHLOW)
                {
                    *(DWORD *)(pReloc + pImageReloc->offset) -= (DWORD)pInitialImageBase;
                    *(DWORD *)(pReloc + pImageReloc->offset) += (DWORD)pDllBase;
                }
                else if (pImageReloc->type == IMAGE_REL_BASED_HIGH)
                {
                    *(WORD *)(pReloc + pImageReloc->offset) -= HIWORD(pInitialImageBase);
                    *(WORD *)(pReloc + pImageReloc->offset) += HIWORD(pDllBase);
                }
                else if (pImageReloc->type == IMAGE_REL_BASED_LOW)
                {
                    *(WORD *)(pReloc + pImageReloc->offset) -= LOWORD(pInitialImageBase);
                    *(WORD *)(pReloc + pImageReloc->offset) += LOWORD(pDllBase);
                }
                
                // get the next entry in the current relocation block
                pImageReloc = (PIMAGE_RELOC)((PCHAR)pImageReloc + sizeof(IMAGE_RELOC));
            }

            // get the next entry in the relocation directory
            pBaseReloc = (PIMAGE_BASE_RELOCATION)((PCHAR)pBaseReloc + pBaseReloc->SizeOfBlock);
        }
    }

    // ----
    // Step 4: Update import table
    // ----
    dprintf("[REFRESH] Resolving Import Address Table (IAT) ");

    pDataDir = &pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    if (pDataDir->Size)
    {
        pImportDesc = (PIMAGE_IMPORT_DESCRIPTOR)(pLibraryAddr + pDataDir->VirtualAddress);

        while (pImportDesc->Characteristics)
        {
            hModule = NULL;
            wszDllName = NULL;
            szDllName = (PCHAR)(pLibraryAddr + pImportDesc->Name);
            stDllName = strnlen(szDllName, MAX_PATH);
            wszDllName = (PWSTR)calloc(stDllName + 1, sizeof(WCHAR));

            if (wszDllName == NULL)
                goto next_import;

            mbstowcs_s(&stSize, wszDllName, stDllName + 1, szDllName, stDllName);

			dprintf("[REFRESH] Loading library: %S", wszDllName);

			// If the DLL starts with api- or ext-, resolve the redirected name and load it
            if (_wcsnicmp(wszDllName, L"api-", 4) == 0 || _wcsnicmp(wszDllName, L"ext-", 4) == 0)
            {
                // wsRedir is not null terminated
                wsRedir = GetRedirectedName(wszBaseDllName, wszDllName, &stRedirName);
                if (wsRedir)
                {
                    // Free the original wszDllName and allocate a new buffer for the redirected dll name
                    free(wszDllName);
                    wszDllName = (PWSTR)calloc(stRedirName + 1, sizeof(WCHAR));
                    if (wszDllName == NULL)
                        goto next_import;

                    memcpy(wszDllName, wsRedir, stRedirName * sizeof(WCHAR));
                    dprintf("[REFRESH] Redirected library: %S", wszDllName);
                }
            }

            // Load the module
            hModule = CustomGetModuleHandleW(wszDllName);

            // Ignore libraries that fail to load
            if (hModule == NULL)
                goto next_import;

            if (pImportDesc->OriginalFirstThunk)
                pThunkData = (PIMAGE_THUNK_DATA)(pLibraryAddr + pImportDesc->OriginalFirstThunk);
            else
                pThunkData = (PIMAGE_THUNK_DATA)(pLibraryAddr + pImportDesc->FirstThunk);

            pIatEntry = (FARPROC*)(pLibraryAddr + pImportDesc->FirstThunk);

            // loop through each thunk and resolve the import
            for(; DEREF(pThunkData); pThunkData++, pIatEntry++)
            {
                if (IMAGE_SNAP_BY_ORDINAL(pThunkData->u1.Ordinal))
                    *pIatEntry = CustomGetProcAddressEx(hModule, (PCHAR)IMAGE_ORDINAL(pThunkData->u1.Ordinal), wszDllName);
                else
                    *pIatEntry = CustomGetProcAddressEx(hModule, ((PIMAGE_IMPORT_BY_NAME)(pLibraryAddr + DEREF(pThunkData)))->Name, wszDllName);
            }

next_import:
            if (wszDllName != NULL)
            {
                free(wszDllName);
                wszDllName = NULL;
            }
            pImportDesc = (PIMAGE_IMPORT_DESCRIPTOR)((PCHAR)pImportDesc + sizeof(IMAGE_IMPORT_DESCRIPTOR));

        }
    }

cleanup:
    if (pFile != NULL)
        UnmapViewOfFile(pFile);
    if (hMap != NULL)
        CloseHandle(hMap);
    if (hFile != INVALID_HANDLE_VALUE)
        CloseHandle(hFile);

    return (HMODULE) pLibraryAddr;
}