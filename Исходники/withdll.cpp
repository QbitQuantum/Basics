BOOL DumpProcess(HANDLE hp)
{
    ULONG64 base;
    ULONG64 next;

    MEMORY_BASIC_INFORMATION mbi;

    printf("  %12s %8s %8s: %3s %3s %4s %3s : %8s\n", "Address", "Offset", "Size", "Typ", "Sta", "Prot", "Ini", "Contents");
    printf("  %12s %8s %8s: %3s %3s %4s %3s : %8s\n", "------------", "--------", "--------", "---", "---", "----", "---", "-----------------");

    for (next = 0;;) {
        base = next;
        ZeroMemory(&mbi, sizeof(mbi));
        if (VirtualQueryEx(hp, (PVOID)base, &mbi, sizeof(mbi)) == 0) {
            break;
        }
        if ((mbi.RegionSize & 0xfff) == 0xfff) {
            break;
        }

        next = (ULONG64)mbi.BaseAddress + mbi.RegionSize;

        if (mbi.State == MEM_FREE) {
            continue;
        }

        CHAR szType[16];
        TypeToString(mbi.Type, szType, ARRAYSIZE(szType));
        CHAR szState[16];
        StateToString(mbi.State, szState, ARRAYSIZE(szState));
        CHAR szProtect[16];
        ProtectToString(mbi.Protect, szProtect, ARRAYSIZE(szProtect));
        CHAR szAllocProtect[16];
        ProtectToString(mbi.AllocationProtect, szAllocProtect, ARRAYSIZE(szAllocProtect));

        CHAR szFile[MAX_PATH];
        szFile[0] = '\0';
        DWORD cb = 0;
        PCHAR pszFile = szFile;

        if (base == (ULONG64)mbi.AllocationBase) {
#if 0
            cb = pfGetMappedFileName(hp, (PVOID)mbi.AllocationBase, szFile, ARRAYSIZE(szFile));
#endif
            if (GetSections(hp, (PBYTE)mbi.AllocationBase)) {
                next = base + 0x1000;
                sprintf_s(szFile, ARRAYSIZE(szFile), "%d-bit PE", Bitness);
            }
        }
        if (cb > 0) {
            for (DWORD c = 0; c < cb; c++) {
                szFile[c] = (szFile[c] >= 'a' && szFile[c] <= 'z')
                    ? szFile[c] - 'a' + 'A' : szFile[c];
            }
            szFile[cb] = '\0';
        }

        if ((pszFile = strrchr(szFile, '\\')) == NULL) {
            pszFile = szFile;
        }
        else {
            pszFile++;
        }

        PBYTE pbEnd;
        PCHAR pszSect = FindSectionName((PBYTE)base, pbEnd);
        if (pszSect != NULL) {
            pszFile = pszSect;
            if (next > (ULONG64)pbEnd) {
                next = (ULONG64)pbEnd;
            }
        }

        CHAR szDesc[128];
        ZeroMemory(&szDesc, ARRAYSIZE(szDesc));
        if (base == (ULONG64)mbi.AllocationBase) {
            sprintf_s(szDesc, ARRAYSIZE(szDesc), "  %12I64x %8I64x %8I64x: %3s %3s %4s %3s : %s",
                      (ULONG64)base,
                      (ULONG64)base - (ULONG64)mbi.AllocationBase,
                      (ULONG64)next - (ULONG64)base,
                      szType,
                      szState,
                      szProtect,
                      szAllocProtect,
                      pszFile);


        }
        else {
            sprintf_s(szDesc, ARRAYSIZE(szDesc), "  %12s %8I64x %8I64x: %3s %3s %4s %3s : %s",
                      "-",
                      (ULONG64)base - (ULONG64)mbi.AllocationBase,
                      (ULONG64)next - (ULONG64)base,
                      szType,
                      szState,
                      szProtect,
                      szAllocProtect,
                      pszFile);
        }
        printf("%s\n", szDesc);
    }
    return TRUE;
}