static void smtpd_peer_from_pass_attr(SMTPD_STATE *state)
{
    HTABLE *attr = (HTABLE *) vstream_context(state->client);
    const char *cp;

    /*
     * Extract the client endpoint information from the attribute hash.
     */
    if ((cp = htable_find(attr, MAIL_ATTR_ACT_CLIENT_ADDR)) == 0)
	msg_fatal("missing client address from proxy");
    if (strrchr(cp, ':') != 0) {
	if (valid_ipv6_hostaddr(cp, DO_GRIPE) == 0)
	    msg_fatal("bad IPv6 client address syntax from proxy: %s", cp);
	state->addr = mystrdup(cp);
	state->rfc_addr = concatenate(IPV6_COL, cp, (char *) 0);
	state->addr_family = AF_INET6;
    } else {
	if (valid_ipv4_hostaddr(cp, DO_GRIPE) == 0)
	    msg_fatal("bad IPv4 client address syntax from proxy: %s", cp);
	state->addr = mystrdup(cp);
	state->rfc_addr = mystrdup(cp);
	state->addr_family = AF_INET;
    }
    if ((cp = htable_find(attr, MAIL_ATTR_ACT_CLIENT_PORT)) == 0)
	msg_fatal("missing client port from proxy");
    if (valid_hostport(cp, DO_GRIPE) == 0)
	msg_fatal("bad TCP client port number syntax from proxy: %s", cp);
    state->port = mystrdup(cp);

    /*
     * The Dovecot authentication server needs the server IP address.
     */
    if ((cp = htable_find(attr, MAIL_ATTR_ACT_SERVER_ADDR)) == 0)
	msg_fatal("missing server address from proxy");
    if (valid_hostaddr(cp, DO_GRIPE) == 0)
	msg_fatal("bad IPv6 server address syntax from proxy: %s", cp);
    state->dest_addr = mystrdup(cp);

    if ((cp = htable_find(attr, MAIL_ATTR_ACT_SERVER_PORT)) == 0)
	msg_fatal("missing server port from proxy");
    if (valid_hostport(cp, DO_GRIPE) == 0)
	msg_fatal("bad TCP server port number syntax from proxy: %s", cp);
    state->dest_port = mystrdup(cp);

    /*
     * Convert the client address from string to binary form.
     */
    smtpd_peer_hostaddr_to_sockaddr(state);
}