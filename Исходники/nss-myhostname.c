enum nss_status _nss_myhostname_gethostbyname4_r(
                const char *name,
                struct gaih_addrtuple **pat,
                char *buffer, size_t buflen,
                int *errnop, int *h_errnop,
                int32_t *ttlp) {

        unsigned lo_ifi;
        char hn[HOST_NAME_MAX+1] = {};
        const char *canonical = NULL;
        size_t l, idx, ms;
        char *r_name;
        struct gaih_addrtuple *r_tuple, *r_tuple_prev = NULL;
        struct address *addresses = NULL, *a;
        unsigned n_addresses = 0, n;
        uint32_t local_address_ipv4;

        if (strcasecmp(name, "localhost") == 0) {
                /* We respond to 'localhost', so that /etc/hosts
                 * is optional */

                canonical = "localhost";
                local_address_ipv4 = htonl(INADDR_LOOPBACK);
        } else {
                /* We respond to our local host name */

                if (gethostname(hn, sizeof(hn)-1) < 0) {
                        *errnop = errno;
                        *h_errnop = NO_RECOVERY;
                        return NSS_STATUS_UNAVAIL;
                }

                if (strcasecmp(name, hn) != 0) {
                        *errnop = ENOENT;
                        *h_errnop = HOST_NOT_FOUND;
                        return NSS_STATUS_NOTFOUND;
                }

                /* If this fails, n_addresses is 0. Which is fine */
                ifconf_acquire_addresses(&addresses, &n_addresses);

                canonical = hn;
                local_address_ipv4 = LOCALADDRESS_IPV4;
        }

        /* If this call fails we fill in 0 as scope. Which is fine */
        lo_ifi = n_addresses <= 0 ? if_nametoindex(LOOPBACK_INTERFACE) : 0;

        l = strlen(canonical);
        ms = ALIGN(l+1)+ALIGN(sizeof(struct gaih_addrtuple))*(n_addresses > 0 ? n_addresses : 2);
        if (buflen < ms) {
                *errnop = ENOMEM;
                *h_errnop = NO_RECOVERY;
                free(addresses);
                return NSS_STATUS_TRYAGAIN;
        }

        /* First, fill in hostname */
        r_name = buffer;
        memcpy(r_name, canonical, l+1);
        idx = ALIGN(l+1);

        if (n_addresses <= 0) {
                /* Second, fill in IPv6 tuple */
                r_tuple = (struct gaih_addrtuple*) (buffer + idx);
                r_tuple->next = r_tuple_prev;
                r_tuple->name = r_name;
                r_tuple->family = AF_INET6;
                memcpy(r_tuple->addr, LOCALADDRESS_IPV6, 16);
                r_tuple->scopeid = (uint32_t) lo_ifi;

                idx += ALIGN(sizeof(struct gaih_addrtuple));
                r_tuple_prev = r_tuple;

                /* Third, fill in IPv4 tuple */
                r_tuple = (struct gaih_addrtuple*) (buffer + idx);
                r_tuple->next = r_tuple_prev;
                r_tuple->name = r_name;
                r_tuple->family = AF_INET;
                *(uint32_t*) r_tuple->addr = local_address_ipv4;
                r_tuple->scopeid = (uint32_t) lo_ifi;

                idx += ALIGN(sizeof(struct gaih_addrtuple));
                r_tuple_prev = r_tuple;
        }

        /* Fourth, fill actual addresses in, but in backwards order */
        for (a = addresses + n_addresses - 1, n = 0; n < n_addresses; n++, a--) {
                r_tuple = (struct gaih_addrtuple*) (buffer + idx);
                r_tuple->next = r_tuple_prev;
                r_tuple->name = r_name;
                r_tuple->family = a->family;
                r_tuple->scopeid = a->ifindex;
                memcpy(r_tuple->addr, a->address, 16);

                idx += ALIGN(sizeof(struct gaih_addrtuple));
                r_tuple_prev = r_tuple;
        }

        /* Verify the size matches */
        assert(idx == ms);

        /* Nscd expects us to store the first record in **pat. */
        if (*pat)
                **pat = *r_tuple_prev;
        else
                *pat = r_tuple_prev;

        if (ttlp)
                *ttlp = 0;

        free(addresses);

        return NSS_STATUS_SUCCESS;
}