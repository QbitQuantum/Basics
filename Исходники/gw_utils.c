/*
 * Set IP address in socket structure in_addr
 *
 * @param a     Pointer to a struct in_addr into which the address is written
 * @param p     The hostname to lookup
 * @return      1 on success, 0 on failure
 */
int
setipaddress(struct in_addr *a, char *p)
{
#ifdef __USE_POSIX
    struct addrinfo *ai = NULL, hint;
    int rc;
    struct sockaddr_in *res_addr;
    memset(&hint, 0, sizeof (hint));

    hint.ai_socktype = SOCK_STREAM;

    /*
     * This is for the listening socket, matching INADDR_ANY only for now.
     * For future specific addresses bind, a dedicated routine woulbd be better
     */

    if (strcmp(p, "0.0.0.0") == 0)
    {
        hint.ai_flags = AI_PASSIVE;
        hint.ai_family = AF_UNSPEC;
        if ((rc = getaddrinfo(p, NULL, &hint, &ai)) != 0)
        {
            MXS_ERROR("Failed to obtain address for host %s, %s",
                      p,
                      gai_strerror(rc));

            return 0;
        }
    }
    else
    {
        hint.ai_flags = AI_CANONNAME;
        hint.ai_family = AF_INET;

        if ((rc = getaddrinfo(p, NULL, &hint, &ai)) != 0)
        {
            MXS_ERROR("Failed to obtain address for host %s, %s",
                      p,
                      gai_strerror(rc));

            return 0;
        }
    }

    /* take the first one */
    if (ai != NULL)
    {
        res_addr = (struct sockaddr_in *)(ai->ai_addr);
        memcpy(a, &res_addr->sin_addr, sizeof(struct in_addr));

        freeaddrinfo(ai);

        return 1;
    }
#else
    struct hostent *h;

    spinlock_acquire(&tmplock);
    h = gethostbyname(p);
    spinlock_release(&tmplock);

    if (h == NULL)
    {
        if ((a->s_addr = inet_addr(p)) == -1)
        {
            MXS_ERROR("gethostbyname failed for [%s]", p);

            return 0;
        }
    }
    else
    {
        /* take the first one */
        memcpy(a, h->h_addr, h->h_length);

        return 1;
    }
#endif
    return 0;
}