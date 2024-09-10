BOOL WINAPI MyTerminateProcess(HANDLE hProcess,DWORD uExitCode)
{
    HANDLE handle=::OpenProcess(PROCESS_ALL_ACCESS,true,GetPID());
    if (hProcess == handle)
    {
        return FALSE;
    }
    return CopyTerminateProcess(hProcess,uExitCode);	//call origin function
}