bool isWinProcessBeingDebugged(unsigned long pid)
{
    HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
    if (processHandle == NULL)
        return false;
    BOOL debugged = FALSE;
    CheckRemoteDebuggerPresent(processHandle, &debugged);
    CloseHandle(processHandle);
    return debugged != FALSE;
}