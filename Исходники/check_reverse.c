int
reverse(thread_pool_t *info, thread_ctx_t *thread_ctx, edict_t *edict)
{
	chkresult_t *result;
	struct hostent *canonicalhost, *reversehost;

	grey_tuple_t *request;
	const char *client_address;
        char buf[INET_ADDRSTRLEN];
	const char *ptr;
	mseconds_t timelimit;

	request = (grey_tuple_t *)edict->job;
	client_address = request->client_address;
	assert(client_address);

	result = (chkresult_t *)Malloc(sizeof(chkresult_t));
	memset(result, 0, sizeof(*result));
	result->judgment = J_UNDEFINED;
	result->checkname = "reverse";

	timelimit = edict->timelimit;

	reversehost = Gethostbyaddr_str(client_address, timelimit);
	if (reversehost) {
                logstr(GLOG_INSANE, "client_address (%s) has a PTR record (%s)",
                        client_address, reversehost->h_name);
		canonicalhost = Gethostbyname(reversehost->h_name, timelimit);
		if (canonicalhost) {
			ptr = inet_ntop(AF_INET, canonicalhost->h_addr_list[0], buf, INET_ADDRSTRLEN);
			assert(ptr);
			logstr(GLOG_INSANE, "client_ip (%s) canonical (%s)",
				client_address, buf);
			if (strcmp(buf, client_address)) {
				logstr(GLOG_DEBUG, "client_address (%s) not canonical (%s)",
					client_address, buf);
				result->judgment = J_SUSPICIOUS;
				result->weight = 1; /* FIXME */
			}
		} else {
			logstr(GLOG_DEBUG, "No A for PTR for client_ip (%s)", client_address);
			result->judgment = J_SUSPICIOUS;
			result->weight = 1;
		}
	} else {
		logstr(GLOG_DEBUG, "client_ip (%s) has no PTR record", client_address);
		result->judgment = J_SUSPICIOUS;
		result->weight = 1;
	}

	send_result(edict, result);
	logstr(GLOG_DEBUG, "reverse returning");
	request_unlink(request);

	return 0;
}