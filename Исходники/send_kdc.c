/*
 * try to send out and receive message.
 * return 1 on success, 0 on failure
 */
static
send_recv(KTEXT pkt, KTEXT rpkt, SOCKET f,
          struct sockaddr_in *_to, struct hostent *addrs)
{
    fd_set readfds;
    register struct hostent *hp;
    struct sockaddr_in from;
    int sin_size;
    int numsent;
    int ret = SOCKET_ERROR;

    if (krb_debug) {
        if (_to->sin_family == AF_INET)
            kdebug("Sending message to %s...", inet_ntoa(_to->sin_addr));
        else
            kdebug("Sending message...");
    }

    if ((numsent = sendto(f,(char *)(pkt->dat), pkt->length, 0,
                          (struct sockaddr *)_to, S_AD_SZ)) != pkt->length) {
        if (krb_debug)
            kdebug("sent only %d/%d\n", numsent, pkt->length);
        return 0;
    }

    if (krb_debug) {
        kdebug("Sent\nWaiting for reply...");
    }
    FD_ZERO(&readfds);
    FD_SET(f, &readfds);
    WSASetLastError(0);
    /* select - either recv is ready, or timeout */
    /* see if timeout or error or wrong descriptor */
    ret = select(0, &readfds, (fd_set *)0, (fd_set *)0, &timeout);
    if (ret != 1 || !FD_ISSET(f, &readfds)) {
        /* I don't think the WinSock blocking stuff is needed... */
        if (WSAIsBlocking()) {
            WSACancelBlockingCall();
        }
        if (krb_debug) {
            kdebug("select failed: ret=%d, readfds=%x, errno=%d",
                   ret, readfds, WSAGetLastError());
        }
        return 0;
    }

    sin_size = sizeof(from);
    if ((numsent = (recvfrom(f, (char *)(rpkt->dat), sizeof(rpkt->dat), 0,
                             (struct sockaddr *)&from, &sin_size)))
        != rpkt->length) {
        if (numsent < 0) {
            if (krb_debug)
                kdebug("recvfrom : Error %d\n", WSAGetLastError());
            return 0;
        }
    }
    if (krb_debug) {
        kdebug("received packet from %s\n", inet_ntoa(from.sin_addr));
    }

    for (hp = addrs; hp->h_name != 0; hp++) {
        if (!memcmp(hp->h_addr, &from.sin_addr.s_addr,
                    hp->h_length))
        {
            if (krb_debug) {
                kdebug("Received it\n");
            }
            return 1;
        }
        if (krb_debug)
            kdebug("packet not from %x\n", hp->h_addr);
    }

    if (krb_debug)
        kdebug("%s: received packet from wrong host! (%x)\n",
               "send_to_kdc(send_rcv)", from.sin_addr.s_addr);
    return 0;
}