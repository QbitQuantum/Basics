bool CPassiveSocket::BindMulticast(const char *pInterface, const char *pGroup, uint16 nPort)
{
    bool           bRetVal = false;
#ifdef WIN32
    ULONG          inAddr;
#else
    in_addr_t      inAddr;
#endif

    //--------------------------------------------------------------------------
    // Set the following socket option SO_REUSEADDR.  This will allow the file
    // descriptor to be reused immediately after the socket is closed instead
    // of setting in a TIMED_WAIT state.
    //--------------------------------------------------------------------------
    memset(&m_stMulticastGroup,0,sizeof(m_stMulticastGroup));
    m_stMulticastGroup.sin_family = AF_INET;
    m_stMulticastGroup.sin_port = htons(nPort);

    //--------------------------------------------------------------------------
    // If no IP Address (interface ethn) is supplied, or the loop back is
    // specified then bind to any interface, else bind to specified interface.
    //--------------------------------------------------------------------------
    if ((pInterface == NULL) || (!strlen(pInterface)))
    {
        m_stMulticastGroup.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    else
    {
        if ((inAddr = inet_addr(pInterface)) != INADDR_NONE)
        {
            m_stMulticastGroup.sin_addr.s_addr = inAddr;
        }
    }

    //--------------------------------------------------------------------------
    // Bind to the specified port
    //--------------------------------------------------------------------------
    if (bind(m_socket, (struct sockaddr *)&m_stMulticastGroup, sizeof(m_stMulticastGroup)) == 0)
    {
        //----------------------------------------------------------------------
        // Join the multicast group
        //----------------------------------------------------------------------
        m_stMulticastRequest.imr_multiaddr.s_addr = inet_addr(pGroup);
        m_stMulticastRequest.imr_interface.s_addr = m_stMulticastGroup.sin_addr.s_addr;

        if (SETSOCKOPT(m_socket, IPPROTO_IP, IP_ADD_MEMBERSHIP,
                       (void *)&m_stMulticastRequest,
                       sizeof(m_stMulticastRequest)) == CSimpleSocket::SocketSuccess)
        {
            bRetVal = true;
        }

        m_timer.SetEndTime();
    }

    m_timer.Initialize();
    m_timer.SetStartTime();


    //--------------------------------------------------------------------------
    // If there was a socket error then close the socket to clean out the
    // connection in the backlog.
    //--------------------------------------------------------------------------
    TranslateSocketError();

    if (bRetVal == false)
    {
        Close();
    }

    return bRetVal;
}