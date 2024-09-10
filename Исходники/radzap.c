static int do_packet(int allports, uint32_t nasaddr, const struct radutmp *u)
{
	int i, retries=5, timeout=3;
	struct timeval tv;
	RADIUS_PACKET *req, *rep = NULL;
	VALUE_PAIR *vp;
	const char *secret;

	if ((req = rad_alloc(1)) == NULL) {
		librad_perror("radzap");
		exit(1);
	}
	req->id = getpid() & 0xFF;
	req->code = PW_ACCOUNTING_REQUEST;
	req->dst_port = acct_port;
	if(req->dst_port == 0) 
		req->dst_port = getport("radacct");
	if(req->dst_port == 0) 
		req->dst_port = PW_ACCT_UDP_PORT;
	if (radiusip == INADDR_NONE) {
		req->dst_ipaddr = ip_getaddr("localhost");
	}
	else {
		req->dst_ipaddr = radiusip;
	}
	if(!req->dst_ipaddr) 
		req->dst_ipaddr = 0x7f000001;
	req->vps = NULL;
	secret = getsecret(req->dst_ipaddr);

	if(allports != 0) {
		INTPAIR(PW_ACCT_STATUS_TYPE, PW_STATUS_ACCOUNTING_OFF);
		IPPAIR(PW_NAS_IP_ADDRESS, nasaddr);
		INTPAIR(PW_ACCT_DELAY_TIME, 0);
	} else {
		char login[sizeof u->login+1];
		char session_id[sizeof u->session_id+1];
		strNcpy(login, u->login, sizeof login);
		strNcpy(session_id, u->session_id, sizeof session_id);
		INTPAIR(PW_ACCT_STATUS_TYPE, PW_STATUS_STOP);
		IPPAIR(PW_NAS_IP_ADDRESS, u->nas_address);
		INTPAIR(PW_ACCT_DELAY_TIME, 0);
		STRINGPAIR(PW_USER_NAME, login);
		INTPAIR(PW_NAS_PORT, u->nas_port);
		STRINGPAIR(PW_ACCT_SESSION_ID, session_id);
		if(u->proto=='P') {
			INTPAIR(PW_SERVICE_TYPE, PW_FRAMED_USER);
			INTPAIR(PW_FRAMED_PROTOCOL, PW_PPP);
		} else if(u->proto=='S') {
			INTPAIR(PW_SERVICE_TYPE, PW_FRAMED_USER);
			INTPAIR(PW_FRAMED_PROTOCOL, PW_SLIP);
		} else {
			INTPAIR(PW_SERVICE_TYPE, PW_LOGIN_USER); /* A guess, really */
		}
		IPPAIR(PW_FRAMED_IP_ADDRESS, u->framed_address);
		INTPAIR(PW_ACCT_SESSION_TIME, 0);
		INTPAIR(PW_ACCT_INPUT_OCTETS, 0);
		INTPAIR(PW_ACCT_OUTPUT_OCTETS, 0);
		INTPAIR(PW_ACCT_INPUT_PACKETS, 0);
		INTPAIR(PW_ACCT_OUTPUT_PACKETS, 0);
	}
	if ((req->sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("radzap: socket: ");
		exit(1);
	}

	for (i = 0; i < retries; i++) {
		fd_set rdfdesc;

		rad_send(req, NULL, secret);

		/* And wait for reply, timing out as necessary */
		FD_ZERO(&rdfdesc);
		FD_SET(req->sockfd, &rdfdesc);

		tv.tv_sec = (int)timeout;
		tv.tv_usec = 1000000 * (timeout - (int)timeout);

		/* Something's wrong if we don't get exactly one fd. */
		if (select(req->sockfd + 1, &rdfdesc, NULL, NULL, &tv) != 1) {
			continue;
		}

		rep = rad_recv(req->sockfd);
		if (rep != NULL) {
			break;
		} else {	/* NULL: couldn't receive the packet */
			librad_perror("radzap:");
			exit(1);
		}
	}

	/* No response or no data read (?) */
	if (i == retries) {
		fprintf(stderr, "%s: no response from server\n", progname);
		exit(1);
	}

	if (rad_decode(rep, req, secret) != 0) {
		librad_perror("rad_decode");
		exit(1);
	}

	vp_printlist(stdout, rep->vps);
	return 0;
}