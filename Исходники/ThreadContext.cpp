//-----------------------------------------------------------------------------
// Name: GetPreviousEipEbp
// Object: get previous eip & ebp
// Parameters :
//     in  : HANDLE hSuspendedThread : handle of the suspended thread
//           PBYTE CurrentEip
//           PBYTE CurrentEbp
//     out : PBYTE* pEip
//           PBYTE* pEbp
//     return : TRUE on success
//-----------------------------------------------------------------------------
BOOL CThreadContext::GetPreviousEipEbp(HANDLE hSuspendedThread,PBYTE CurrentEip,PBYTE CurrentEbp,PBYTE* pEip,PBYTE* pEbp)
{
    // only ebp is requiered for retrieving previous eip/ebp
    UNREFERENCED_PARAMETER(CurrentEip);


    // retrieve Process Id of thread (we got time we are in suspended state :D)
    CProcessAndThreadID ProcessAndThreadID;
    DWORD dwProcessId=ProcessAndThreadID.GetProcessIdOfThread(hSuspendedThread);
    BOOL bThreadBelongsToCurrentProcess=(dwProcessId==GetCurrentProcessId());
    SIZE_T ReadBytes=0;

    // use the return address of the call so it's position in the stack is at ebp+4
    if (bThreadBelongsToCurrentProcess)
    {
        if (IsBadReadPtr(CurrentEbp+sizeof(PBYTE),sizeof(PBYTE)))
            return FALSE;
        memcpy(pEip,CurrentEbp+sizeof(PBYTE),sizeof(PBYTE));
    }
    else
    {
        // --> read this address in remote process
        if(!Toolhelp32ReadProcessMemory(dwProcessId,CurrentEbp+sizeof(PBYTE),pEip,sizeof(PBYTE),&ReadBytes))
            return FALSE;
    }
    
    // notice you can retrieve ebp directly too
    // if you want to do it just use the following lines
    //   Notice: real ebp is the content of ct.ebp  --> like a mov dwRealEbp,dword ptr[ct.ebp]
    if (bThreadBelongsToCurrentProcess)
    {
        if (IsBadReadPtr(CurrentEbp,sizeof(PBYTE)))
            return FALSE;
        memcpy(pEbp,CurrentEbp,sizeof(PBYTE));
    }
    else
    {
        if(!Toolhelp32ReadProcessMemory(dwProcessId,CurrentEbp,pEbp,sizeof(PBYTE),&ReadBytes))
            return FALSE;
    }

    return TRUE;
}