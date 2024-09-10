DWORD
_cdecl
main(
    int argc,
    char *argv[],
    char *envp[]
    )
{

    STARTUPINFO	StartupInfo;
    PROCESS_INFORMATION ProcessInfo;
    BOOL Success;
    DWORD st;
    DWORD ProcessCount;
    SMALL_RECT Window;
    MEMORY_BASIC_INFORMATION info;
    PUCHAR address;
    PUCHAR buffer;

    ProcessCount = 0;
    if ( strchr(GetCommandLine(),'+') ) {
        NewProcess();
        }

    GetStartupInfo(&StartupInfo);

    Success = CreateProcess(
                    NULL,
                    "vmread +",
                    NULL,
                    NULL,
                    FALSE,
                    CREATE_NEW_CONSOLE,
                    NULL,
                    NULL,
                    &StartupInfo,
                    &ProcessInfo
                    );

    if (Success) {
        printf("Process Created\n");

        Sleep (1000);


        buffer = VirtualAlloc (NULL, 10*1000*1000, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

        if (!buffer) {
            printf("virtual alloc failed at %ld.\n",GetLastError());
            return 1;
        }

        address = NULL;
        do {

            Success = VirtualQueryEx (ProcessInfo.hProcess,
                                      (PVOID)address,
                                      &info,
                                      sizeof(info));

            if (!Success) {
                printf ("virtual query failed at %lx - %ld.\n",address,GetLastError());
                break;
            } else {
                printf("address: %lx size %lx state %lx protect %lx type %lx\n",
                    address,
                    info.RegionSize,
                    info.State,
                    info.Protect,
                    info.Type);
            }

            address += info.RegionSize;
        } while (address < (PUCHAR)0x80000000);

        address = 0x40000000;
        do {

            Success = VirtualQueryEx (ProcessInfo.hProcess,
                                      (PVOID)address,
                                      &info,
                                      sizeof(info));

            if (!Success) {
                printf ("virtual query failed at %lx %ld.\n",address,GetLastError());
                return 1;
            } else {
                if (info.AllocationBase == address) {
                    printf("address: %lx size %lx state %lx protect %lx type %lx\n",
                        address,
                        info.RegionSize,
                        info.State,
                        info.Protect,
                        info.Type);
                }
            }
            address += 4096;
        } while (address < (PUCHAR)0x80000000);

        CloseHandle(ProcessInfo.hProcess);
        CloseHandle(ProcessInfo.hThread);
    }
}