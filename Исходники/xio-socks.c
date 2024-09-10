/* perform socks4 client dialog on existing FD.
   Called within fork/retry loop, after connect() */
int _xioopen_socks4_connect(struct single *xfd,
                            struct socks4 *sockhead,
                            size_t headlen,
                            int level) {
    ssize_t bytes;
    int result;
    unsigned char buff[SIZEOF_STRUCT_SOCKS4];
    struct socks4 *replyhead = (struct socks4 *)buff;
    char *destdomname = NULL;

    /* send socks header (target addr+port, +auth) */
#if WITH_MSGLEVEL <= E_INFO
    if (ntohl(sockhead->dest) <= 0x000000ff) {
        destdomname = strchr(sockhead->userid, '\0')+1;
    }
    Info11("sending socks4%s request VN=%d DC=%d DSTPORT=%d DSTIP=%d.%d.%d.%d USERID=%s%s%s",
           destdomname?"a":"",
           sockhead->version, sockhead->action, ntohs(sockhead->port),
           ((unsigned char *)&sockhead->dest)[0],
           ((unsigned char *)&sockhead->dest)[1],
           ((unsigned char *)&sockhead->dest)[2],
           ((unsigned char *)&sockhead->dest)[3],
           sockhead->userid,
           destdomname?" DESTNAME=":"",
           destdomname?destdomname:"");
#endif /* WITH_MSGLEVEL <= E_INFO */
#if WITH_MSGLEVEL <= E_DEBUG
    {
        char *msgbuff;
        if ((msgbuff = Malloc(3*headlen)) != NULL) {
            xiohexdump((const unsigned char *)sockhead, headlen, msgbuff);
            Debug1("sending socks4(a) request data %s", msgbuff);
        }
    }
#endif /* WITH_MSGLEVEL <= E_DEBUG */
    if (writefull(xfd->fd, sockhead, headlen) < 0) {
        Msg4(level, "write(%d, %p, "F_Zu"): %s",
             xfd->fd, sockhead, headlen, strerror(errno));
        if (Close(xfd->fd) < 0) {
            Info2("close(%d): %s", xfd->fd, strerror(errno));
        }
        return STAT_RETRYLATER;	/* retry complete open cycle */
    }

    bytes = 0;
    Info("waiting for socks reply");
    while (bytes >= 0) {	/* loop over answer chunks until complete or error */
        /* receive socks answer */
        do {
            result = Read(xfd->fd, buff+bytes, SIZEOF_STRUCT_SOCKS4-bytes);
        } while (result < 0 && errno == EINTR);
        if (result < 0) {
            Msg4(level, "read(%d, %p, "F_Zu"): %s",
                 xfd->fd, buff+bytes, SIZEOF_STRUCT_SOCKS4-bytes,
                 strerror(errno));
            if (Close(xfd->fd) < 0) {
                Info2("close(%d): %s", xfd->fd, strerror(errno));
            }
        }
        if (result == 0) {
            Msg(level, "read(): EOF during read of socks reply, peer might not be a socks4 server");
            if (Close(xfd->fd) < 0) {
                Info2("close(%d): %s", xfd->fd, strerror(errno));
            }
            return STAT_RETRYLATER;
        }
#if WITH_MSGLEVEL <= E_DEBUG
        {
            char msgbuff[3*SIZEOF_STRUCT_SOCKS4];
            * xiohexdump((const unsigned char *)replyhead+bytes, result, msgbuff)
                = '\0';
            Debug2("received socks4 reply data (offset "F_Zd"): %s", bytes, msgbuff);
        }
#endif /* WITH_MSGLEVEL <= E_DEBUG */
        bytes += result;
        if (bytes == SIZEOF_STRUCT_SOCKS4) {
            Debug1("received all "F_Zd" bytes", bytes);
            break;
        }
        Debug2("received %d bytes, waiting for "F_Zu" more bytes",
               result, SIZEOF_STRUCT_SOCKS4-bytes);
    }
    if (result <= 0) {	/* we had a problem while reading socks answer */
        return STAT_RETRYLATER;	/* retry complete open cycle */
    }

    Info7("received socks reply VN=%u CD=%u DSTPORT=%u DSTIP=%u.%u.%u.%u",
          replyhead->version, replyhead->action, ntohs(replyhead->port),
          ((uint8_t *)&replyhead->dest)[0],
          ((uint8_t *)&replyhead->dest)[1],
          ((uint8_t *)&replyhead->dest)[2],
          ((uint8_t *)&replyhead->dest)[3]);
    if (replyhead->version != 0) {
        Warn1("socks: reply code version is not 0 (%d)",
              replyhead->version);
    }

    switch (replyhead->action) {
    case SOCKS_CD_GRANTED:
        /* Notice("socks: connect request succeeded"); */
#if 0
        if (Getsockname(xfd->fd, (struct sockaddr *)&us, &uslen) < 0) {
            Warn4("getsockname(%d, %p, {%d}): %s",
                  xfd->fd, &us, uslen, strerror(errno));
        }
        Notice1("successfully connected from %s via socks4",
                sockaddr_info((struct sockaddr *)&us, infobuff, sizeof(infobuff)));
#else
        Notice("successfully connected via socks4");
#endif
        break;

    case SOCKS_CD_FAILED:
        Msg(level, "socks: connect request rejected or failed");
        return STAT_RETRYLATER;

    case SOCKS_CD_NOIDENT:
        Msg(level, "socks: ident refused by client");
        return STAT_RETRYLATER;

    case SOCKS_CD_IDENTFAILED:
        Msg(level, "socks: ident failed");
        return STAT_RETRYLATER;

    default:
        Msg1(level, "socks: undefined status %u", replyhead->action);
    }

    return STAT_OK;
}