int sim_parse_addr (const char *cptr, char *host, size_t host_len, const char *default_host, char *port, size_t port_len, const char *default_port, const char *validate_addr)
{
char gbuf[CBUFSIZE];
char *hostp, *portp;
char *endc;
unsigned long portval;

if ((cptr == NULL) || (*cptr == 0))
    return SCPE_ARG;
if ((host != NULL) && (host_len != 0))
    memset (host, 0, host_len);
if ((port != NULL) && (port_len != 0))
    memset (port, 0, port_len);
gbuf[sizeof(gbuf)-1] = '\0';
strncpy (gbuf, cptr, sizeof(gbuf)-1);
hostp = gbuf;                                           /* default addr */
portp = NULL;
if ((portp = strrchr (gbuf, ':')) &&                    /* x:y? split */
    (NULL == strchr (portp, ']'))) {
    *portp++ = 0;
    if (*portp == '\0')
        portp = (char *)default_port;
    }
else {                                                  /* No colon in input */
    portp = gbuf;                                       /* Input is the port specifier */
    hostp = (char *)default_host;                       /* host is defaulted if provided */
    }
if (portp != NULL) {
    portval = strtoul(portp, &endc, 10);
    if ((*endc == '\0') && ((portval == 0) || (portval > 65535)))
        return SCPE_ARG;                                /* numeric value too big */
    if (*endc != '\0') {
        struct servent *se = getservbyname(portp, "tcp");

        if (se == NULL)
            return SCPE_ARG;                            /* invalid service name */
        }
    }
if (port)                                               /* port wanted? */
    if (portp != NULL) {
        if (strlen(portp) >= port_len)
            return SCPE_ARG;                            /* no room */
        else
            strcpy (port, portp);
        }
if (hostp != NULL) {
    if (']' == hostp[strlen(hostp)-1]) {
        if ('[' != hostp[0])
            return SCPE_ARG;                            /* invalid domain literal */
        /* host may be the const default_host so move to temp buffer before modifying */
        strncpy(gbuf, hostp+1, sizeof(gbuf)-1);         /* remove brackets from domain literal host */
        hostp = gbuf;
        hostp[strlen(hostp)-1] = '\0';
        }
    }
if (host)                                               /* host wanted? */
    if (hostp != NULL) {
        if (strlen(hostp) >= host_len)
            return SCPE_ARG;                            /* no room */
        else
            strcpy (host, hostp);
        }
if (validate_addr) {
    struct addrinfo *ai_host, *ai_validate, *ai;
    int status;

    if (hostp == NULL)
        return SCPE_ARG;
    if (getaddrinfo(hostp, NULL, NULL, &ai_host))
        return SCPE_ARG;
    if (getaddrinfo(validate_addr, NULL, NULL, &ai_validate)) {
        freeaddrinfo (ai_host);
        return SCPE_ARG;
        }
    status = SCPE_ARG;
    for (ai = ai_host; ai != NULL; ai = ai->ai_next) {
        if ((ai->ai_addrlen == ai_validate->ai_addrlen) &&
            (ai->ai_family == ai_validate->ai_family) &&
            (0 == memcmp (ai->ai_addr, ai_validate->ai_addr, ai->ai_addrlen))) {
            status = SCPE_OK;
            break;
            }
        }
    if (status != SCPE_OK) {
        /* be generous and allow successful validations against variations of localhost addresses */
        if (((0 == strcmp("127.0.0.1", hostp)) &&
             (0 == strcmp("::1", validate_addr))) ||
            ((0 == strcmp("127.0.0.1", validate_addr)) &&
             (0 == strcmp("::1", hostp))))
            status = SCPE_OK;
        }
    freeaddrinfo (ai_host);
    freeaddrinfo (ai_validate);
    return status;
    }
return SCPE_OK;
}