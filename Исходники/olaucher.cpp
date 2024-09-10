int oLaucher::PauseProcess(DWORD pid)
{

    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, pid);

    THREADENTRY32 thrdEntry;
    thrdEntry.dwSize = sizeof(thrdEntry);

    Thread32First(hSnap, &thrdEntry);

    do
    {

        if(thrdEntry.th32OwnerProcessID==pid)
        {
            HANDLE hThrd = OpenThread(THREAD_ALL_ACCESS, FALSE, thrdEntry.th32ThreadID);
            SuspendThread(hThrd);
            CloseHandle(hThrd);
        }

    } while(Thread32Next(hSnap, &thrdEntry));

    CloseHandle(hSnap);

    return 0;
}