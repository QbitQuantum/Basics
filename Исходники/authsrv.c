void
mschap(Ticketreq *tr)
{

	char *secret, *hkey;
	char sbuf[SECRETLEN], hbuf[DESKEYLEN];
	uchar chal[CHALLEN];
	uchar hash[MShashlen];
	uchar hash2[MShashlen];
	uchar resp[MSresplen];
	OMSchapreply reply;
	int dupe, lmok, ntok;
	DigestState *s;
	uchar digest[SHA1dlen];

	/*
	 *  Create a challenge and send it.
	 */
	randombytes((uchar*)chal, sizeof(chal));
	write(1, chal, sizeof(chal));

	/*
	 *  get chap reply
	 */
	if(readn(0, &reply, sizeof(reply)) < 0)
		exits(0);

	safecpy(tr->uid, reply.uid, sizeof(tr->uid));
	/*
	 * lookup
	 */
	secret = findsecret(KEYDB, tr->uid, sbuf);
	hkey = findkey(KEYDB, tr->hostid, hbuf);
	if(hkey == 0 || secret == 0){
		replyerror("mschap-fail bad response %s/%s(%s)",
			tr->uid, tr->hostid, raddr);
		logfail(tr->uid);
		exits(0);
	}

	lmhash(hash, secret);
	mschalresp(resp, hash, chal);
	lmok = memcmp(resp, reply.LMresp, MSresplen) == 0;
	nthash(hash, secret);
	mschalresp(resp, hash, chal);
	ntok = memcmp(resp, reply.NTresp, MSresplen) == 0;
	dupe = memcmp(reply.LMresp, reply.NTresp, MSresplen) == 0;

	/*
	 * It is valid to send the same response in both the LM and NTLM 
	 * fields provided one of them is correct, if neither matches,
	 * or the two fields are different and either fails to match, 
	 * the whole sha-bang fails.
	 *
	 * This is an improvement in security as it allows clients who
	 * wish to do NTLM auth (which is insecure) not to send
	 * LM tokens (which is very insecure).
	 *
	 * Windows servers supports clients doing this also though
	 * windows clients don't seem to use the feature.
	 */
	if((!ntok && !lmok) || ((!ntok || !lmok) && !dupe)){
		replyerror("mschap-fail bad response %s/%s(%s) %d,%d,%d",
			tr->uid, tr->hostid, raddr, dupe, lmok, ntok);
		logfail(tr->uid);
		exits(0);
	}

	succeed(tr->uid);

	/*
	 *  reply with ticket & authenticator
	 */
	if(tickauthreply(tr, hkey) < 0)
		exits(0);

	if(debug)
		replyerror("mschap-ok %s/%s(%s) %ux",
			tr->uid, tr->hostid, raddr);

	nthash(hash, secret);
	md4(hash, 16, hash2, 0);
	s = sha1(hash2, 16, 0, 0);
	sha1(hash2, 16, 0, s);
	sha1(chal, 8, digest, s);

	if(write(1, digest, 16) < 0)
		exits(0);
}