DWORD WINAPI ServerWorkerThread(LPVOID CompletionPortID)
{
    DWORD					dwBytesTransferred = 0;
    CGateInfo*				pGateInfo = NULL;
    LPOVERLAPPED			lpOverlapped = NULL;
    char					szTmp[DATA_BUFSIZE];

    while (TRUE)
    {
        if ( GetQueuedCompletionStatus(
                    (HANDLE)CompletionPortID,
                    &dwBytesTransferred,
                    (LPDWORD)&pGateInfo,
                    (LPOVERLAPPED *)&lpOverlapped,
                    INFINITE) == 0 )
        {
            return 0;
        }

        if (g_fTerminated)
        {
            PLISTNODE		pListNode;

            if (g_xGateList.GetCount())
            {
                pListNode = g_xGateList.GetHead();

                while (pListNode)
                {
                    pGateInfo = g_xGateList.GetData(pListNode);

                    if (pGateInfo)
                        pGateInfo->Close();

                    delete pGateInfo;
                    pGateInfo = NULL;

                    pListNode = g_xGateList.RemoveNode(pListNode);
                }
            }

            return 0;
        }

        if ( dwBytesTransferred == 0 )
        {
            pGateInfo->Close();
            continue;
        }

        pGateInfo->bufLen += dwBytesTransferred;

        while ( pGateInfo->HasCompletionPacket() )
        {
            *(pGateInfo->ExtractPacket( szTmp ) - 1) = '\0';

            switch ( szTmp[1] )
            {
            case '-':
                pGateInfo->SendKeepAlivePacket();
                break;
            case 'A':
                pGateInfo->ReceiveSendUser(&szTmp[2]);
                break;
            case 'O':
                pGateInfo->ReceiveOpenUser(&szTmp[2]);
                break;
            case 'X':
                pGateInfo->ReceiveCloseUser(&szTmp[2]);
                break;
            case 'S':
                pGateInfo->ReceiveServerMsg(&szTmp[2]);
                break;
            case 'M':
                pGateInfo->MakeNewUser(&szTmp[2]);
                break;
            }
        }

        if ( pGateInfo->Recv() == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING )
        {
            InsertLogMsg(_TEXT("WSARecv() failed"));
            continue;
        }
    }

    return 0;
}