krb5_error_code KRB5_LIB_FUNCTION
krb5_parse_address(krb5_context context,
		   const char *string,
		   krb5_addresses *addresses)
{
    int i, n;
    struct addrinfo *ai, *a;
    int error;
    int save_errno;

    addresses->len = 0;
    addresses->val = NULL;

    for(i = 0; i < num_addrs; i++) {
	if(at[i].parse_addr) {
	    krb5_address addr;
	    if((*at[i].parse_addr)(context, string, &addr) == 0) {
		ALLOC_SEQ(addresses, 1);
		if (addresses->val == NULL) {
		    krb5_set_error_message(context, ENOMEM,
					   N_("malloc: out of memory", ""));
		    return ENOMEM;
		}
		addresses->val[0] = addr;
		return 0;
	    }
	}
    }

    error = getaddrinfo (string, NULL, NULL, &ai);
    if (error) {
	krb5_error_code ret2;
	save_errno = errno;
	ret2 = krb5_eai_to_heim_errno(error, save_errno);
	krb5_set_error_message (context, ret2, "%s: %s",
				string, gai_strerror(error));
	return ret2;
    }

    n = 0;
    for (a = ai; a != NULL; a = a->ai_next)
	++n;

    ALLOC_SEQ(addresses, n);
    if (addresses->val == NULL) {
	krb5_set_error_message(context, ENOMEM,
			       N_("malloc: out of memory", ""));
	freeaddrinfo(ai);
	return ENOMEM;
    }

    addresses->len = 0;
    for (a = ai, i = 0; a != NULL; a = a->ai_next) {
	if (krb5_sockaddr2address (context, ai->ai_addr, &addresses->val[i]))
	    continue;
	if(krb5_address_search(context, &addresses->val[i], addresses)) {
	    krb5_free_address(context, &addresses->val[i]);
	    continue;
	}
	i++;
	addresses->len = i;
    }
    freeaddrinfo (ai);
    return 0;
}