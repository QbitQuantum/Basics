int
manage_request(char *target_domain)
{
    char buf[BUFFER_SIZE + 1];
    char *c, *decoded;
    ntlmhdr *fast_header;
    int oversized = 0;


try_again:
    if (fgets(buf, BUFFER_SIZE, stdin) == NULL)
	return 0;

    c = memchr(buf, '\n', BUFFER_SIZE);
    if (c) {
	if (oversized) {
	    helperfail("illegal request received");
	    warn("Illegal request received: '%s'\n", buf);
	    return 1;
	}
	*c = '\0';
    }
    else {
	warn("No newline in '%s'\n", buf);
	oversized = 1;
	goto try_again;
    }

    debug("Got '%s' from squid.\n", buf);
    if (memcmp(buf, "YR", 2) == 0) {	/* refresh-request */
	sendchallenge(ntlm_make_challenge(target_domain, NULL,
		build_challenge(), CHALLENGE_LEN));
	return 1;
    }
    if (strncmp(buf, "KK ", 3) != 0) {	/* not an auth-request */
	helperfail("illegal request received");
	warn("Illegal request received: '%s'\n", buf);
	return 1;
    }
    /* At this point I'm sure it's a KK */
    decoded = base64_decode(buf + 3);
    if (!decoded) {		/* decoding failure, return error */
	authfail("-", "-", "Auth-format error, base64-decoding error");
	return 1;
    }
    fast_header = (struct _ntlmhdr *) decoded;

    /* sanity-check: it IS a NTLMSSP packet, isn't it? */
    if (memcmp(fast_header->signature, "NTLMSSP", 8) != 0) {
	authfail("-", "-", "Broken NTLM packet, missing NTLMSSP signature");
	return 1;
    }
    /* Understand what we got */
    switch WSWAP(fast_header->type) {
    case NTLM_NEGOTIATE:
	authfail("-", "-", "Received neg-request while expecting auth packet");
	return 1;
    case NTLM_CHALLENGE:
	authfail("-", "-", "Received challenge. Refusing to abide");
	return 1;
    case NTLM_AUTHENTICATE:
	do_authenticate((ntlm_authenticate *) decoded,
	    (strlen(buf) - 3) * 3 / 4);
	return 1;
    default:
	helperfail("Unknown authentication packet type");
	return 1;
    }
    /* notreached */
    return 1;
}