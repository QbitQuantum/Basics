static int modem_wait_sock(modem_t *modem, int ms, modem_poll_t flags)
{
    /* This method ignores ms and waits infinitely */
    DWORD dwEvtMask;
    DWORD dwWait;
    DWORD comerrors;
    OVERLAPPED o;
    BOOL result;
    int ret;
    HANDLE arHandles[2];

    ret = MODEM_POLL_ERROR;
	arHandles[0] = modem->threadAbort;

    o.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    arHandles[1] = o.hEvent;

    /* Initialize the rest of the OVERLAPPED structure to zero. */
    o.Internal = 0;
    o.InternalHigh = 0;
    o.Offset = 0;
    o.OffsetHigh = 0;
    assert(o.hEvent);

    if ((result = WaitCommEvent(modem->master, &dwEvtMask, &o)) == 0)
    {
        if (GetLastError() != ERROR_IO_PENDING)
        {
            /* Something went horribly wrong with WaitCommEvent(), so 
               clear all errors and try again */
            ClearCommError(modem->master, &comerrors, 0);
        }
        else
        {
	        /* IO is pending, wait for it to finish */
            dwWait = WaitForMultipleObjects(2, arHandles, FALSE, INFINITE);
            if (dwWait == WAIT_OBJECT_0 + 1  &&  !modem->block_read)
                ret = MODEM_POLL_READ;
        }
    }
    else
    {
        if (!modem->block_read)
            ret = MODEM_POLL_READ;
    }

    CloseHandle (o.hEvent);
    return ret;
}