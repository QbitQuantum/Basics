void ListenerImpl::doListen()
{
    HANDLE			hWaits[2];
    hWaits[0]		= hKillEvent;
    hWaits[1]		= hSocketEvent;


    WSANETWORKEVENTS events;
    while(true)
    {
        // Wait for either the kill event or  an accept event :
        DWORD dwRet = WSAWaitForMultipleEvents(2, hWaits, FALSE, INFINITE, FALSE);

        //If kill event then quit loop :
        if (dwRet == WAIT_OBJECT_0)
        {
            break;
        }

        int nRet = WSAEnumNetworkEvents(hSocket, hSocketEvent, &events);
        if (nRet == SOCKET_ERROR)
        {
            //Error
            break;
        }

        //Deal with the new incoming connection
        if ((events.lNetworkEvents & FD_ACCEPT) && (events.iErrorCode[FD_ACCEPT_BIT] == 0))
        {
            if(!acceptConnectionRequest())
                break;
        }
        else
            break;
    }
}