static void
sendquery(isc_task_t *task, isc_event_t *event) {
	struct in_addr inaddr;
	isc_sockaddr_t address;
	isc_region_t r;
	isc_result_t result;
	dns_fixedname_t keyname;
	dns_fixedname_t ownername;
	isc_buffer_t namestr, keybuf;
	unsigned char keydata[9];
	dns_message_t *query;
	dns_request_t *request;
	static char keystr[] = "0123456789ab";

	isc_event_free(&event);

	result = ISC_R_FAILURE;
	if (inet_pton(AF_INET, "10.53.0.1", &inaddr) != 1)
		CHECK("inet_pton", result);
	isc_sockaddr_fromin(&address, &inaddr, PORT);

	dns_fixedname_init(&keyname);
	isc_buffer_constinit(&namestr, "tkeytest.", 9);
	isc_buffer_add(&namestr, 9);
	result = dns_name_fromtext(dns_fixedname_name(&keyname), &namestr,
				   NULL, 0, NULL);
	CHECK("dns_name_fromtext", result);

	dns_fixedname_init(&ownername);
	isc_buffer_constinit(&namestr, ownername_str, strlen(ownername_str));
	isc_buffer_add(&namestr, strlen(ownername_str));
	result = dns_name_fromtext(dns_fixedname_name(&ownername), &namestr,
				   NULL, 0, NULL);
	CHECK("dns_name_fromtext", result);

	isc_buffer_init(&keybuf, keydata, 9);
	result = isc_base64_decodestring(keystr, &keybuf);
	CHECK("isc_base64_decodestring", result);

	isc_buffer_usedregion(&keybuf, &r);

	initialkey = NULL;
	result = dns_tsigkey_create(dns_fixedname_name(&keyname),
				    DNS_TSIG_HMACMD5_NAME,
				    isc_buffer_base(&keybuf),
				    isc_buffer_usedlength(&keybuf),
				    ISC_FALSE, NULL, 0, 0, mctx, ring,
				    &initialkey);
	CHECK("dns_tsigkey_create", result);

	query = NULL;
	result = dns_message_create(mctx, DNS_MESSAGE_INTENTRENDER, &query);
	CHECK("dns_message_create", result);

	result = dns_tkey_builddhquery(query, ourkey,
				       dns_fixedname_name(&ownername),
				       DNS_TSIG_HMACMD5_NAME, &nonce, 3600);
	CHECK("dns_tkey_builddhquery", result);

	request = NULL;
	result = dns_request_create(requestmgr, query, &address,
				    DNS_REQUESTOPT_TCP, initialkey,
				    TIMEOUT, task, recvquery, query,
				    &request);
	CHECK("dns_request_create", result);
}