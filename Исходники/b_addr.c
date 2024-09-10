/*-
 * BIO_lookup - look up the node and service you want to connect to.
 * @node: the node you want to connect to.
 * @service: the service you want to connect to.
 * @lookup_type: declare intent with the result, client or server.
 * @family: the address family you want to use.  Use AF_UNSPEC for any, or
 *  AF_INET, AF_INET6 or AF_UNIX.
 * @socktype: The socket type you want to use.  Can be SOCK_STREAM, SOCK_DGRAM
 *  or 0 for all.
 * @res: Storage place for the resulting list of returned addresses
 *
 * This will do a lookup of the node and service that you want to connect to.
 * It returns a linked list of different addresses you can try to connect to.
 *
 * When no longer needed you should call BIO_ADDRINFO_free() to free the result.
 *
 * The return value is 1 on success or 0 in case of error.
 */
int BIO_lookup(const char *host, const char *service,
               enum BIO_lookup_type lookup_type,
               int family, int socktype, BIO_ADDRINFO **res)
{
    int ret = 0;                 /* Assume failure */

    switch(family) {
    case AF_INET:
#ifdef AF_INET6
    case AF_INET6:
#endif
#ifdef AF_UNIX
    case AF_UNIX:
#endif
#ifdef AF_UNSPEC
    case AF_UNSPEC:
#endif
        break;
    default:
        BIOerr(BIO_F_BIO_LOOKUP, BIO_R_UNSUPPORTED_PROTOCOL_FAMILY);
        return 0;
    }

#ifdef AF_UNIX
    if (family == AF_UNIX) {
        if (addrinfo_wrap(family, socktype, host, strlen(host), 0, res))
            return 1;
        else
            BIOerr(BIO_F_BIO_LOOKUP, ERR_R_MALLOC_FAILURE);
        return 0;
    }
#endif

    if (BIO_sock_init() != 1)
        return 0;

    if (1) {
#ifdef AI_PASSIVE
        int gai_ret = 0;
        struct addrinfo hints;

        memset(&hints, 0, sizeof hints);

        hints.ai_family = family;
        hints.ai_socktype = socktype;

        if (lookup_type == BIO_LOOKUP_SERVER)
            hints.ai_flags |= AI_PASSIVE;

        /* Note that |res| SHOULD be a 'struct addrinfo **' thanks to
         * macro magic in bio_lcl.h
         */
        switch ((gai_ret = getaddrinfo(host, service, &hints, res))) {
# ifdef EAI_SYSTEM
        case EAI_SYSTEM:
            SYSerr(SYS_F_GETADDRINFO, get_last_socket_error());
            BIOerr(BIO_F_BIO_LOOKUP, ERR_R_SYS_LIB);
            break;
# endif
        case 0:
            ret = 1;             /* Success */
            break;
        default:
            BIOerr(BIO_F_BIO_LOOKUP, ERR_R_SYS_LIB);
            ERR_add_error_data(1, gai_strerror(gai_ret));
            break;
        }
    } else {
#endif
        const struct hostent *he;
/*
 * Because struct hostent is defined for 32-bit pointers only with
 * VMS C, we need to make sure that '&he_fallback_address' and
 * '&he_fallback_addresses' are 32-bit pointers
 */
#if defined(OPENSSL_SYS_VMS) && defined(__DECC)
# pragma pointer_size save
# pragma pointer_size 32
#endif
        /* Windows doesn't seem to have in_addr_t */
#ifdef OPENSSL_SYS_WINDOWS
        static uint32_t he_fallback_address;
        static const char *he_fallback_addresses[] =
            { (char *)&he_fallback_address, NULL };
#else
        static in_addr_t he_fallback_address;
        static const char *he_fallback_addresses[] =
            { (char *)&he_fallback_address, NULL };
#endif
        static const struct hostent he_fallback =
            { NULL, NULL, AF_INET, sizeof(he_fallback_address),
              (char **)&he_fallback_addresses };
#if defined(OPENSSL_SYS_VMS) && defined(__DECC)
# pragma pointer_size restore
#endif

        struct servent *se;
        /* Apparently, on WIN64, s_proto and s_port have traded places... */
#ifdef _WIN64
        struct servent se_fallback = { NULL, NULL, NULL, 0 };
#else
        struct servent se_fallback = { NULL, NULL, 0, NULL };
#endif

        if (!RUN_ONCE(&bio_lookup_init, do_bio_lookup_init)) {
            BIOerr(BIO_F_BIO_LOOKUP, ERR_R_MALLOC_FAILURE);
            ret = 0;
            goto err;
        }

        CRYPTO_THREAD_write_lock(bio_lookup_lock);
        he_fallback_address = INADDR_ANY;
        if (host == NULL) {
            he = &he_fallback;
            switch(lookup_type) {
            case BIO_LOOKUP_CLIENT:
                he_fallback_address = INADDR_LOOPBACK;
                break;
            case BIO_LOOKUP_SERVER:
                he_fallback_address = INADDR_ANY;
                break;
            default:
                OPENSSL_assert(("We forgot to handle a lookup type!" == 0));
                break;
            }
        } else {
            he = gethostbyname(host);

            if (he == NULL) {
#ifndef OPENSSL_SYS_WINDOWS
                /*
                 * This might be misleading, because h_errno is used as if
                 * it was errno. To minimize mixup add 1000. Underlying
                 * reason for this is that hstrerror is declared obsolete,
                 * not to mention that a) h_errno is not always guaranteed
                 * to be meaningless; b) hstrerror can reside in yet another
                 * library, linking for sake of hstrerror is an overkill;
                 * c) this path is not executed on contemporary systems
                 * anyway [above getaddrinfo/gai_strerror is]. We just let
                 * system administrator figure this out...
                 */
                SYSerr(SYS_F_GETHOSTBYNAME, 1000 + h_errno);
#else
                SYSerr(SYS_F_GETHOSTBYNAME, WSAGetLastError());
#endif
                ret = 0;
                goto err;
            }
        }

        if (service == NULL) {
            se_fallback.s_port = 0;
            se_fallback.s_proto = NULL;
            se = &se_fallback;
        } else {
            char *endp = NULL;
            long portnum = strtol(service, &endp, 10);

/*
 * Because struct servent is defined for 32-bit pointers only with
 * VMS C, we need to make sure that 'proto' is a 32-bit pointer.
 */
#if defined(OPENSSL_SYS_VMS) && defined(__DECC)
# pragma pointer_size save
# pragma pointer_size 32
#endif
            char *proto = NULL;
#if defined(OPENSSL_SYS_VMS) && defined(__DECC)
# pragma pointer_size restore
#endif

            switch (socktype) {
            case SOCK_STREAM:
                proto = "tcp";
                break;
            case SOCK_DGRAM:
                proto = "udp";
                break;
            }

            if (endp != service && *endp == '\0'
                    && portnum > 0 && portnum < 65536) {
                se_fallback.s_port = htons(portnum);
                se_fallback.s_proto = proto;
                se = &se_fallback;
            } else if (endp == service) {
                se = getservbyname(service, proto);

                if (se == NULL) {
#ifndef OPENSSL_SYS_WINDOWS
                    SYSerr(SYS_F_GETSERVBYNAME, errno);
#else
                    SYSerr(SYS_F_GETSERVBYNAME, WSAGetLastError());
#endif
                    goto err;
                }
            } else {
                BIOerr(BIO_F_BIO_LOOKUP, BIO_R_MALFORMED_HOST_OR_SERVICE);
                goto err;
            }
        }

        *res = NULL;

        {
/*
 * Because hostent::h_addr_list is an array of 32-bit pointers with VMS C,
 * we must make sure our iterator designates the same element type, hence
 * the pointer size dance.
 */
#if defined(OPENSSL_SYS_VMS) && defined(__DECC)
# pragma pointer_size save
# pragma pointer_size 32
#endif
            char **addrlistp;
#if defined(OPENSSL_SYS_VMS) && defined(__DECC)
# pragma pointer_size restore
#endif
            size_t addresses;
            BIO_ADDRINFO *tmp_bai = NULL;

            /* The easiest way to create a linked list from an
               array is to start from the back */
            for(addrlistp = he->h_addr_list; *addrlistp != NULL;
                addrlistp++)
                ;

            for(addresses = addrlistp - he->h_addr_list;
                addrlistp--, addresses-- > 0; ) {
                if (!addrinfo_wrap(he->h_addrtype, socktype,
                                   *addrlistp, he->h_length,
                                   se->s_port, &tmp_bai))
                    goto addrinfo_malloc_err;
                tmp_bai->bai_next = *res;
                *res = tmp_bai;
                continue;
             addrinfo_malloc_err:
                BIO_ADDRINFO_free(*res);
                *res = NULL;
                BIOerr(BIO_F_BIO_LOOKUP, ERR_R_MALLOC_FAILURE);
                ret = 0;
                goto err;
            }

            ret = 1;
        }
     err:
        CRYPTO_THREAD_unlock(bio_lookup_lock);
    }

    return ret;
}