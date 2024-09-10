static void do_smb_resolve(struct mdns_smbsrv_result *browsesrv)
{
	DNSServiceRef mdns_conn_sdref = NULL;
	int mdnsfd;
	int fdsetsz;
	int ret;
	struct timeval tv;
	DNSServiceErrorType err;

	TALLOC_CTX * ctx = talloc_tos();

	err = DNSServiceResolve(&mdns_conn_sdref, 0 /* flags */,
		browsesrv->ifIndex,
		browsesrv->serviceName, browsesrv->regType, browsesrv->domain,
		do_smb_resolve_reply, NULL);

	if (err != kDNSServiceErr_NoError) {
		return;
	}

	mdnsfd = DNSServiceRefSockFD(mdns_conn_sdref);
	for (;;)  {
		int revents;

		ret = poll_one_fd(mdnsfd, POLLIN|POLLHUP, 1000, &revents);
		if (ret <= 0 && errno != EINTR) {
			break;
		}

		if (revents & (POLLIN|POLLHUP|POLLERR)) {
			/* Invoke callback function */
			DNSServiceProcessResult(mdns_conn_sdref);
			break;
		}
	}

	TALLOC_FREE(fdset);
	DNSServiceRefDeallocate(mdns_conn_sdref);
}