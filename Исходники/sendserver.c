int rc_send_server (rc_handle *rh, SEND_DATA *data, char *msg)
{
	int             sockfd;
	struct sockaddr_in sinlocal;
	struct sockaddr_in sinremote;
	AUTH_HDR       *auth, *recv_auth;
	uint32_t           auth_ipaddr, nas_ipaddr;
	char           *server_name;	/* Name of server to query */
	socklen_t       salen;
	int             result = 0;
	int             total_length;
	int             length;
	int             retry_max;
	size_t			secretlen;
	char            secret[MAX_SECRET_LENGTH + 1];
	unsigned char   vector[AUTH_VECTOR_LEN];
	// uint16_t for alignment
	uint16_t		recv_buffer[BUFFER_LEN / sizeof(uint16_t)];
	uint16_t		send_buffer[BUFFER_LEN / sizeof(uint16_t)];
	int		retries;
	VALUE_PAIR 	*vp;
	struct pollfd	pfd;
	double		start_time, timeout;

	memset(send_buffer, 0, BUFFER_LEN);
	server_name = data->server;
	if (server_name == NULL || server_name[0] == '\0')
		return ERROR_RC;

	if ((vp = rc_avpair_get(data->send_pairs, PW_SERVICE_TYPE, 0)) && \
	    (vp->lvalue == PW_ADMINISTRATIVE))
	{
		strcpy(secret, MGMT_POLL_SECRET);
		if ((auth_ipaddr = rc_get_ipaddr(server_name)) == 0)
			return ERROR_RC;
	}
	else
	{
		if(data->secret != NULL)
		{
			strncpy(secret, data->secret, MAX_SECRET_LENGTH);
		}
		/*
		else
		{
		*/
		if (rc_find_server (rh, server_name, &auth_ipaddr, secret) != 0)
		{
			rc_log(LOG_ERR, "rc_send_server: unable to find server: %s", server_name);
			return ERROR_RC;
		}
		/*}*/
	}

	DEBUG(LOG_ERR, "DEBUG: rc_send_server: creating socket to: %s", server_name);

	sockfd = socket (AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		memset (secret, '\0', sizeof (secret));
		rc_log(LOG_ERR, "rc_send_server: socket: %s", strerror(errno));
		return ERROR_RC;
	}

	memset((char *)&sinlocal, '\0', sizeof(sinlocal));
	sinlocal.sin_family = AF_INET;
	sinlocal.sin_addr.s_addr = htonl(rc_own_bind_ipaddress(rh));
	sinlocal.sin_port = htons((unsigned short) 0);
	if (bind(sockfd, SA(&sinlocal), sizeof(sinlocal)) < 0)
	{
		close (sockfd);
		memset (secret, '\0', sizeof (secret));
		rc_log(LOG_ERR, "rc_send_server: bind: %s: %s", server_name, strerror(errno));
		return ERROR_RC;
	}

	retry_max = data->retries;	/* Max. numbers to try for reply */
	retries = 0;			/* Init retry cnt for blocking call */

	memset ((char *)&sinremote, '\0', sizeof(sinremote));
	sinremote.sin_family = AF_INET;
	sinremote.sin_addr.s_addr = htonl (auth_ipaddr);
	sinremote.sin_port = htons ((unsigned short) data->svc_port);

	/*
	 * Fill in NAS-IP-Address (if needed)
	 */
	if (rc_avpair_get(data->send_pairs, PW_NAS_IP_ADDRESS, 0) == NULL) {
		if (sinlocal.sin_addr.s_addr == htonl(INADDR_ANY)) {
			if (rc_get_srcaddr(SA(&sinlocal), SA(&sinremote)) != 0) {
				close (sockfd);
				memset (secret, '\0', sizeof (secret));
				return ERROR_RC;
			}
		}
		nas_ipaddr = ntohl(sinlocal.sin_addr.s_addr);
		rc_avpair_add(rh, &(data->send_pairs), PW_NAS_IP_ADDRESS,
		    &nas_ipaddr, 0, 0);
	}

	/* Build a request */
	auth = (AUTH_HDR *) send_buffer;
	auth->code = data->code;
	auth->id = data->seq_nbr;

	if (data->code == PW_ACCOUNTING_REQUEST)
	{
		total_length = rc_pack_list(data->send_pairs, secret, auth) + AUTH_HDR_LEN;

		auth->length = htons ((unsigned short) total_length);

		memset((char *) auth->vector, 0, AUTH_VECTOR_LEN);
		secretlen = strlen (secret);
		memcpy ((char *) auth + total_length, secret, secretlen);
		rc_md5_calc (vector, (unsigned char *) auth, total_length + secretlen);
		memcpy ((char *) auth->vector, (char *) vector, AUTH_VECTOR_LEN);
	}
	else
	{
		rc_random_vector (vector);
		memcpy ((char *) auth->vector, (char *) vector, AUTH_VECTOR_LEN);

		total_length = rc_pack_list(data->send_pairs, secret, auth) + AUTH_HDR_LEN;

		auth->length = htons ((unsigned short) total_length);
	}

	DEBUG(LOG_ERR, "DEBUG: local %s : 0, remote %s : %u\n", 
		inet_ntoa(sinlocal.sin_addr),
		inet_ntoa(sinremote.sin_addr), data->svc_port);

	for (;;)
	{
		sendto (sockfd, (char *) auth, (unsigned int) total_length, (int) 0,
			SA(&sinremote), sizeof (struct sockaddr_in));

		pfd.fd = sockfd;
		pfd.events = POLLIN;
		pfd.revents = 0;
		start_time = rc_getctime();
		for (timeout = data->timeout; timeout > 0;
		    timeout -= rc_getctime() - start_time) {
			result = poll(&pfd, 1, timeout * 1000);
			if (result != -1 || errno != EINTR)
				break;
		}
		if (result == -1)
		{
			rc_log(LOG_ERR, "rc_send_server: poll: %s", strerror(errno));
			memset (secret, '\0', sizeof (secret));
			close (sockfd);
			return ERROR_RC;
		}
		if (result == 1 && (pfd.revents & POLLIN) != 0)
			break;

		/*
		 * Timed out waiting for response.  Retry "retry_max" times
		 * before giving up.  If retry_max = 0, don't retry at all.
		 */
		if (retries++ >= retry_max)
		{
			rc_log(LOG_ERR,
				"rc_send_server: no reply from RADIUS server %s:%u, %s",
				 rc_ip_hostname (auth_ipaddr), data->svc_port, inet_ntoa(sinremote.sin_addr));
			close (sockfd);
			memset (secret, '\0', sizeof (secret));
			return TIMEOUT_RC;
		}
	}
	salen = sizeof(sinremote);
	length = recvfrom (sockfd, (char *) recv_buffer,
			   (int) sizeof (recv_buffer),
			   (int) 0, SA(&sinremote), &salen);

	if (length <= 0)
	{
		rc_log(LOG_ERR, "rc_send_server: recvfrom: %s:%d: %s", server_name,\
			 data->svc_port, strerror(errno));
		close (sockfd);
		memset (secret, '\0', sizeof (secret));
		return ERROR_RC;
	}

	recv_auth = (AUTH_HDR *)recv_buffer;

	if (length < AUTH_HDR_LEN || length < ntohs(recv_auth->length)) {
		rc_log(LOG_ERR, "rc_send_server: recvfrom: %s:%d: reply is too short",
		    server_name, data->svc_port);
		close(sockfd);
		memset(secret, '\0', sizeof(secret));
		return ERROR_RC;
	}

	result = rc_check_reply (recv_auth, BUFFER_LEN, secret, vector, data->seq_nbr);

	length = ntohs(recv_auth->length)  - AUTH_HDR_LEN;
	if (length > 0) {
		data->receive_pairs = rc_avpair_gen(rh, NULL, recv_auth->data,
		    length, 0);
	} else {
		data->receive_pairs = NULL;
	}

	close (sockfd);
	memset (secret, '\0', sizeof (secret));

	if (result != OK_RC) return result;

	*msg = '\0';
	vp = data->receive_pairs;
	while (vp)
	{
		if ((vp = rc_avpair_get(vp, PW_REPLY_MESSAGE, 0)))
		{
			strcat(msg, vp->strvalue);
			strcat(msg, "\n");
			vp = vp->next;
		}
	}

	if ((recv_auth->code == PW_ACCESS_ACCEPT) ||
		(recv_auth->code == PW_PASSWORD_ACK) ||
		(recv_auth->code == PW_ACCOUNTING_RESPONSE))
	{
		result = OK_RC;
	}
	else if ((recv_auth->code == PW_ACCESS_REJECT) ||
		(recv_auth->code == PW_PASSWORD_REJECT))
	{
		result = REJECT_RC;
	}
	else
	{
		result = BADRESP_RC;
	}

	return result;
}