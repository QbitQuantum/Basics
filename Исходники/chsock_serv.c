static int serve_client(CHSOCK *chsock, int sock)
{
    int i, stat = 0;
    char *inet_ntoa();
    char *hostname;  /* points to the remote host's name string */

    CLIENT *client = NULL;
    struct hostent *hp; /* pointer to host info for remote host */

    close(chsock->ls); /* Close the listen socket inherited from the daemon. */

    /* Look up the host information for the remote host
     * that we have connected with.  Its internet address
     * was returned by the accept call, in the main
     * daemon loop above.
     */
    hp = gethostbyaddr ((char *) &chsock->peeraddr_in.sin_addr,
       sizeof (struct in_addr),
       chsock->peeraddr_in.sin_family);

    if (hp == NULL) 
    {
        /* The information is unavailable for the remote
         * host.  Just format its internet address to be
         * printed out in the logging information.  The
         * address will be shown in "internet dot format".
         */
        hostname = inet_ntoa(chsock->peeraddr_in.sin_addr);
    } 
    else 
    {
        hostname = hp->h_name;  /* point to host's name */
    }

    /* The port number must be converted first to host byte
     * order before printing.  On most hosts, this is not
     * necessary, but the ntohs() call is included here so
     * that this program could easily be ported to a host
     * that does require it.
     */
    fprintf(stderr, "%s: %s: info: startup from %s port %u\n",
        timestamp(), ProgName, hostname, ntohs(chsock->peeraddr_in.sin_port));

    /* Set the socket for a lingering, graceful close.
     * This will cause a final close of this socket to wait until all of the
     * data sent on it has been received by the remote host.
     */
    chsock->linger.l_onoff  =1;
    chsock->linger.l_linger =1;
    if (setsockopt(sock, SOL_SOCKET, SO_LINGER, &chsock->linger,
        sizeof(struct linger)) == -1) 
    {
        fprintf(stderr, "%s: %s: error: set socket options failed: %s\n", 
            timestamp(), ProgName, strerror(errno)); 
        return 1;
    }

    for ( i = 0; i < chsock->conf->nclients; i++ )
    {
        client = chsock->conf->clients[i];
        if ( !strncmp(client->hostname, hostname, strlen(client->hostname)) )
        {
            break;
        }
    }

    if ( i == chsock->conf->nclients )
    {
        fprintf(stderr, "%s: %s: info: refused connection with client %s: ", 
            timestamp(), ProgName, hostname); 
        fprintf(stderr, "not in configuration\n");
        return 1;
    }

    if ( client->recv_from )
    {
        fprintf(stderr, "%s: %s: info: receive from client \"%s\" enabled\n",
            timestamp(), ProgName, hostname); 
        return serve_client_in(client,sock,chsock->conf->datadir,hostname);
    }
    else if ( client->send_to )
    {
        fprintf(stderr, "%s: %s: info: send to client \"%s\" enabled\n",
            timestamp(), ProgName, hostname); 
        return serve_client_out(client,sock,chsock->conf->datadir,hostname);
    }

    fprintf(stderr, "%s: %s: error: connection with %s aborted: ",
            timestamp(), ProgName, hostname); 
    fprintf(stderr, "parameters 'recv_from' and 'send_to' not set in config\n");
    return 1;

} /* serve_client() */