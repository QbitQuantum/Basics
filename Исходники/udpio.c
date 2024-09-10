int udpioSend(UDPIO *up, UINT32 ip, int port, char *buf, int buflen)
{
int sent;
LOGIO *lp;
struct sockaddr_in addr;
static int alen = sizeof(struct sockaddr_in);
static char *fid = "udpioSend";

    if (up == NULL || buf == NULL) {
        errno = EINVAL;
        lp = (up == NULL) ? NULL : up->lp;
        logioMsg(lp, LOG_ERR, "%s: NULL input not allowed", fid);
        return -1;
    }

    memset((void *) &addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = htonl(ip);
    addr.sin_port        = htons((short) port);

    sent = SENDTO(up->sd, buf, buflen, 0, &addr, alen);
    UpdateStats(&up->stats.xmit, sent, utilTimeStamp());

    return sent;
}