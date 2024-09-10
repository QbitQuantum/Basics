static void cbOpenMutexA()
{
    char mutex_name[20]="";
    long mutex_addr=0;
    long esp_addr=0;
    unsigned int return_addr=0;
    DeleteAPIBreakPoint((char*)"kernel32.dll", (char*)"OpenMutexA", UE_APISTART);
    esp_addr=(long)GetContextData(UE_ESP);
    if(!ReadProcessMemory(g_fdProcessInfo->hProcess, (const void*)esp_addr, &return_addr, 4, 0))
    {
        VF_FatalError(rpmerror(), g_ErrorMessageCallback);
        return;
    }
    if(!ReadProcessMemory(g_fdProcessInfo->hProcess, (const void*)(esp_addr+12), &mutex_addr, 4, 0))
    {
        VF_FatalError(rpmerror(), g_ErrorMessageCallback);
        return;
    }
    if(!ReadProcessMemory(g_fdProcessInfo->hProcess, (const void*)mutex_addr, &mutex_name, 20, 0))
    {
        VF_FatalError(rpmerror(), g_ErrorMessageCallback);
        return;
    }
    CreateMutexA(0, FALSE, mutex_name);
    if(GetLastError()==ERROR_SUCCESS)
        SetAPIBreakPoint((char*)"kernel32.dll", (char*)"VirtualProtect", UE_BREAKPOINT, UE_APISTART, (void*)cbVirtualProtect);
    else
    {
        char log_message[256]="";
        sprintf(log_message, "[Fail] Failed to create mutex %s", mutex_name);
        VF_FatalError(log_message, g_ErrorMessageCallback);
    }
}