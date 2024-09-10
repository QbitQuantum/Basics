PING *ping_init (int type, int ident)
{
    int fd;

    struct protoent *proto;

    PING *p;

    /* Initialize raw ICMP socket */
    proto = getprotobyname ("icmp");
    if (!proto)
    {
        fprintf (stderr, "ping: unknown protocol icmp.\n");
        return NULL;
    }

    fd = socket (AF_INET, SOCK_RAW, proto->p_proto);
    if (fd < 0)
    {
        if (errno == EPERM)
            fprintf (stderr, "ping: ping must run as root\n");
        return NULL;
    }

    /* Allocate PING structure and initialize it to default values */
    p = malloc (sizeof (*p));
    if (!p)
    {
        close (fd);
        return p;
    }

    memset (p, 0, sizeof (*p));

    p->ping_fd = fd;
    p->ping_type = type;
    p->ping_count = 0;
    p->ping_interval = PING_DEFAULT_INTERVAL;
    p->ping_datalen = sizeof (icmphdr_t);
    /* Make sure we use only 16 bits in this field, id for icmp is a u_short.  */
    p->ping_ident = ident & 0xFFFF;
    p->ping_cktab_size = PING_CKTABSIZE;
    gettimeofday (&p->ping_start_time, NULL);
    return p;
}