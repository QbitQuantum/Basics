/* {{{ mysqlnd_sha256_get_rsa_key */
static RSA *
mysqlnd_sha256_get_rsa_key(MYSQLND_CONN_DATA * conn,
						   const MYSQLND_SESSION_OPTIONS * const session_options,
						   const MYSQLND_PFC_DATA * const pfc_data
						  )
{
	RSA * ret = NULL;
	const char * fname = (pfc_data->sha256_server_public_key && pfc_data->sha256_server_public_key[0] != '\0')?
								pfc_data->sha256_server_public_key:
								MYSQLND_G(sha256_server_public_key);
	php_stream * stream;
	DBG_ENTER("mysqlnd_sha256_get_rsa_key");
	DBG_INF_FMT("options_s256_pk=[%s] MYSQLND_G(sha256_server_public_key)=[%s]",
				 pfc_data->sha256_server_public_key? pfc_data->sha256_server_public_key:"n/a",
				 MYSQLND_G(sha256_server_public_key)? MYSQLND_G(sha256_server_public_key):"n/a");
	if (!fname || fname[0] == '\0') {
		MYSQLND_PACKET_SHA256_PK_REQUEST * pk_req_packet = NULL;
		MYSQLND_PACKET_SHA256_PK_REQUEST_RESPONSE * pk_resp_packet = NULL;

		do {
			DBG_INF("requesting the public key from the server");
			pk_req_packet = conn->payload_decoder_factory->m.get_sha256_pk_request_packet(conn->payload_decoder_factory, FALSE);
			if (!pk_req_packet) {
				SET_OOM_ERROR(conn->error_info);
				break;
			}
			pk_resp_packet = conn->payload_decoder_factory->m.get_sha256_pk_request_response_packet(conn->payload_decoder_factory, FALSE);
			if (!pk_resp_packet) {
				SET_OOM_ERROR(conn->error_info);
				PACKET_FREE(pk_req_packet);
				break;
			}

			if (! PACKET_WRITE(pk_req_packet)) {
				DBG_ERR_FMT("Error while sending public key request packet");
				php_error(E_WARNING, "Error while sending public key request packet. PID=%d", getpid());
				SET_CONNECTION_STATE(&conn->state, CONN_QUIT_SENT);
				break;
			}
			if (FAIL == PACKET_READ(pk_resp_packet) || NULL == pk_resp_packet->public_key) {
				DBG_ERR_FMT("Error while receiving public key");
				php_error(E_WARNING, "Error while receiving public key. PID=%d", getpid());
				SET_CONNECTION_STATE(&conn->state, CONN_QUIT_SENT);
				break;
			}
			DBG_INF_FMT("Public key(%d):\n%s", pk_resp_packet->public_key_len, pk_resp_packet->public_key);
			/* now extract the public key */
			{
				BIO * bio = BIO_new_mem_buf(pk_resp_packet->public_key, pk_resp_packet->public_key_len);
				ret = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL);
				BIO_free(bio);
			}
		} while (0);
		PACKET_FREE(pk_req_packet);
		PACKET_FREE(pk_resp_packet);

		DBG_INF_FMT("ret=%p", ret);
		DBG_RETURN(ret);

		SET_CLIENT_ERROR(conn->error_info, CR_UNKNOWN_ERROR, UNKNOWN_SQLSTATE,
			"sha256_server_public_key is not set for the connection or as mysqlnd.sha256_server_public_key");
		DBG_ERR("server_public_key is not set");
		DBG_RETURN(NULL);
	} else {
		zend_string * key_str;
		DBG_INF_FMT("Key in a file. [%s]", fname);
		stream = php_stream_open_wrapper((char *) fname, "rb", REPORT_ERRORS, NULL);

		if (stream) {
			if ((key_str = php_stream_copy_to_mem(stream, PHP_STREAM_COPY_ALL, 0)) != NULL) {
				BIO * bio = BIO_new_mem_buf(ZSTR_VAL(key_str), ZSTR_LEN(key_str));
				ret = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL);
				BIO_free(bio);
				DBG_INF("Successfully loaded");
				DBG_INF_FMT("Public key:%*.s", ZSTR_LEN(key_str), ZSTR_VAL(key_str));
				zend_string_release(key_str);
			}
			php_stream_close(stream);
		}
	}
	DBG_RETURN(ret);
}