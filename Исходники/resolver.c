NOEXPORT int getaddrinfo(const char *node, const char *service,
        const struct addrinfo *hints, struct addrinfo **res) {
    struct hostent *h;
#ifndef _WIN32_WCE
    struct servent *p;
#endif
    u_short port;
    struct addrinfo *ai;
    int retval;
    char *tmpstr;

    if(!node)
        node=hints->ai_flags&AI_PASSIVE ? DEFAULT_ANY : DEFAULT_LOOPBACK;
#if defined(USE_WIN32) && !defined(_WIN32_WCE)
    if(s_getaddrinfo)
        return s_getaddrinfo(node, service, hints, res);
#endif
    /* decode service name */
    port=htons((u_short)strtol(service, &tmpstr, 10));
    if(tmpstr==service || *tmpstr) { /* not a number */
#ifdef _WIN32_WCE
        return EAI_NONAME;
#else /* defined(_WIN32_WCE) */
        p=getservbyname(service, "tcp");
        if(!p)
            return EAI_NONAME;
        port=(u_short)p->s_port;
#endif /* defined(_WIN32_WCE) */
    }

    /* allocate addrlist structure */
    ai=str_alloc(sizeof(struct addrinfo));
    if(hints)
        memcpy(ai, hints, sizeof(struct addrinfo));

    /* try to decode numerical address */
#if defined(USE_IPv6) && !defined(USE_WIN32)
    ai->ai_family=AF_INET6;
    ai->ai_addrlen=sizeof(struct sockaddr_in6);
    ai->ai_addr=str_alloc((size_t)ai->ai_addrlen);
    ai->ai_addr->sa_family=AF_INET6;
    if(inet_pton(AF_INET6, node,
            &((struct sockaddr_in6 *)ai->ai_addr)->sin6_addr)>0) {
#else
    ai->ai_family=AF_INET;
    ai->ai_addrlen=sizeof(struct sockaddr_in);
    ai->ai_addr=str_alloc(ai->ai_addrlen);
    ai->ai_addr->sa_family=AF_INET;
    ((struct sockaddr_in *)ai->ai_addr)->sin_addr.s_addr=inet_addr(node);
    if(((struct sockaddr_in *)ai->ai_addr)->sin_addr.s_addr+1) {
    /* (signed)((struct sockaddr_in *)ai->ai_addr)->sin_addr.s_addr!=-1 */
#endif
        ((struct sockaddr_in *)ai->ai_addr)->sin_port=port;
        *res=ai;
        return 0; /* numerical address resolved */
    }
    str_free(ai->ai_addr);
    str_free(ai);

    /* not numerical: need to call resolver library */
    *res=NULL;
    ai=NULL;
    CRYPTO_w_lock(stunnel_locks[LOCK_INET]);
#ifdef HAVE_GETHOSTBYNAME2
    h=gethostbyname2(node, AF_INET6);
    if(h) /* some IPv6 addresses found */
        alloc_addresses(h, hints, port, res, &ai); /* ignore the error */
#endif
    h=gethostbyname(node); /* get list of addresses */
    if(h)
        retval=ai ?
            alloc_addresses(h, hints, port, &ai->ai_next, &ai) :
            alloc_addresses(h, hints, port, res, &ai);
    else if(!*res)
        retval=EAI_NONAME; /* no results */
    else
        retval=0;
#ifdef HAVE_ENDHOSTENT
    endhostent();
#endif
    CRYPTO_w_unlock(stunnel_locks[LOCK_INET]);
    if(retval) { /* error: free allocated memory */
        freeaddrinfo(*res);
        *res=NULL;
    }
    return retval;
}

NOEXPORT int alloc_addresses(struct hostent *h, const struct addrinfo *hints,
        u_short port, struct addrinfo **head, struct addrinfo **tail) {
    int i;
    struct addrinfo *ai;

    /* copy addresses */
    for(i=0; h->h_addr_list[i]; i++) {
        ai=str_alloc(sizeof(struct addrinfo));
        if(hints)
            memcpy(ai, hints, sizeof(struct addrinfo));
        ai->ai_next=NULL; /* just in case */
        if(*tail) { /* list not empty: add a node */
            (*tail)->ai_next=ai;
            *tail=ai;
        } else { /* list empty: create it */
            *head=ai;
            *tail=ai;
        }
        ai->ai_family=h->h_addrtype;
#if defined(USE_IPv6)
        if(h->h_addrtype==AF_INET6) {
            ai->ai_addrlen=sizeof(struct sockaddr_in6);
            ai->ai_addr=str_alloc((size_t)ai->ai_addrlen);
            memcpy(&((struct sockaddr_in6 *)ai->ai_addr)->sin6_addr,
                h->h_addr_list[i], (size_t)h->h_length);
        } else
#endif
        {
            ai->ai_addrlen=sizeof(struct sockaddr_in);
            ai->ai_addr=str_alloc((size_t)ai->ai_addrlen);
            memcpy(&((struct sockaddr_in *)ai->ai_addr)->sin_addr,
                h->h_addr_list[i], (size_t)h->h_length);
        }
        ai->ai_addr->sa_family=(u_short)h->h_addrtype;
        /* offsets of sin_port and sin6_port should be the same */
        ((struct sockaddr_in *)ai->ai_addr)->sin_port=port;
    }
    return 0; /* success */
}