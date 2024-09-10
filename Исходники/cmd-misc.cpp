bool cbDebugLoadLib(int argc, char* argv[])
{
    if(argc < 2)
    {
        dputs(QT_TRANSLATE_NOOP("DBG", "Error: you must specify the name of the DLL to load\n"));
        return false;
    }

    LoadLibThreadID = fdProcessInfo->dwThreadId;
    HANDLE LoadLibThread = ThreadGetHandle((DWORD)LoadLibThreadID);

    DLLNameMem = MemAllocRemote(0, strlen(argv[1]) + 1);
    ASMAddr = MemAllocRemote(0, 0x1000);

    if(!DLLNameMem || !ASMAddr)
    {
        dputs(QT_TRANSLATE_NOOP("DBG", "Error: couldn't allocate memory in debuggee"));
        return false;
    }

    if(!MemWrite(DLLNameMem, argv[1], strlen(argv[1])))
    {
        dputs(QT_TRANSLATE_NOOP("DBG", "Error: couldn't write process memory"));
        return false;
    }

    int size = 0;
    int counter = 0;
    duint LoadLibraryA = 0;
    char command[50] = "";
    char error[MAX_ERROR_SIZE] = "";

    GetFullContextDataEx(LoadLibThread, &backupctx);

    if(!valfromstring("kernel32:LoadLibraryA", &LoadLibraryA, false))
    {
        dputs(QT_TRANSLATE_NOOP("DBG", "Error: couldn't get kernel32:LoadLibraryA"));
        return false;
    }

    // Arch specific asm code
#ifdef _WIN64
    sprintf_s(command, "mov rcx, %p", DLLNameMem);
#else
    sprintf_s(command, "push %p", DLLNameMem);
#endif // _WIN64

    assembleat(ASMAddr, command, &size, error, true);
    counter += size;

#ifdef _WIN64
    sprintf_s(command, "mov rax, %p", LoadLibraryA);
    assembleat(ASMAddr + counter, command, &size, error, true);
    counter += size;
    sprintf_s(command, "call rax");
#else
    sprintf_s(command, "call %p", LoadLibraryA);
#endif // _WIN64

    assembleat(ASMAddr + counter, command, &size, error, true);
    counter += size;

    SetContextDataEx(LoadLibThread, UE_CIP, ASMAddr);
    auto ok = SetBPX(ASMAddr + counter, UE_SINGLESHOOT | UE_BREAKPOINT_TYPE_INT3, (void*)cbDebugLoadLibBPX);

    ThreadSuspendAll();
    ResumeThread(LoadLibThread);

    unlock(WAITID_RUN);

    return ok;
}