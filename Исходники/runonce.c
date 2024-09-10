/*********************************************************
设定运行标志
*********************************************************/
LIBUTILS_API int UTILS_API set_runningW(const wchar_t * szProgramName)
{
    HANDLE hMutex;
    hMutex=CreateMutexW(0,TRUE,szProgramName);
    if(!hMutex)
    {
        return -1;
    }
    if(ERROR_ALREADY_EXISTS == GetLastError())
    {
        CloseHandle(hMutex);
        return 1;
    }
    return 0;
}