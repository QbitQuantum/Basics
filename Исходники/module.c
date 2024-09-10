BOOL
WINAPI
EnumProcessModules(
    HANDLE hProcess,
    HMODULE *lphModule,
    DWORD cb,
    LPDWORD lpcbNeeded
    )
{
    PROCESS_BASIC_INFORMATION BasicInfo;
    NTSTATUS Status;
    PPEB Peb;
    PPEB_LDR_DATA Ldr;
    PLIST_ENTRY LdrHead;
    PLIST_ENTRY LdrNext;
    DWORD chMax;
    DWORD ch;

    Status = NtQueryInformationProcess(
                hProcess,
                ProcessBasicInformation,
                &BasicInfo,
                sizeof(BasicInfo),
                NULL
                );

    if ( !NT_SUCCESS(Status) ) {
        SetLastError( RtlNtStatusToDosError( Status ) );
        return(FALSE);
        }

    Peb = BasicInfo.PebBaseAddress;

    //
    // Ldr = Peb->Ldr
    //

    if (!ReadProcessMemory(hProcess, &Peb->Ldr, &Ldr, sizeof(Ldr), NULL)) {
        return(FALSE);
        }

    LdrHead = &Ldr->InMemoryOrderModuleList;

    //
    // LdrNext = Head->Flink;
    //

    if (!ReadProcessMemory(hProcess, &LdrHead->Flink, &LdrNext, sizeof(LdrNext), NULL)) {
        return(FALSE);
        }

    chMax = cb / sizeof(HMODULE);
    ch = 0;

    while (LdrNext != LdrHead) {
        PLDR_DATA_TABLE_ENTRY LdrEntry;
        LDR_DATA_TABLE_ENTRY LdrEntryData;

        LdrEntry = CONTAINING_RECORD(LdrNext, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

        if (!ReadProcessMemory(hProcess, LdrEntry, &LdrEntryData, sizeof(LdrEntryData), NULL)) {
            return(FALSE);
            }

        if (ch < chMax) {
            try {
                   lphModule[ch] = (HMODULE) LdrEntryData.DllBase;
                }
            except (EXCEPTION_EXECUTE_HANDLER) {
                SetLastError( RtlNtStatusToDosError( GetExceptionCode() ) );
                return(FALSE);
                }
            }

        ch++;

        LdrNext = LdrEntryData.InMemoryOrderLinks.Flink;
        }

    try {
        *lpcbNeeded = ch * sizeof(HMODULE);
        }
    except (EXCEPTION_EXECUTE_HANDLER) {
        SetLastError( RtlNtStatusToDosError( GetExceptionCode() ) );
        return(FALSE);
        }

    return(TRUE);
}