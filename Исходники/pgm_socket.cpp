void zmq::pgm_socket_t::open_transport ()
{
    SOCKADDR_IN salocal;
    SOCKADDR_IN sasession;

    zmq_log (1, "Opening PGM: network  %s, port %i, %s(%i)\n",
        network, port_number, __FILE__, __LINE__);
    
    //  Check if the machine supports PGM.
    int	protocol_list[] = { IPPROTO_RM, 0 };
    WSAPROTOCOL_INFOW*	lpProtocolBuf = NULL;
    DWORD dwBufLen = 0;
    int err;
    int protocols = WSCEnumProtocols (protocol_list, lpProtocolBuf, 
        &dwBufLen, &err);
    if (protocols != SOCKET_ERROR)
        assert (false);
    else if (err != WSAENOBUFS)
        assert (false);

    //  Allocate needed space for lpProtocolBuf.
    lpProtocolBuf = (WSAPROTOCOL_INFOW*)malloc (dwBufLen);
    if (lpProtocolBuf == NULL)
        assert (false);

    //  Get information about available protocols, the information will be
    //  placed to lpProtocolBuf.
	protocols = WSCEnumProtocols (protocol_list, lpProtocolBuf, 
        &dwBufLen, &err);
    if (SOCKET_ERROR == protocols) {
        free (lpProtocolBuf);
        assert (false);
    }

    bool found = FALSE;
    for (int i = 0; i < protocols; i++) {
        if (AF_INET == lpProtocolBuf[i].iAddressFamily &&
              IPPROTO_RM == lpProtocolBuf[i].iProtocol &&
              SOCK_RDM == lpProtocolBuf[i].iSocketType) {
            found = TRUE;
            break;
        }
    }

    if (!found) {
        fprintf (stderr, "PGM support is not installed on this machine.");
        free (lpProtocolBuf);
        assert (false);
    }

	free (lpProtocolBuf);
        
    //  Receiver transport.
    if (receiver) {

        receiver_listener_socket = socket (AF_INET, SOCK_RDM, IPPROTO_RM);
        wsa_assert (receiver_listener_socket != INVALID_SOCKET);

        // The bind port (port_number) specified should match that
        // which the sender specified in the connect call.
        salocal.sin_family = AF_INET;
        salocal.sin_port   = htons (port_number);
        salocal.sin_addr.s_addr = inet_addr (multicast);

        int rc = bind (receiver_listener_socket, (SOCKADDR *) &salocal, 
            sizeof(salocal));
        wsa_assert (rc != SOCKET_ERROR);

        rc = listen (receiver_listener_socket, 10);
        wsa_assert (rc != SOCKET_ERROR);

        //  Set the socket to non-blocking mode.
        u_long flag = 1;
        rc = ioctlsocket (receiver_listener_socket, FIONBIO, &flag);
        wsa_assert (rc != SOCKET_ERROR);
 
    //  Sender transport.
    } else {

        sender_socket = socket (AF_INET, SOCK_RDM, IPPROTO_RM);
        wsa_assert (sender_socket != INVALID_SOCKET);
        salocal.sin_family = AF_INET;
        salocal.sin_port   = htons (0);        // Port is ignored here
        salocal.sin_addr.s_addr = htonl (INADDR_ANY);

        int rc = bind (sender_socket, (SOCKADDR *)&salocal, sizeof(salocal));
        wsa_assert (rc != SOCKET_ERROR);
        int to_preallocate = 0;

        // Set socket options.
        ULONG val = 1;
        setsockopt (sender_socket, IPPROTO_RM, RM_HIGH_SPEED_INTRANET_OPT, 
            (char*)&val, sizeof(val));

        //  Set the socket to non-blocking mode.
        u_long flag = 1;
        rc = ioctlsocket (sender_socket, FIONBIO, &flag);
        wsa_assert (rc != SOCKET_ERROR);

        // Set the outgoing interface.
        ULONG send_iface;
        send_iface = inet_addr (network);
        rc = setsockopt (sender_socket, IPPROTO_RM, RM_SET_SEND_IF,
            (char *)&send_iface, sizeof(send_iface));
        wsa_assert (rc != SOCKET_ERROR);

        //  Set window size.
        //  Parameter WindowSizeInBytes is calculated automaticaly as
        //  send_window.WindowSizeInBytes = 
        //  send_window.RateKbitsPerSec * send_window.WindowSizeInMSecs / 8.
        assert (pgm_max_rte >= 1000);
        assert (pgm_secs != 0);
        RM_SEND_WINDOW send_window;
        send_window.RateKbitsPerSec = (pgm_max_rte / 1024) * 8;
        send_window.WindowSizeInMSecs = pgm_secs * 1000;

        //  Parameter WindowSizeInBytes is calculated automaticaly as:
        send_window.WindowSizeInBytes =
            send_window.RateKbitsPerSec * send_window.WindowSizeInMSecs / 8;
        
        //  Set multicast address and port number.
        sasession.sin_family = AF_INET;
        sasession.sin_port = htons (port_number);
        sasession.sin_addr.s_addr = inet_addr (multicast);
        
        rc = setsockopt (sender_socket, IPPROTO_RM, RM_RATE_WINDOW_SIZE, 
            (char *) &send_window, sizeof (send_window));
        wsa_assert (rc != SOCKET_ERROR);

        rc = connect (sender_socket, (SOCKADDR *)&sasession, 
            sizeof(sasession));
        wsa_assert (rc != SOCKET_ERROR);
    }
}