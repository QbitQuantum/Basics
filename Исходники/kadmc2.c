/*
 * kadm_init_link
 *      receives    : name, inst, realm
 *
 * initializes client parm, the Kadm_Client structure which holds the
 * data about the connection between the server and client, the services
 * used, the locations and other fun things
 */
long /* DAMMIT! USE LONGS! */
kadm_init_link(
    char n[],
    char i[],
    char r[]
    )
{
    struct servent FAR *sep;           /* service we will talk to */
    struct hostent FAR *hop;           /* host we will talk to */
    char adm_hostname[MAXHOSTNAMELEN];

    (void) strcpy(clientParm.sname, n);
    (void) strcpy(clientParm.sinst, i);
    (void) strcpy(clientParm.krbrlm, r);
    clientParm.admin_fd = -1;
    clientParm.nSocketState = STATE_NONE;

    /* set up the admin_addr - fetch name of admin host */
    if (krb_get_admhst(adm_hostname, clientParm.krbrlm, 1) != KSUCCESS)
        return KADM_NO_HOST;
    bzero((char *) &clientParm.admin_addr,
          sizeof(clientParm.admin_addr));
    if ((hop = GETHOSTBYNAME(adm_hostname)) == NULL)
        return KADM_UNK_HOST;  /* couldnt find the admin servers address */

    bcopy(hop->h_addr, &clientParm.admin_addr.sin_addr, hop->h_length);
    clientParm.admin_addr.sin_family = hop->h_addrtype;

    if (sep = getservbyname(KADM_SNAME, "tcp"))
        clientParm.admin_addr.sin_port = sep->s_port;
    else if (KADM_DEFAULT_PORT) /* set to 0 to turn this off */
        clientParm.admin_addr.sin_port = htons(KADM_DEFAULT_PORT);
    else
        return KADM_NO_SERV;   /* couldnt find the admin service */

    return KADM_SUCCESS;
}                                      /* procedure kadm_init_link */