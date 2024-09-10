/*
 * chap_handle_response - check the response to our challenge.
 */
static void  chap_handle_response(ppp_pcb *pcb, int id,
		     unsigned char *pkt, int len) {
	int response_len, ok, mlen;
	const unsigned char *response;
	unsigned char *outp;
	struct pbuf *p;
	const char *name = NULL;	/* initialized to shut gcc up */
#if 0 /* UNUSED */
	int (*verifier)(const char *, const char *, int, const struct chap_digest_type *,
		const unsigned char *, const unsigned char *, char *, int);
#endif /* UNUSED */
	char rname[MAXNAMELEN+1];
	char message[256];

	if ((pcb->chap_server.flags & LOWERUP) == 0)
		return;
	if (id != pcb->chap_server.challenge[PPP_HDRLEN+1] || len < 2)
		return;
	if (pcb->chap_server.flags & CHALLENGE_VALID) {
		response = pkt;
		GETCHAR(response_len, pkt);
		len -= response_len + 1;	/* length of name */
		name = (char *)pkt + response_len;
		if (len < 0)
			return;

		if (pcb->chap_server.flags & TIMEOUT_PENDING) {
			pcb->chap_server.flags &= ~TIMEOUT_PENDING;
			UNTIMEOUT(chap_timeout, pcb);
		}
#if PPP_REMOTENAME
		if (pcb->settings.explicit_remote) {
			name = pcb->remote_name;
		} else
#endif /* PPP_REMOTENAME */
		{
			/* Null terminate and clean remote name. */
			ppp_slprintf(rname, sizeof(rname), "%.*v", len, name);
			name = rname;
		}

#if 0 /* UNUSED */
		if (chap_verify_hook)
			verifier = chap_verify_hook;
		else
			verifier = chap_verify_response;
		ok = (*verifier)(name, pcb->chap_server.name, id, pcb->chap_server.digest,
				 pcb->chap_server.challenge + PPP_HDRLEN + CHAP_HDRLEN,
				 response, pcb->chap_server.message, sizeof(pcb->chap_server.message));
#endif /* UNUSED */
		ok = chap_verify_response(pcb, name, pcb->chap_server.name, id, pcb->chap_server.digest,
                    pcb->chap_server.challenge + PPP_HDRLEN + CHAP_HDRLEN,
                    response, message, sizeof(message));
#if 0 /* UNUSED */
		if (!ok || !auth_number()) {
#endif /* UNUSED */
		if (!ok) {
			pcb->chap_server.flags |= AUTH_FAILED;
			ppp_warn("Peer %q failed CHAP authentication", name);
		}
	} else if ((pcb->chap_server.flags & AUTH_DONE) == 0)
		return;

	/* send the response */
	mlen = strlen(message);
	len = CHAP_HDRLEN + mlen;
	p = pbuf_alloc(PBUF_RAW, (u16_t)(PPP_HDRLEN +len), PPP_CTRL_PBUF_TYPE);
	if(NULL == p)
		return;
	if(p->tot_len != p->len) {
		pbuf_free(p);
		return;
	}

	outp = (unsigned char *)p->payload;
	MAKEHEADER(outp, PPP_CHAP);

	outp[0] = (pcb->chap_server.flags & AUTH_FAILED)? CHAP_FAILURE: CHAP_SUCCESS;
	outp[1] = id;
	outp[2] = len >> 8;
	outp[3] = len;
	if (mlen > 0)
		memcpy(outp + CHAP_HDRLEN, message, mlen);
	ppp_write(pcb, p);

	if (pcb->chap_server.flags & CHALLENGE_VALID) {
		pcb->chap_server.flags &= ~CHALLENGE_VALID;
		if (!(pcb->chap_server.flags & AUTH_DONE) && !(pcb->chap_server.flags & AUTH_FAILED)) {

#if 0 /* UNUSED */
		    /*
		     * Auth is OK, so now we need to check session restrictions
		     * to ensure everything is OK, but only if we used a
		     * plugin, and only if we're configured to check.  This
		     * allows us to do PAM checks on PPP servers that
		     * authenticate against ActiveDirectory, and use AD for
		     * account info (like when using Winbind integrated with
		     * PAM).
		     */
		    if (session_mgmt &&
			session_check(name, NULL, devnam, NULL) == 0) {
			pcb->chap_server.flags |= AUTH_FAILED;
			ppp_warn("Peer %q failed CHAP Session verification", name);
		    }
#endif /* UNUSED */

		}
		if (pcb->chap_server.flags & AUTH_FAILED) {
			auth_peer_fail(pcb, PPP_CHAP);
		} else {
			if ((pcb->chap_server.flags & AUTH_DONE) == 0)
				auth_peer_success(pcb, PPP_CHAP,
						  pcb->chap_server.digest->code,
						  name, strlen(name));
			if (pcb->settings.chap_rechallenge_time) {
				pcb->chap_server.flags |= TIMEOUT_PENDING;
				TIMEOUT(chap_timeout, pcb,
					pcb->settings.chap_rechallenge_time);
			}
		}
		pcb->chap_server.flags |= AUTH_DONE;
	}
}