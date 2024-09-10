VOID HookInlineChecks(BOOL Patch)
{
    int i;
    DWORD NewData;
#ifndef ISXEQ
    DWORD tmp;
    DWORD oldperm;
#endif

    int cmps[] = { __AC1 + 6 };

    int cmps2[] = { __AC2,
                    __AC3,
                    __AC4,
                    __AC5,
                    __AC6,
                    __AC7 };

    int len2[] = { 6, 6, 6, 6, 6, 6 }; 

    char NewData2[20];

    static char OldData2[sizeof(cmps2)/sizeof(cmps2[0])][20];

    if (Patch)
    {
        NewData = 0x7fffffff;

        for (i=0;i<sizeof(cmps)/sizeof(cmps[0]);i++) {
#ifdef ISXEQ
            EzModify(cmps[i],&NewData,4);
#else
            AddDetour(cmps[i], NULL, NULL, 4);
            VirtualProtectEx(GetCurrentProcess(), (LPVOID)cmps[i], 4, PAGE_EXECUTE_READWRITE, &oldperm);
            WriteProcessMemory(GetCurrentProcess(), (LPVOID)cmps[i], (LPVOID)&NewData, 4, NULL);
            VirtualProtectEx(GetCurrentProcess(), (LPVOID)cmps[i], 4, oldperm, &tmp);
#endif
        }

        memset(NewData2, 0x90, 20);

        for (i=0;i<sizeof(cmps2)/sizeof(cmps2[0]);i++) {
#ifdef ISXEQ
            EzModify(cmps2[i],NewData2,len2[i]);
#else
            AddDetour(cmps2[i], NULL, NULL, len2[i]);
            VirtualProtectEx(GetCurrentProcess(), (LPVOID)cmps2[i], len2[i], PAGE_EXECUTE_READWRITE, &oldperm);
            memcpy((void *)OldData2[i], (void *)cmps2[i], len2[i]);
            WriteProcessMemory(GetCurrentProcess(), (LPVOID)cmps2[i], (LPVOID)NewData2, len2[i], NULL);
            VirtualProtectEx(GetCurrentProcess(), (LPVOID)cmps2[i], len2[i], oldperm, &tmp);
#endif
        }
    }
    else
    {
        NewData = __AC1_Data;

        for (i=0;i<sizeof(cmps)/sizeof(cmps[0]);i++) {
#ifdef ISXEQ
            EzUnModify(cmps[i]);
#else
            VirtualProtectEx(GetCurrentProcess(), (LPVOID)cmps[i], 4, PAGE_EXECUTE_READWRITE, &oldperm);
            WriteProcessMemory(GetCurrentProcess(), (LPVOID)cmps[i], (LPVOID)&NewData, 4, NULL);
            VirtualProtectEx(GetCurrentProcess(), (LPVOID)cmps[i], 4, oldperm, &tmp);
            RemoveDetour(cmps[i]);
#endif
        }

        for (i=0;i<sizeof(cmps2)/sizeof(cmps2[0]);i++) {
#ifdef ISXEQ
            EzUnModify(cmps2[i]);
#else
            VirtualProtectEx(GetCurrentProcess(), (LPVOID)cmps2[i], len2[i], PAGE_EXECUTE_READWRITE, &oldperm);
            WriteProcessMemory(GetCurrentProcess(), (LPVOID)cmps2[i], (LPVOID)OldData2[i], len2[i], NULL);
            VirtualProtectEx(GetCurrentProcess(), (LPVOID)cmps2[i], len2[i], oldperm, &tmp);
            RemoveDetour(cmps2[i]);
#endif
        }
    }
}