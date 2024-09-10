//worker thread
DWORD WINAPI WorkerThread(LPVOID lpParam)
{
    CSocketSever* pSocketServer = (CSocketSever*)lpParam;
    int i = 0;
    fd_set fdread;
    struct timeval tv = {0, 50};
    char szMessage[nMsgSize];
    memset(szMessage, 0, nMsgSize);
    while(TRUE)
    {
        // set fdread初始化为空
        FD_ZERO(&fdread);
        for(i = 0; i < pSocketServer->m_iTotalConn; i++)
                //将client socket加入fdread set
                FD_SET(pSocketServer->m_ClientSocketArr[i], &fdread);
        int ret = select(0, &fdread, NULL, NULL, &tv);
        if (ret == 0)
        {
            // Time expired 
            continue;
        }
        for(i = 0; i < pSocketServer->m_iTotalConn; i++)
        {
           if( FD_ISSET( pSocketServer->m_ClientSocketArr[i], &fdread ) )
            {
                    memset(szMessage, 0, nMsgSize);
                    ret = recv(pSocketServer->m_ClientSocketArr[i], szMessage, nMsgSize,0);
                    if ( ret == 0 || ( ret == SOCKET_ERROR && WSAGetLastError() ) )
                    {
                            //Client socket closed
                            cout << "Client socket " << pSocketServer->m_ClientSocketArr[i] << "closed." << endl;
                            closesocket( pSocketServer->m_ClientSocketArr[i]);
                            pSocketServer->m_ClientSocketArr[i--] = pSocketServer->m_ClientSocketArr[--pSocketServer->m_iTotalConn];
                    }
                    else
                    {
                            string heart = szMessage;
                            if (heart.find("心跳包") != heart.npos)
                            {
                                //cout << szMessage << endl;
                                continue;
                            }
                            //接入业务处理部分
                            g_pos = strlen(LogBuffer);
                            AcquireSRWLockExclusive(&srwTest);
                            sprintf(LogBuffer + g_pos, "%s\n", szMessage);
                            ReleaseSRWLockExclusive(&srwTest);

                            pSocketServer->m_pRTHandleData->GetClientSocket(pSocketServer->m_ClientSocketArr[i]);
                            pSocketServer->m_pRTHandleData->HandleData(szMessage, ret); 

                    }
            }
        }
    }
    return 0;
}