/* we receive a connection acknowledgement from the server,
 * consisting of nothing more than a status report. If success,
 * then we initiate authentication method */
static pmix_status_t recv_connect_ack(int sd)
{
    pmix_status_t reply;
    pmix_status_t rc;
    struct timeval tv, save;
    pmix_socklen_t sz;
    bool sockopt = true;
    uint32_t u32;
    char nspace[PMIX_MAX_NSLEN+1];

    pmix_output_verbose(2, pmix_globals.debug_output,
                        "pmix: RECV CONNECT ACK FROM SERVER");

    /* get the current timeout value so we can reset to it */
    sz = sizeof(save);
    if (0 != getsockopt(sd, SOL_SOCKET, SO_RCVTIMEO, (void*)&save, &sz)) {
        if (ENOPROTOOPT == errno) {
            sockopt = false;
        } else {
           return PMIX_ERR_UNREACH;
       }
   } else {
        /* set a timeout on the blocking recv so we don't hang */
        tv.tv_sec  = 2;
        tv.tv_usec = 0;
        if (0 != setsockopt(sd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv))) {
            pmix_output_verbose(2, pmix_globals.debug_output,
                                "pmix: recv_connect_ack could not setsockopt SO_RCVTIMEO");
            return PMIX_ERR_UNREACH;
        }
    }

    /* receive the status reply */
    rc = pmix_ptl_base_recv_blocking(sd, (char*)&u32, sizeof(uint32_t));
    if (PMIX_SUCCESS != rc) {
        PMIX_ERROR_LOG(rc);
        return rc;
    }
    reply = ntohl(u32);

    if (PMIX_PROC_IS_CLIENT) {
        /* see if they want us to do the handshake */
        if (PMIX_ERR_READY_FOR_HANDSHAKE == reply) {
            PMIX_PSEC_CLIENT_HANDSHAKE(rc, pmix_client_globals.myserver, sd);
            if (PMIX_SUCCESS != rc) {
                return rc;
            }
        } else if (PMIX_SUCCESS != reply) {
            return reply;
        }
        pmix_output_verbose(2, pmix_globals.debug_output,
                            "pmix: RECV CONNECT CONFIRMATION");

        /* receive our index into the server's client array */
        rc = pmix_ptl_base_recv_blocking(sd, (char*)&u32, sizeof(uint32_t));
        if (PMIX_SUCCESS != rc) {
            PMIX_ERROR_LOG(rc);
            return rc;
        }
        pmix_globals.pindex = ntohl(u32);
    } else {  // we are a tool
        /* if the status indicates an error, then we are done */
        if (PMIX_SUCCESS != reply) {
            PMIX_ERROR_LOG(reply);
            return reply;
        }
        /* recv our nspace */
        rc = pmix_ptl_base_recv_blocking(sd, (char*)&pmix_globals.myid.nspace, PMIX_MAX_NSLEN+1);
        if (PMIX_SUCCESS != rc) {
            PMIX_ERROR_LOG(rc);
            return rc;
        }
        /* our rank is always zero */
        pmix_globals.myid.rank = 0;

        /* get the server's nspace and rank so we can send to it */
        pmix_client_globals.myserver->info = PMIX_NEW(pmix_rank_info_t);
        pmix_client_globals.myserver->nptr = PMIX_NEW(pmix_nspace_t);
        pmix_ptl_base_recv_blocking(sd, (char*)nspace, PMIX_MAX_NSLEN+1);
        pmix_client_globals.myserver->nptr->nspace = strdup(nspace);
        pmix_client_globals.myserver->info->pname.nspace = strdup(nspace);
        pmix_ptl_base_recv_blocking(sd, (char*)&(pmix_client_globals.myserver->info->pname.rank), sizeof(int));

        pmix_output_verbose(2, pmix_globals.debug_output,
                            "pmix: RECV CONNECT CONFIRMATION FOR TOOL %s:%d FROM SERVER %s:%d",
                            pmix_globals.myid.nspace, pmix_globals.myid.rank,
                            pmix_client_globals.myserver->info->pname.nspace,
                            pmix_client_globals.myserver->info->pname.rank);

        /* get the returned status from the security handshake */
        pmix_ptl_base_recv_blocking(sd, (char*)&reply, sizeof(pmix_status_t));
        if (PMIX_SUCCESS != reply) {
            /* see if they want us to do the handshake */
            if (PMIX_ERR_READY_FOR_HANDSHAKE == reply) {
                PMIX_PSEC_CLIENT_HANDSHAKE(reply, pmix_client_globals.myserver, sd);
                if (PMIX_SUCCESS != reply) {
                    return reply;
                }
                /* if the handshake succeeded, then fall thru to the next step */
            } else {
                return reply;
            }
        }
    }

    if (sockopt) {
        if (0 != setsockopt(sd, SOL_SOCKET, SO_RCVTIMEO, &save, sz)) {
            return PMIX_ERR_UNREACH;
        }
    }

    return PMIX_SUCCESS;
}