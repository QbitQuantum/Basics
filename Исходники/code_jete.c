// http://stackoverflow.com/questions/3749668/how-to-query-the-thread-count-of-a-process-using-the-regular-windows-c-c-apis
int GetCurrentThreadCount()
{
    // first determine the id of the current process
    DWORD const  id = GetCurrentProcessId();

    // then get a process list snapshot.
    HANDLE const  snapshot = CreateToolhelp32Snapshot( TH32CS_SNAPALL, 0 );

    // initialize the process entry structure.
    PROCESSENTRY32 entry = { 0 };
    entry.dwSize = sizeof( entry );

    // get the first process info.
    BOOL  ret = true;
    ret = Process32First( snapshot, &entry );
    while( ret && entry.th32ProcessID != id ) {
        ret = Process32Next( snapshot, &entry );
    }
    CloseHandle( snapshot );
    return ret 
        ?   entry.cntThreads
        :   -1;
}