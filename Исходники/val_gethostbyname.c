/*
 * Function: get_hostent_from_etc_hosts
 *
 * Purpose: Read the ETC_HOSTS file and check if it contains the given name.
 *          Return the result in a hostent structure.
 *
 * Parameters:
 *              ctx -- The validation context.
 *             name -- The domain name or IP address in string form.
 *               af -- The address family: AF_INET or AF_INET6.
 *              ret -- Pointer to a hostent structure to return the result.
 *                     This parameter must not be NULL.
 *              buf -- A buffer to store auxiliary data.  This parameter must not be NULL.
 *           buflen -- Length of the buffer 'buf'.
 *           offset -- Pointer to an integer variable that contains the offset in the buffer
 *                     'buf', where data can be written.  When this function writes any data
 *                     in the auxiliary data, the offset is incremented accordingly.  This
 *                     parameter must not be NULL.
 *
 * Return value: Returns NULL on failure and 'ret' on success.
 *
 * See also: get_hostent_from_response()
 */
static struct hostent *
get_hostent_from_etc_hosts(val_context_t * ctx,
                           const char *name,
                           int af,
                           struct hostent *ret,
                           char *buf, int buflen, int *offset)
{
    int             orig_offset = 0;
    struct hosts   *hs = NULL;
    struct hosts   *h_prev = NULL;

    if ((ret == NULL) || (buf == NULL) || (offset == NULL)
        || (*offset < 0)) {
        return NULL;
    }

    /*
     * Parse the /etc/hosts file 
     */
    hs = parse_etc_hosts(name);

    orig_offset = *offset;
    memset(ret, 0, sizeof(struct hostent));

    /*
     * XXX: todo -- can hs have more than one element ? 
     */
    while (hs) {
        struct sockaddr_in sa;
#if defined( WIN32 )
        size_t addrlen4 = sizeof(struct sockaddr_in);
#endif
#ifdef VAL_IPV6
        struct sockaddr_in6 sa6;
#if defined( WIN32 )
        size_t addrlen6 = sizeof(struct sockaddr_in6);
#endif
#endif
        char            addr_buf[INET6_ADDRSTRLEN];
        int             i, alias_count;
        int             len = 0;
        const char *addr = NULL;
        size_t buflen = INET6_ADDRSTRLEN;

        if ((af == AF_INET)
            && (INET_PTON(AF_INET, hs->address, ((struct sockaddr *)&sa), &addrlen4) > 0)) {
            INET_NTOP(AF_INET, (&sa), sizeof(sa), addr_buf, buflen, addr);
            val_log(ctx, LOG_DEBUG, "get_hostent_from_etc_hosts(): type of address is IPv4");
            val_log(ctx, LOG_DEBUG, "get_hostent_from_etc_hosts(): Address is: %s",
                    addr
		);
        } 
#ifdef VAL_IPV6
	else if ((af == AF_INET6)
                   && (INET_PTON(AF_INET6, hs->address, ((struct sockaddr *)&sa6), &addrlen6) > 0)) {
	    
            INET_NTOP(AF_INET6, (&sa6), sizeof(sa6), addr_buf, buflen, addr);
            val_log(ctx, LOG_DEBUG, "get_hostent_from_etc_hosts(): type of address is IPv6");
            val_log(ctx, LOG_DEBUG, "get_hostent_from_etc_hosts(): Address is: %s",
                    addr
                  );
        } 
#endif
	else {
            /*
             * not a valid address ... skip this line 
             */
            val_log(ctx, LOG_WARNING,
                    "get_hostent_from_etc_hosts(): error in address format: %s",
                    hs->address);
            h_prev = hs;
            hs = hs->next;
            FREE_HOSTS(h_prev);
            continue;
        }

        // Name
        len =
            (hs->canonical_hostname ==
             NULL) ? 0 : strlen(hs->canonical_hostname);

        if (hs->canonical_hostname) {
            ret->h_name = (char *) bufalloc(buf, buflen, offset, len + 1);
            if (ret->h_name == NULL) {
                goto err;
            }

            memcpy(ret->h_name, hs->canonical_hostname, len + 1);
        } else {
            ret->h_name = NULL;
        }

        // Aliases
        alias_count = 0;
        while (hs->aliases[alias_count]) {
            alias_count++;
        }
        alias_count++;

        ret->h_aliases =
            (char **) bufalloc(buf, buflen, offset,
                               alias_count * sizeof(char *));

        if (ret->h_aliases == NULL) {
            goto err;
        }

        for (i = 0; i < alias_count; i++) {
            len = (hs->aliases[i] == NULL) ? 0 : strlen(hs->aliases[i]);
            if (hs->aliases[i]) {
                ret->h_aliases[i] =
                    (char *) bufalloc(buf, buflen, offset, len + 1);
                if (ret->h_aliases[i] == NULL) {
                    goto err;
                }
                memcpy(ret->h_aliases[i], hs->aliases[i], len + 1);
            } else {
                ret->h_aliases[i] = NULL;
            }
        }

        // Addresses
        ret->h_addr_list =
            (char **) bufalloc(buf, buflen, offset, 2 * sizeof(char *));
        if ((ret->h_addr_list == NULL)
            || ((af != AF_INET) && (af != AF_INET6))) {
            goto err;
        }
        if (af == AF_INET) {
            ret->h_addrtype = AF_INET;
            ret->h_length = sizeof(struct in_addr);
            ret->h_addr_list[0] =
                (char *) bufalloc(buf, buflen, offset,
                                  sizeof(struct in_addr));
            if (ret->h_addr_list[0] == NULL) {
                goto err;
            }
            memcpy(ret->h_addr_list[0], &sa.sin_addr, sizeof(struct in_addr));
            ret->h_addr_list[1] = 0;
        } 
#ifdef VAL_IPV6
        else if (af == AF_INET6) {
            ret->h_addrtype = AF_INET6;
            ret->h_length = sizeof(struct in6_addr);
            ret->h_addr_list[0] =
                (char *) bufalloc(buf, buflen, offset,
                                  sizeof(struct in6_addr));
            if (ret->h_addr_list[0] == NULL) {
                goto err;
            }
            memcpy(ret->h_addr_list[0], &sa6.sin6_addr,
                   sizeof(struct in6_addr));
            ret->h_addr_list[1] = 0;
        }
#endif

        /*
         * clean up host list 
         */
        while (hs) {
            h_prev = hs;
            hs = hs->next;
            FREE_HOSTS(h_prev);
        }
        return ret;
    }

    return NULL;

  err:
    /*
     * clean up host list 
     */
    while (hs) {
        h_prev = hs;
        hs = hs->next;
        FREE_HOSTS(h_prev);
    }

    *offset = orig_offset;
    return NULL;

}                               /* get_hostent_from_etc_hosts() */