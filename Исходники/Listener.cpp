TInt32 CListener::Run(TInt32 cnt)
{
    TInt32 usedCnt = HasNewConnection();
    SOCKET acceptedSocket = SOCKET_ERROR;
    int nLen = sizeof(SOCKADDR_IN);
    for (int i =0;i<usedCnt;++i)
    {
        acceptedSocket = WSAAccept(m_listeningSocket,
            NULL,
            &nLen,0,0);
        if (SOCKET_ERROR != acceptedSocket)
        {
//             TInt32 ret = SetSocketOptions(acceptedSocket);
//             if (SUCCESS > ret)
//             {
//                 closesocket(ret);
//                 continue;
//             }
            TInt32 result = SetSocketOptions(acceptedSocket);
            if (SUCCESS > result)
            {
                closesocket(acceptedSocket);
                continue;
            }
            
            
            CConnection *pNew = m_pConnectionPool->GetItem();
            if (!pNew)
            {
                closesocket(acceptedSocket);
                return usedCnt;
            }
            CConPair pair;
            GetConnPair(acceptedSocket,pair);
            IfConnectionCallBack *pAppCallBack = m_pListenerCallBack->OnNewConnection(&pair);
            if (!pAppCallBack)
            {
                closesocket(acceptedSocket);
                continue;
            }
            IfParser  *pParser;
            if (m_pParserFactory)
            {
                pParser = m_pParserFactory->GetParser(&pair,pNew->GetConnectionIdx());
            }
            else
            {
                pParser = NULL;
            }
            IfCryptor *pCryptor;
            if (m_pCryptorFactory)
            {
                 pCryptor = m_pCryptorFactory->GetCryptor(&pair,pNew->GetConnectionIdx());
            }
            else
            {
                pCryptor = NULL;
            }
			pNew->SetConnectionType(connection_is_postive);
            TInt32 ret = pNew->Init(acceptedSocket,&pair,pAppCallBack,pParser,pCryptor);
            if (SUCCESS > ret)
            {
				pAppCallBack->OnDissconneted(ret);
                pNew->CloseConnection();
                m_pConnectionPool->ReleaseItem(pNew);
                continue;
            }
            HANDLE h = CreateIoCompletionPort((HANDLE) acceptedSocket, m_compeltionPort, (ULONG_PTR)(pNew), 0);

            if (h != m_compeltionPort)
            {
				pAppCallBack->OnDissconneted(ret);
                pNew->OnDisconnected();
                m_pConnectionPool->ReleaseItem(pNew);
                continue;
            }
            
            ret = pNew->OnConnected();
            if (SUCCESS > ret)
            {
				pAppCallBack->OnDissconneted(ret);
                pNew->CloseConnection();
                m_pConnectionPool->ReleaseItem(pNew);
                continue;
            }
        }
    }
    return usedCnt;
}