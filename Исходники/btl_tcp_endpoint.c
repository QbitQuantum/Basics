/*
 *  Start a connection to the endpoint. This will likely not complete,
 *  as the socket is set to non-blocking, so register for event
 *  notification of connect completion. On connection we send
 *  our globally unique process identifier to the endpoint and wait for
 *  the endpoints response.
 */
static int mca_btl_tcp_endpoint_start_connect(mca_btl_base_endpoint_t* btl_endpoint)
{
    int rc,flags;
    struct sockaddr_storage endpoint_addr;
    /* By default consider a IPv4 connection */
    uint16_t af_family = AF_INET;
    opal_socklen_t addrlen = sizeof(struct sockaddr_in);
    
#if OPAL_WANT_IPV6
    if (AF_INET6 == btl_endpoint->endpoint_addr->addr_family) {
        af_family = AF_INET6;
        addrlen = sizeof (struct sockaddr_in6);
    }
#endif
    
    btl_endpoint->endpoint_sd = socket(af_family, SOCK_STREAM, 0);
    if (btl_endpoint->endpoint_sd < 0) {
        btl_endpoint->endpoint_retries++;
        return OMPI_ERR_UNREACH;
    }

    /* setup socket buffer sizes */
    mca_btl_tcp_set_socket_options(btl_endpoint->endpoint_sd);

    /* setup event callbacks */
    mca_btl_tcp_endpoint_event_init(btl_endpoint);

    /* setup the socket as non-blocking */
    if((flags = fcntl(btl_endpoint->endpoint_sd, F_GETFL, 0)) < 0) {
        BTL_ERROR(("fcntl(F_GETFL) failed: %s (%d)", 
                   strerror(opal_socket_errno), opal_socket_errno));
    } else {
        flags |= O_NONBLOCK;
        if(fcntl(btl_endpoint->endpoint_sd, F_SETFL, flags) < 0)
            BTL_ERROR(("fcntl(F_SETFL) failed: %s (%d)", 
                       strerror(opal_socket_errno), opal_socket_errno));
    }

    /* start the connect - will likely fail with EINPROGRESS */
    mca_btl_tcp_proc_tosocks(btl_endpoint->endpoint_addr, &endpoint_addr);

    opal_output_verbose(20, mca_btl_base_output, 
                        "btl: tcp: attempting to connect() to %s address %s on port %d",
                        ORTE_NAME_PRINT(&btl_endpoint->endpoint_proc->proc_ompi->proc_name),
                        opal_net_get_hostname((struct sockaddr*) &endpoint_addr),
                        ntohs(btl_endpoint->endpoint_addr->addr_port));

    if(connect(btl_endpoint->endpoint_sd, (struct sockaddr*)&endpoint_addr, addrlen) < 0) {
        /* non-blocking so wait for completion */
        if(opal_socket_errno == EINPROGRESS || opal_socket_errno == EWOULDBLOCK) {
            btl_endpoint->endpoint_state = MCA_BTL_TCP_CONNECTING;
            opal_event_add(&btl_endpoint->endpoint_send_event, 0);
            return OMPI_SUCCESS;
        }
        {
            char *address;
            address = opal_net_get_hostname((struct sockaddr*) &endpoint_addr);
            BTL_PEER_ERROR( btl_endpoint->endpoint_proc->proc_ompi,
                          ( "Unable to connect to the peer %s on port %d: %s\n",
                            address,
                           btl_endpoint->endpoint_addr->addr_port, strerror(opal_socket_errno) ) );
        }
        mca_btl_tcp_endpoint_close(btl_endpoint);
        btl_endpoint->endpoint_retries++;
        return OMPI_ERR_UNREACH;
    }

    /* send our globally unique process identifier to the endpoint */
    if((rc = mca_btl_tcp_endpoint_send_connect_ack(btl_endpoint)) == OMPI_SUCCESS) {
        btl_endpoint->endpoint_state = MCA_BTL_TCP_CONNECT_ACK;
        opal_event_add(&btl_endpoint->endpoint_recv_event, 0);
    } else {
        mca_btl_tcp_endpoint_close(btl_endpoint);
    }
    return rc;
}