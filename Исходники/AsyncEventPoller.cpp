int AsyncEventPoller::Poll(int timeout)
{
    if (fdEvents_.empty())
    {
        UpdateTimer();
        Sleep(timeout);
        return 0;
    }
    int count = 0;
    for (auto iter = eventFds_.begin(); iter != eventFds_.end(); ++iter)
    {
        events_[count++] = iter->first;
    }
    int nready = WSAWaitForMultipleEvents((DWORD)count, events_, FALSE, timeout, FALSE);
    if (nready == WSA_WAIT_FAILED)
    {
        LOG(ERROR) << "WSAWaitForMultipleEvents: " << LAST_ERROR_MSG;
        return 0;
    }
    else if (nready == WSA_WAIT_TIMEOUT)
    {
        UpdateTimer();
    }
    else if (nready == WSA_WAIT_IO_COMPLETION)
    {
        // Alertable I/O
    }
    else 
    {
        int index = nready - WSA_WAIT_EVENT_0;
        if (index >= WSA_MAXIMUM_WAIT_EVENTS)
        {
            LOG(ERROR) << "WSA wait events index out of range: " << index;
            return 0;
        }
        WSAEVENT hEvent = events_[index];
        FdEntry* entry = eventFds_[hEvent];
        WSANETWORKEVENTS events = {};

        // This will reset the event object and adjust the status of 
        // active FD events on the socket in an atomic fashion.
        int r = WSAEnumNetworkEvents(entry->fd, hEvent, &events);
        if (r == SOCKET_ERROR)
        {
            LOG(ERROR) << "WSAEnumNetworkEvents: " << LAST_ERROR_MSG;
            return 0;
        }
        HandleEvents(entry, &events);
        return 1;
    }
    return 0;
}