BOOL CURtpMulticastMediaFramesSource::Connect(CString & sError)
{
    BOOL bRet = CUTcpMediaFramesSource::Connect(sError);

    if(!bRet)
        return FALSE;

    try
    {
        MulticastGroupDescription grDesc;
        ZeroMemory(&grDesc, sizeof(MulticastGroupDescription));
        if(!ReadBytes((BYTE *)&grDesc, sizeof(MulticastGroupDescription)))
            throw(_T("Media server dropped connection"));

        if(grDesc.nPort != 0)
        {

            // Create the socket. In Winsock 2 we do have to specify the
            // multicast attributes that this socket will be used with.
            if ((m_sock = WSASocket(AF_INET, SOCK_DGRAM, 0, NULL, 0,
                                    WSA_FLAG_MULTIPOINT_C_LEAF
                                    | WSA_FLAG_MULTIPOINT_D_LEAF
                                    | WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
                throw(_T("Winsock multicast error - can't create datagram socket"));

            //Disable loopback
            int optval = 0;
            if(setsockopt(m_sock, IPPROTO_IP, 4, (char *)&optval, sizeof(optval)) == SOCKET_ERROR)
                throw(_T("Winsock multicast error - can't disable loopback"));

            //Enlarge receive buffer
            optval = 0x20000;
            if(setsockopt(m_sock, SOL_SOCKET, SO_RCVBUF, (char *)&optval, sizeof(optval)) == SOCKET_ERROR)
            {
                optval = 0x10000;
                if(setsockopt(m_sock, SOL_SOCKET, SO_RCVBUF, (char *)&optval, sizeof(optval)) == SOCKET_ERROR)
                {
                    optval = 0x8000;
                    setsockopt(m_sock, SOL_SOCKET, SO_RCVBUF, (char *)&optval, sizeof(optval));
                }
            }

            //Allow multiple viewers
            BOOL bReuse = TRUE;
            setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&bReuse, sizeof(BOOL));

            // Setup the SOCKADDR_IN structure describing the multicast
            // group we want to join.
            sockaddr_in  remote    = {0};
            remote.sin_family      = AF_INET;
            remote.sin_port        = htons(grDesc.nPort);
            remote.sin_addr.s_addr = inet_addr(grDesc.chGroup);

            // Join the multicast group.  sockM is not used to send
            // or receive data. It is used when you want to leave the
            // multicast group. Simply call closesocket() on it to
            // unsubscribe from the group.
            if((m_sockM = WSAJoinLeaf(m_sock, (SOCKADDR *)&remote,
                                      sizeof(remote), NULL, NULL, NULL, NULL, JL_RECEIVER_ONLY)) == INVALID_SOCKET)
                throw(_T("Winsock multicast error - can't join multicast group"));
        }
    }
    catch(const LPTSTR & sMessage)
    {
        sError = sMessage;
        bRet = FALSE;
    }
    catch(...)
    {
        sError = _T("Unexpected error");
        bRet = FALSE;
    }

    return bRet;
}