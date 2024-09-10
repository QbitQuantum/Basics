/** void connect_server()
 *  Attempts to connect to all configured servers.
 */
int connect_server(int initial_id)
{
    int attempts = 2;
    int rc = initial_id;


    /* Checking if the initial is zero, meaning we have to rotate to the
     * beginning.
     */
    if(agt->rip[initial_id] == NULL)
    {
        rc = 0;
        initial_id = 0;
    }


    /* Closing socket if available. */
    if(agt->sock >= 0)
    {
        sleep(1);
        CloseSocket(agt->sock);
        agt->sock = -1;

        if(agt->rip[1])
        {
            verbose("%s: INFO: Closing connection to server (%s:%d).",
                    ARGV0,
                    agt->rip[rc],
                    agt->port);
        }

    }


    while(agt->rip[rc])
    {
        char *tmp_str;

        /* Checking if we have a hostname. */
        tmp_str = strchr(agt->rip[rc], '/');
        if(tmp_str)
        {
            char *f_ip;
            *tmp_str = '\0';

            f_ip = OS_GetHost(agt->rip[rc], 5);
            if(f_ip)
            {
                char ip_str[128];
                ip_str[127] = '\0';

                snprintf(ip_str, 127, "%s/%s", agt->rip[rc], f_ip);

                free(f_ip);
                free(agt->rip[rc]);

                os_strdup(ip_str, agt->rip[rc]);
                tmp_str = strchr(agt->rip[rc], '/');
                tmp_str++;
            }
            else
            {
                merror("%s: WARN: Unable to get hostname for '%s'.",
                       ARGV0, agt->rip[rc]);
                *tmp_str = '/';
                tmp_str++;
            }
        }
        else
        {
            tmp_str = agt->rip[rc];
        }


        verbose("%s: INFO: Trying to connect to server (%s:%d).", ARGV0,
                agt->rip[rc],
                agt->port);

        /* IPv6 address: */
        if(strchr(tmp_str,':') != NULL)
        {
            verbose("%s: INFO: Using IPv6 for: %s .", ARGV0, tmp_str);
            agt->sock = OS_ConnectUDP(agt->port, tmp_str, 1);
        }
        else
        {
            verbose("%s: INFO: Using IPv4 for: %s .", ARGV0, tmp_str);
            agt->sock = OS_ConnectUDP(agt->port, tmp_str, 0);
        }

        if(agt->sock < 0)
        {
            agt->sock = -1;
            merror(CONNS_ERROR, ARGV0, tmp_str);
            rc++;

            if(agt->rip[rc] == NULL)
            {
                attempts += 10;

                /* Only log that if we have more than 1 server configured. */
                if(agt->rip[1])
                    merror("%s: ERROR: Unable to connect to any server.",ARGV0);

                sleep(attempts);
                rc = 0;
            }
        }
        else
        {
            /* Setting socket non-blocking on HPUX */
            #ifdef HPUX
            //fcntl(agt->sock, O_NONBLOCK);
            #endif

            #ifdef WIN32
            int bmode = 1;

            /* Setting socket to non-blocking */
            ioctlsocket(agt->sock, FIONBIO, (u_long FAR*) &bmode);
            #endif

            agt->rip_id = rc;
            return(1);
        }
    }

    return(0);
}