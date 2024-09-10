static Xauth *get_authptr(struct sockaddr *sockname, int display)
{
    char *addr = 0;
    int addrlen = 0;
    unsigned short family;
    char hostnamebuf[256];   /* big enough for max hostname */
    char dispbuf[40];   /* big enough to hold more than 2^64 base 10 */
    int dispbuflen;

    family = FamilyLocal; /* 256 */
    switch(sockname->sa_family)
    {
#ifdef AF_INET6
    case AF_INET6:
        addr = (char *) SIN6_ADDR(sockname);
        addrlen = sizeof(*SIN6_ADDR(sockname));
        if(!IN6_IS_ADDR_V4MAPPED(SIN6_ADDR(sockname)))
        {
            if(!IN6_IS_ADDR_LOOPBACK(SIN6_ADDR(sockname)))
                family = XCB_FAMILY_INTERNET_6;
            break;
        }
        addr += 12;
        /* if v4-mapped, fall through. */
#endif
    case AF_INET:
        if(!addr)
            addr = (char *) &((struct sockaddr_in *)sockname)->sin_addr;
        addrlen = sizeof(((struct sockaddr_in *)sockname)->sin_addr);
        if(*(in_addr_t *) addr != htonl(INADDR_LOOPBACK))
            family = XCB_FAMILY_INTERNET;
        break;
    case AF_UNIX:
        break;
    default:
        return 0;   /* cannot authenticate this family */
    }

    dispbuflen = snprintf(dispbuf, sizeof(dispbuf), "%d", display);
    if(dispbuflen < 0)
        return 0;
    /* snprintf may have truncate our text */
    dispbuflen = MIN(dispbuflen, sizeof(dispbuf) - 1);

    if (family == FamilyLocal) {
        if (gethostname(hostnamebuf, sizeof(hostnamebuf)) == -1)
            return 0;   /* do not know own hostname */
        addr = hostnamebuf;
        addrlen = strlen(addr);
    }

    return XauGetBestAuthByAddr (family,
                                 (unsigned short) addrlen, addr,
                                 (unsigned short) dispbuflen, dispbuf,
                                 N_AUTH_PROTOS, authnames, authnameslen);
}