//--------------------------------------------------------------------------
// patches the entry point of the main thread to go into infinite loop
// dll is injected when this loop is reached,
// after which the old entry point data is restored
int PatchEntryPoint(HANDLE proc, HANDLE thread, char *dllName)
{
    DWORD entryPoint;
    DWORD oldProtect1,oldProtect2;
    unsigned char oldHeader[2];
    unsigned char newHeader[2];
    CONTEXT context;

    entryPoint = GetEntryPoint(proc);

    if (!entryPoint)
    {
        printf("Error getting entry point\n");
        return 0;
    }

    // make entry point writeable
    VirtualProtectEx(proc, (LPVOID)entryPoint, 2, PAGE_EXECUTE_READWRITE, &oldProtect1);

    //store 2 bytes from entry point
    if (!ReadProcessMemory(proc, (LPCVOID)(entryPoint),oldHeader, 2, NULL))
    {
        printf("Error reading data from entry point");
        return 0;
    }

    // JMP -2
    newHeader[0] = 0xEB;
    newHeader[1] = 0xFE;

    // patch entry point to go into infinite loop
    if (!WriteProcessMemory(proc, (LPVOID)(entryPoint),newHeader, 2, NULL))
    {
        printf("Error writing to entry point");
        return 0;
    }

    ResumeThread(thread);

    // wait until entry point is reached
    while (true)
    {
        Sleep(100);

        context.ContextFlags = CONTEXT_CONTROL;
        GetThreadContext(thread, &context);

        if (context.Eip == entryPoint)
            break;
    }

    InjectDLL(proc, dllName);

    SuspendThread(thread);

    // return original code to entry point
    if (!WriteProcessMemory(proc, (LPVOID)(entryPoint),oldHeader, 2, NULL))
    {
        printf("Error writing to entry point");
        return 0;
    }

    // restore protection
    VirtualProtectEx(proc, (LPVOID)entryPoint, 2, oldProtect1, &oldProtect2);

    return 1;
}