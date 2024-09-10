DWORD WINAPI
addr_change_thread(LPVOID dummy) {

    HANDLE h_waits[2];
    HANDLE h_notify;

    OVERLAPPED overlap;
    DWORD ret;

    PDESCTHREAD(L"Address change waiter", L"App");

    ZeroMemory(&overlap, sizeof(overlap));

    h_notify = NULL;
    overlap.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    do {
        ret = NotifyAddrChange(&h_notify, &overlap);

        if (ret != ERROR_IO_PENDING) {
            goto _end_thread;   /* some error */
        }

        h_waits[0] = overlap.hEvent;
        h_waits[1] = evt_terminate;

        ret = WaitForMultipleObjects(2, h_waits, FALSE, INFINITE);

        if ( ret == WAIT_OBJECT_0 ) {
            Sleep(3000);        /* wait for things to settle down */
            kmq_post_message(KMSG_CRED, KMSG_CRED_ADDR_CHANGE, 0, 0);
        } else {
            goto _end_thread;
        }
    } while(TRUE);
    
 _end_thread:
    ExitThread(0);
    return 0;                   /* unreachable */
}