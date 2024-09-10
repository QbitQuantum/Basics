/*----------------------------------------------------------------------*
                         rtp_net_setmembership
 *----------------------------------------------------------------------*/
int rtp_net_setmembership (RTP_HANDLE sockHandle, unsigned char * ipAddr, int type, unsigned int onBool)
{
#ifdef LINUXTOBEIMPLEMENTED
    struct sockaddr_in localAddr;
    int result;
    int localLen;
    struct ip_mreq mcreq;
    unsigned long in_addr = 0;
    
    localLen = sizeof(localAddr);
    memset(&localAddr, 0, localLen);
    memset( ( void * )&mcreq, 0, sizeof( struct ip_mreq ) );
    
    if (ipAddr)
    {
        unsigned char *ptr = (unsigned char *) &in_addr;
        
        if (type == RTP_NET_TYPE_IPV4)
        {
            ptr[0] = ipAddr[0];
            ptr[1] = ipAddr[1];
            ptr[2] = ipAddr[2];
            ptr[3] = ipAddr[3];
        }
        else
        {
            /* ----------------------------------- */
            /* RTP_NET_TYPE_IPV6 not yet supported */
            /* ----------------------------------- */
            return (-1);
        }
    }
    else
    {
        in_addr = INADDR_ANY;
    }

#ifdef RTP_DEBUG
    /* ----------------------------------- */
    /*  Clear the error state by setting   */
    /*  to 0.                              */
    /* ----------------------------------- */
    WSASetLastError (0);
#endif

    if (getsockname ((SOCKET) sockHandle, (struct sockaddr *) &localAddr, (int *) &localLen) != 0)
    {
#ifdef RTP_DEBUG
        result = WSAGetLastError();
        RTP_DEBUG_OUTPUT_STR("rtp_net_setmembership: error returned ");
        RTP_DEBUG_OUTPUT_INT(result);
        RTP_DEBUG_OUTPUT_STR(".\n");
#endif
        return (-1);
    }
    
    memmove(&mcreq.imr_multiaddr.s_addr, &in_addr, 4);
    memmove(&mcreq.imr_interface.s_addr, &localAddr.sin_addr.s_addr, 4); 

    if (onBool)
    {
        result = setsockopt((int) sockHandle, IPPROTO_IP, 
                            IP_ADD_MEMBERSHIP, (const char *)&mcreq, 
                            sizeof( struct ip_mreq ));
    }
    else
    {
        result = setsockopt((int) sockHandle, IPPROTO_IP, 
                            IP_DROP_MEMBERSHIP, (const char *)&mcreq, 
                            sizeof( struct ip_mreq ));
    }
        
    if (result != 0)
    {
#ifdef RTP_DEBUG
        result = WSAGetLastError();
        RTP_DEBUG_OUTPUT_STR("rtp_net_setmembership: error returned ");
        RTP_DEBUG_OUTPUT_INT(result);
        RTP_DEBUG_OUTPUT_STR(".\n");
#endif
        return (-1);
    }
    return (0);
#else
	return (0);
#endif
}