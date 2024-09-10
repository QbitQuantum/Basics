extern "C" __declspec(dllexport) DWORD GetProcessMainThreadId(DWORD procId)
{

#ifndef MAKEULONGLONG
#define MAKEULONGLONG(ldw, hdw) ((ULONGLONG(hdw) << 32) | ((ldw) & 0xFFFFFFFF))
#endif
#ifndef MAXULONGLONG
#define MAXULONGLONG ((ULONGLONG)~((ULONGLONG)0))
#endif

    DWORD dwMainThreadID = 0;
    ULONGLONG ullMinCreateTime = MAXULONGLONG;
    //includes all threads in the system
    HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hThreadSnap != INVALID_HANDLE_VALUE) {
        THREADENTRY32 th32;
        th32.dwSize = sizeof(THREADENTRY32);
        BOOL bOK = TRUE;
        //Enumerate all threads in the system and filter on th32OwnerProcessID = pid
        for (bOK = Thread32First(hThreadSnap, &th32); bOK ; bOK = Thread32Next(hThreadSnap, &th32)) {
            //if (th32.dwSize >= FIELD_OFFSET(THREADENTRY32, th32OwnerProcessID) + sizeof(th32.th32OwnerProcessID)) {
            if (th32.th32OwnerProcessID == procId && (th32.dwSize >= FIELD_OFFSET(THREADENTRY32, th32OwnerProcessID) + sizeof(th32.th32OwnerProcessID))) {
                //_tprintf(_T("DEBUG Enumerate Process (%ld) Thread Id: %ld\n"), procId, th32.th32ThreadID);
                HANDLE hThread = OpenThread(THREAD_QUERY_INFORMATION, TRUE, th32.th32ThreadID);
                if (hThread) {
                    FILETIME afTimes[4] = {0};
                    if (GetThreadTimes(hThread,	&afTimes[0], &afTimes[1], &afTimes[2], &afTimes[3])) {
                        ULONGLONG ullTest = MAKEULONGLONG(afTimes[0].dwLowDateTime, afTimes[0].dwHighDateTime);
                        if (ullTest && ullTest < ullMinCreateTime) { //check each thread's creation time
                            ullMinCreateTime = ullTest;
                            dwMainThreadID = th32.th32ThreadID; // let it be main thread
                        }
                    }
                    CloseHandle(hThread); //must close opened thread
                }
            }
        }
#ifndef UNDER_CE
        CloseHandle(hThreadSnap); //close thread snapshot
#else
        CloseToolhelp32Snapshot(hThreadSnap); //close thread snapshot
#endif
    }
    return dwMainThreadID; //returns main thread id or returns 0 if can't find it
}