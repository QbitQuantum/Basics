NS_IMETHODIMP
nsNotifyAddrListener::Run()
{
    PR_SetCurrentThreadName("Link Monitor");

    HANDLE ev = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    NS_ENSURE_TRUE(ev, NS_ERROR_OUT_OF_MEMORY);

    HANDLE handles[2] = { ev, mShutdownEvent };
    OVERLAPPED overlapped = { 0 };
    bool shuttingDown = false;

    overlapped.hEvent = ev;
    while (!shuttingDown) {
        HANDLE h;
        DWORD ret = NotifyAddrChange(&h, &overlapped);

        if (ret == ERROR_IO_PENDING) {
            ret = WaitForMultipleObjects(2, handles, FALSE, INFINITE);
            if (ret == WAIT_OBJECT_0) {
                CheckLinkStatus();
            } else {
                shuttingDown = true;
            }
        } else {
            shuttingDown = true;
        }
    }
    CloseHandle(ev);

    return NS_OK;
}