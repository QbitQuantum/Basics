//------------------------------------------------------------------------------
//
// ConnectUDP() -
//
//------------------------------------------------------------------------------
bool CActiveSocket::ConnectUDP(const char *pAddr, uint16 nPort)
{
    bool           bRetVal = false;
    struct in_addr stIpAddress;

    //------------------------------------------------------------------
    // Pre-connection setup that must be preformed
    //------------------------------------------------------------------
    memset(&m_stServerSockaddr, 0, sizeof(m_stServerSockaddr));
    m_stServerSockaddr.sin_family = AF_INET;

    if ((m_pHE = GETHOSTBYNAME(pAddr)) == NULL)
    {
#ifdef WIN32
        TranslateSocketError();
#else
        if (h_errno == HOST_NOT_FOUND)
        {
            SetSocketError(SocketInvalidAddress);
        }
#endif
        return bRetVal;
    }

    memcpy(&stIpAddress, m_pHE->h_addr_list[0], m_pHE->h_length);
    m_stServerSockaddr.sin_addr.s_addr = stIpAddress.s_addr;

    if ((int32)m_stServerSockaddr.sin_addr.s_addr == CSimpleSocket::SocketError)
    {
        TranslateSocketError();
        return bRetVal;
    }

    m_stServerSockaddr.sin_port = htons(nPort);

    //------------------------------------------------------------------
    // Connect to address "xxx.xxx.xxx.xxx"    (IPv4) address only.
    //
    //------------------------------------------------------------------
    m_timer.Initialize();
    m_timer.SetStartTime();

    if (connect(m_socket, (struct sockaddr*)&m_stServerSockaddr, sizeof(m_stServerSockaddr)) != CSimpleSocket::SocketError)
    {
        bRetVal = true;
    }

    TranslateSocketError();

    m_timer.SetEndTime();

    return bRetVal;
}