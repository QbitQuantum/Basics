ATF_TC_BODY(tsig_tcp, tc) {
	const dns_name_t *tsigowner = NULL;
	dns_fixedname_t fkeyname;
	dns_message_t *msg = NULL;
	dns_name_t *keyname;
	dns_tsig_keyring_t *ring = NULL;
	dns_tsigkey_t *key = NULL;
	isc_buffer_t *buf = NULL;
	isc_buffer_t *querytsig = NULL;
	isc_buffer_t *tsigin = NULL;
	isc_buffer_t *tsigout = NULL;
	isc_result_t result;
	unsigned char secret[16] = { 0 };
	dst_context_t *tsigctx = NULL;
	dst_context_t *outctx = NULL;

	UNUSED(tc);

	result = dns_test_begin(stderr, ISC_TRUE);
	ATF_REQUIRE_EQ(result, ISC_R_SUCCESS);

	/* isc_log_setdebuglevel(lctx, 99); */

	dns_fixedname_init(&fkeyname);
	keyname = dns_fixedname_name(&fkeyname);
	result = dns_name_fromstring(keyname, "test", 0, NULL);
	ATF_REQUIRE_EQ(result, ISC_R_SUCCESS);

	result = dns_tsigkeyring_create(mctx, &ring);
	ATF_REQUIRE_EQ(result, ISC_R_SUCCESS);

	result = dns_tsigkey_create(keyname, dns_tsig_hmacsha256_name,
				    secret, sizeof(secret), ISC_FALSE,
				    NULL, 0, 0, mctx, ring, &key);
	ATF_REQUIRE_EQ(result, ISC_R_SUCCESS);

	/*
	 * Create request.
	 */
	result = isc_buffer_allocate(mctx, &buf, 65535);
	ATF_REQUIRE_EQ(result, ISC_R_SUCCESS);
	render(buf, 0, key, &tsigout, &querytsig, NULL);
	isc_buffer_free(&buf);

	/*
	 * Create response message 1.
	 */
	result = isc_buffer_allocate(mctx, &buf, 65535);
	ATF_REQUIRE_EQ(result, ISC_R_SUCCESS);
	render(buf, DNS_MESSAGEFLAG_QR, key, &querytsig, &tsigout, NULL);

	/*
	 * Process response message 1.
	 */
	result = dns_message_create(mctx, DNS_MESSAGE_INTENTPARSE, &msg);
	ATF_CHECK_EQ_MSG(result, ISC_R_SUCCESS,
			 "dns_message_create: %s",
			 dns_result_totext(result));

	result = dns_message_settsigkey(msg, key);
	ATF_CHECK_EQ_MSG(result, ISC_R_SUCCESS,
			 "dns_message_settsigkey: %s",
			 dns_result_totext(result));

	result = dns_message_parse(msg, buf, 0);
	ATF_CHECK_EQ_MSG(result, ISC_R_SUCCESS,
			 "dns_message_parse: %s",
			 dns_result_totext(result));

	printmessage(msg);

	result = dns_message_setquerytsig(msg, querytsig);
	ATF_CHECK_EQ_MSG(result, ISC_R_SUCCESS,
			 "dns_message_setquerytsig: %s",
			 dns_result_totext(result));

	result = dns_tsig_verify(buf, msg, NULL, NULL);
	ATF_CHECK_EQ_MSG(result, ISC_R_SUCCESS,
			 "dns_tsig_verify: %s",
			 dns_result_totext(result));
	ATF_CHECK_EQ(msg->verified_sig, 1);
	ATF_CHECK_EQ(msg->tsigstatus, dns_rcode_noerror);

	/*
	 * Check that we have a TSIG in the first message.
	 */
	ATF_REQUIRE(dns_message_gettsig(msg, &tsigowner) != NULL);

	result = dns_message_getquerytsig(msg, mctx, &tsigin);
	ATF_CHECK_EQ_MSG(result, ISC_R_SUCCESS,
			 "dns_message_getquerytsig: %s",
			 dns_result_totext(result));

	tsigctx = msg->tsigctx;
	msg->tsigctx = NULL;
	isc_buffer_free(&buf);
	dns_message_destroy(&msg);

	result = dst_context_create3(key->key, mctx, DNS_LOGCATEGORY_DNSSEC,
				     ISC_FALSE, &outctx);
	ATF_REQUIRE_EQ(result, ISC_R_SUCCESS);

	/*
	 * Start digesting.
	 */
	result = add_mac(outctx, tsigout);
	ATF_REQUIRE_EQ(result, ISC_R_SUCCESS);

	/*
	 * Create response message 2.
	 */
	result = isc_buffer_allocate(mctx, &buf, 65535);
	ATF_REQUIRE_EQ(result, ISC_R_SUCCESS);

	ATF_REQUIRE_EQ(result, ISC_R_SUCCESS);
	render(buf, DNS_MESSAGEFLAG_QR, key, &tsigout, &tsigout, outctx);

	/*
	 * Process response message 2.
	 */
	result = dns_message_create(mctx, DNS_MESSAGE_INTENTPARSE, &msg);
	ATF_CHECK_EQ_MSG(result, ISC_R_SUCCESS,
			 "dns_message_create: %s",
			 dns_result_totext(result));

	msg->tcp_continuation = 1;
	msg->tsigctx = tsigctx;
	tsigctx = NULL;

	result = dns_message_settsigkey(msg, key);
	ATF_CHECK_EQ_MSG(result, ISC_R_SUCCESS,
			 "dns_message_settsigkey: %s",
			 dns_result_totext(result));

	result = dns_message_parse(msg, buf, 0);
	ATF_CHECK_EQ_MSG(result, ISC_R_SUCCESS,
			 "dns_message_parse: %s",
			 dns_result_totext(result));

	printmessage(msg);

	result = dns_message_setquerytsig(msg, tsigin);
	ATF_CHECK_EQ_MSG(result, ISC_R_SUCCESS,
			 "dns_message_setquerytsig: %s",
			 dns_result_totext(result));

	result = dns_tsig_verify(buf, msg, NULL, NULL);
	ATF_CHECK_EQ_MSG(result, ISC_R_SUCCESS,
			 "dns_tsig_verify: %s",
			 dns_result_totext(result));
	ATF_CHECK_EQ(msg->verified_sig, 1);
	ATF_CHECK_EQ(msg->tsigstatus, dns_rcode_noerror);

	/*
	 * Check that we don't have a TSIG in the second message.
	 */
	tsigowner = NULL;
	ATF_REQUIRE(dns_message_gettsig(msg, &tsigowner) == NULL);

	tsigctx = msg->tsigctx;
	msg->tsigctx = NULL;
	isc_buffer_free(&buf);
	dns_message_destroy(&msg);

	/*
	 * Create response message 3.
	 */
	result = isc_buffer_allocate(mctx, &buf, 65535);
	ATF_REQUIRE_EQ(result, ISC_R_SUCCESS);
	render(buf, DNS_MESSAGEFLAG_QR, key, &tsigout, &tsigout, outctx);

	result = add_tsig(outctx, key, buf);
	ATF_CHECK_EQ_MSG(result, ISC_R_SUCCESS,
			 "add_tsig: %s",
			 dns_result_totext(result));

	/*
	 * Process response message 3.
	 */
	result = dns_message_create(mctx, DNS_MESSAGE_INTENTPARSE, &msg);
	ATF_CHECK_EQ_MSG(result, ISC_R_SUCCESS,
			 "dns_message_create: %s",
			 dns_result_totext(result));

	msg->tcp_continuation = 1;
	msg->tsigctx = tsigctx;
	tsigctx = NULL;

	result = dns_message_settsigkey(msg, key);
	ATF_CHECK_EQ_MSG(result, ISC_R_SUCCESS,
			 "dns_message_settsigkey: %s",
			 dns_result_totext(result));

	result = dns_message_parse(msg, buf, 0);
	ATF_CHECK_EQ_MSG(result, ISC_R_SUCCESS,
			 "dns_message_parse: %s",
			 dns_result_totext(result));

	printmessage(msg);

	/*
	 * Check that we had a TSIG in the third message.
	 */
	ATF_REQUIRE(dns_message_gettsig(msg, &tsigowner) != NULL);

	result = dns_message_setquerytsig(msg, tsigin);
	ATF_CHECK_EQ_MSG(result, ISC_R_SUCCESS,
			 "dns_message_setquerytsig: %s",
			 dns_result_totext(result));

	result = dns_tsig_verify(buf, msg, NULL, NULL);
	ATF_CHECK_EQ_MSG(result, ISC_R_SUCCESS,
			 "dns_tsig_verify: %s",
			 dns_result_totext(result));
	ATF_CHECK_EQ(msg->verified_sig, 1);
	ATF_CHECK_EQ(msg->tsigstatus, dns_rcode_noerror);

	if (tsigin != NULL)
		isc_buffer_free(&tsigin);

	result = dns_message_getquerytsig(msg, mctx, &tsigin);
	ATF_CHECK_EQ_MSG(result, ISC_R_SUCCESS,
			 "dns_message_getquerytsig: %s",
			 dns_result_totext(result));

	isc_buffer_free(&buf);
	dns_message_destroy(&msg);

	if (outctx != NULL)
		dst_context_destroy(&outctx);
	if (querytsig != NULL)
		isc_buffer_free(&querytsig);
	if (tsigin != NULL)
		isc_buffer_free(&tsigin);
	if (tsigout != NULL)
		isc_buffer_free(&tsigout);
	if (buf != NULL)
		isc_buffer_free(&buf);
	if (msg != NULL)
		dns_message_destroy(&msg);
	if (key != NULL)
		dns_tsigkey_detach(&key);
	if (ring != NULL)
		dns_tsigkeyring_detach(&ring);
	dns_test_end();
}