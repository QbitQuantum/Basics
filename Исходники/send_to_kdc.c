int
krb4int_send_to_kdc_addr(
    KTEXT pkt, KTEXT rpkt, char *realm,
    struct sockaddr *addr, socklen_t *addrlen)
{
    struct addrlist	al = ADDRLIST_INIT;
    char		lrealm[REALM_SZ];
    krb5int_access	internals;
    krb5_error_code	retval;
    struct servent	*sp;
    int			krb_udp_port = 0;
    int			krbsec_udp_port = 0;
    char		krbhst[MAXHOSTNAMELEN];
    char		*scol;
    int			i;
    int			err;
    krb5_data		message, reply;

    /*
     * If "realm" is non-null, use that, otherwise get the
     * local realm.
     */
    if (realm)
	strncpy(lrealm, realm, sizeof(lrealm) - 1);
    else {
	if (krb_get_lrealm(lrealm, 1)) {
	    DEB (("%s: can't get local realm\n", prog));
	    return SKDC_CANT;
	}
    }
    lrealm[sizeof(lrealm) - 1] = '\0';
    DEB (("lrealm is %s\n", lrealm));

    retval = krb5int_accessor(&internals, KRB5INT_ACCESS_VERSION);
    if (retval)
	return KFAILURE;

    /* The first time, decide what port to use for the KDC.  */
    if (cached_krb_udp_port == 0) {
	sp = getservbyname("kerberos","udp");
        if (sp)
	    cached_krb_udp_port = sp->s_port;
	else
	    cached_krb_udp_port = htons(KERBEROS_PORT); /* kerberos/udp */
        DEB (("cached_krb_udp_port is %d\n", cached_krb_udp_port));
    }
    /* If kerberos/udp isn't 750, try using kerberos-sec/udp (or 750) 
       as a fallback. */
    if (cached_krbsec_udp_port == 0 && 
	cached_krb_udp_port != htons(KERBEROS_PORT)) {
	sp = getservbyname("kerberos-sec","udp");
        if (sp)
	    cached_krbsec_udp_port = sp->s_port;
	else
	    cached_krbsec_udp_port = htons(KERBEROS_PORT); /* kerberos/udp */
        DEB (("cached_krbsec_udp_port is %d\n", cached_krbsec_udp_port));
    }

    for (i = 1; krb_get_krbhst(krbhst, lrealm, i) == KSUCCESS; ++i) {
#ifdef DEBUG
        if (krb_debug) {
            DEB (("Getting host entry for %s...",krbhst));
            (void) fflush(stdout);
        }
#endif
	if (0 != (scol = strchr(krbhst,':'))) {
	    krb_udp_port = htons(atoi(scol+1));
	    *scol = 0;
	    if (krb_udp_port == 0) {
#ifdef DEBUG
		if (krb_debug) {
		    DEB (("bad port number %s\n",scol+1));
		    (void) fflush(stdout);
		}
#endif
		continue;
	    }
	    krbsec_udp_port = 0;
	} else {
	    krb_udp_port = cached_krb_udp_port;
	    krbsec_udp_port = cached_krbsec_udp_port;
	}
        err = internals.add_host_to_list(&al, krbhst,
					 krb_udp_port, krbsec_udp_port,
					 SOCK_DGRAM, PF_INET);
	if (err) {
	    retval = SKDC_CANT;
	    goto free_al;
	}
    }
    if (al.naddrs == 0) {
	DEB (("%s: can't find any Kerberos host.\n", prog));
        retval = SKDC_CANT;
    }

    message.length = pkt->length;
    message.data = (char *)pkt->dat; /* XXX yuck */
    retval = internals.sendto_udp(NULL, &message, &al, NULL, &reply, addr,
				  addrlen, NULL, 0, NULL);
    DEB(("sendto_udp returns %d\n", retval));
free_al:
    internals.free_addrlist(&al);
    if (retval)
	return SKDC_CANT;
    DEB(("reply.length=%d\n", reply.length));
    if (reply.length > sizeof(rpkt->dat))
	retval = SKDC_CANT;
    rpkt->length = 0;
    if (!retval) {
	memcpy(rpkt->dat, reply.data, reply.length);
	rpkt->length = reply.length;
    }
    krb5_free_data_contents(NULL, &reply);
    return retval;
}