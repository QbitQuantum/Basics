int scamper_ip4_openraw(void)
{
    int fd = -1;

#if defined(WITHOUT_PRIVSEP)
    int hdr = 1;
    if((fd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) == -1)
    {
        printerror(errno, strerror, __func__, "could not open socket");
        goto err;
    }

    if(setsockopt(fd, IPPROTO_IP, IP_HDRINCL, (void *)&hdr, sizeof(hdr)) == -1)
    {
        printerror(errno, strerror, __func__, "could not IP_HDRINCL");
        goto err;
    }
#else
    if((fd = scamper_privsep_open_rawip()) == -1)
    {
        printerror(errno, strerror, __func__, "could not open socket");
        goto err;
    }
#endif

    return fd;

err:
    if(fd != -1) scamper_ip4_close(fd);
    return -1;
}