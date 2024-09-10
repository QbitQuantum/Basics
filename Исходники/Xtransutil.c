char *
TRANS(GetPeerNetworkId) (XtransConnInfo ciptr)

{
    int		family = ciptr->family;
    char	*hostname;
    char	addrbuf[256];
    char	*addr = NULL;

    switch (family)
    {
    case AF_UNSPEC:
#if defined(UNIXCONN) || defined(STREAMSCONN) || defined(LOCALCONN) || defined(OS2PIPECONN)
    case AF_UNIX:
    {
	if (gethostname (addrbuf, sizeof (addrbuf)) == 0) {
	    addrbuf[sizeof(addrbuf)-1] = '\0';
	    addr = addrbuf;
	}
	break;
    }
#endif /* defined(UNIXCONN) || defined(STREAMSCONN) || defined(LOCALCONN) || defined(OS2PIPECONN)
*/

#if defined(TCPCONN) || defined(STREAMSCONN) || defined(MNX_TCPCONN)
    case AF_INET:
    {
    char	*peer_addr = ciptr->peeraddr;
	struct sockaddr_in *saddr = (struct sockaddr_in *) peer_addr;
	struct hostent * hostp = NULL;

#if defined(SIGALRM) && !defined(_WIN32)
	/*
	 * gethostbyaddr can take a LONG time if the host does not exist.
	 * Assume that if it does not respond in NAMESERVER_TIMEOUT seconds
	 * that something is wrong and do not make the user wait.
	 * gethostbyaddr will continue after a signal, so we have to
	 * jump out of it.
	 */

	nameserver_timedout = 0;
	signal (SIGALRM, nameserver_lost);
	alarm (4);
	if (setjmp(env) == 0) {
#endif
	    hostp = gethostbyaddr ((char *) &saddr->sin_addr,
		sizeof (saddr->sin_addr), AF_INET);
#if defined(SIGALRM) && !defined(_WIN32)
	}
	alarm (0);
#endif
	if (hostp != NULL)
	  addr = hostp->h_name;
	else
	  addr = inet_ntoa (saddr->sin_addr);
	break;
    }

#endif /* defined(TCPCONN) || defined(STREAMSCONN) || MNX_TCPCONN */

#if defined(DNETCONN)
    case AF_DECnet:
    {
    char	*peer_addr = ciptr->peeraddr;
	struct sockaddr_dn *saddr = (struct sockaddr_dn *) peer_addr;
	struct nodeent *np;

	if (np = getnodebyaddr(saddr->sdn_add.a_addr,
	    saddr->sdn_add.a_len, AF_DECnet)) {
	    snprintf(addrbuf, sizeof(addrbuf), "%s:", np->n_name);
	} else {
	    snprintf(addrbuf, sizeof(addrbuf), "%s:", dnet_htoa(&saddr->sdn_add));
	}
	addr = addrbuf;
	break;
    }
#endif /* defined(DNETCONN) */

#if defined(AMRPCCONN)
    case AF_AMOEBA:
    {
	addr = "Amoeba"; /* not really used */
	break;
    }
#endif
#if defined(AMTCPCONN) && !(defined(TCPCONN) || defined(STREAMSCONN))
    case AF_INET:
    {
	if (gethostname (addrbuf, sizeof (addrbuf)) == 0) {
	    addrbuf[sizeof(addrbuf)-1] = '\0';
	    addr = addrbuf;
	} else {
	    addr = "";
	}
	break;
    }
#endif

    default:
	return (NULL);
    }


    hostname = (char *) xalloc (
	strlen (ciptr->transptr->TransName) + strlen (addr) + 2);
    strcpy (hostname, ciptr->transptr->TransName);
    strcat (hostname, "/");
    if (addr)
	strcat (hostname, addr);

    return (hostname);
}