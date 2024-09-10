int main(int argc, char **argv)
{
	int port = 0;
	int messagenumber = 5;
	char local_addr[256];
	int c;
	int mclient = 1;
	char peer_address[129] = "\0";
	int peer_port = PEER_DEFAULT_PORT;

	char rest_api_separator = ':';
	int use_null_cipher=0;

	set_logfile("stdout");

	set_execdir();

	set_system_parameters(0);

	ns_bzero(local_addr, sizeof(local_addr));

	while ((c = getopt(argc, argv, "d:p:l:n:L:m:e:r:u:w:i:k:z:W:C:E:F:vsyhcxXgtTSAPDNOUHMRIGB")) != -1) {
		switch (c){
		case 'B':
			random_disconnect = 1;
			break;
		case 'G':
			extra_requests = 1;
			break;
		case 'F':
			STRCPY(cipher_suite,optarg);
			break;
		case 'I':
			no_permissions = 1;
			break;
		case 'M':
			mobility = 1;
			break;
		case 'H':
			shatype = SHATYPE_SHA256;
			break;
		case 'E':
		{
			char* fn = find_config_file(optarg,1);
			if(!fn) {
				fprintf(stderr,"ERROR: file %s not found\n",optarg);
				exit(-1);
			}
			STRCPY(ca_cert_file,fn);
		}
			break;
		case 'O':
			dos = 1;
			break;
		case 'C':
			rest_api_separator=*optarg;
			break;
		case 'D':
			mandatory_channel_padding = 1;
			break;
		case 'N':
			negative_test = 1;
			break;
		case 'R':
			negative_protocol_test = 1;
			break;
		case 'z':
			RTP_PACKET_INTERVAL = atoi(optarg);
			break;
		case 'A':
			use_short_term = 1;
			break;
		case 'u':
			STRCPY(g_uname, optarg);
			break;
		case 'w':
			STRCPY(g_upwd, optarg);
			break;
		case 'g':
			dont_fragment = 1;
			break;
		case 'd':
			STRCPY(client_ifname, optarg);
			break;
		case 'x':
			default_address_family = STUN_ATTRIBUTE_REQUESTED_ADDRESS_FAMILY_VALUE_IPV6;
			break;
		case 'X':
			default_address_family = STUN_ATTRIBUTE_REQUESTED_ADDRESS_FAMILY_VALUE_IPV4;
			break;
		case 'l':
			clmessage_length = atoi(optarg);
			break;
		case 's':
			do_not_use_channel = 1;
			break;
		case 'n':
			messagenumber = atoi(optarg);
			break;
		case 'p':
			port = atoi(optarg);
			break;
		case 'L':
			STRCPY(local_addr, optarg);
			break;
		case 'e':
			STRCPY(peer_address, optarg);
			break;
		case 'r':
			peer_port = atoi(optarg);
			break;
		case 'v':
			clnet_verbose = TURN_VERBOSE_NORMAL;
			break;
		case 'h':
			hang_on = 1;
			break;
		case 'c':
			no_rtcp = 1;
			break;
		case 'm':
			mclient = atoi(optarg);
			break;
		case 'y':
			c2c = 1;
			break;
		case 't':
			use_tcp = 1;
			break;
		case 'P':
			passive_tcp = 1;
			/* implies 'T': */
			/* no break */
		case 'T':
			relay_transport = STUN_ATTRIBUTE_TRANSPORT_TCP_VALUE;
			break;
		case 'U':
		  use_null_cipher = 1;
		  /* implies 'S' */
		  /* no break */
		case 'S':
			use_secure = 1;
			break;
		case 'W':
			g_use_auth_secret_with_timestamp = 1;
			STRCPY(g_auth_secret,optarg);
			break;
		case 'i':
		{
			char* fn = find_config_file(optarg,1);
			if(!fn) {
				fprintf(stderr,"ERROR: file %s not found\n",optarg);
				exit(-1);
			}
			STRCPY(cert_file,fn);
			free(fn);
		}
			break;
		case 'k':
		{
			char* fn = find_config_file(optarg,1);
			if(!fn) {
				fprintf(stderr,"ERROR: file %s not found\n",optarg);
				exit(-1);
			}
			STRCPY(pkey_file,fn);
			free(fn);
		}
			break;
		default:
			fprintf(stderr, "%s\n", Usage);
			exit(1);
		}
	}

	if(g_use_auth_secret_with_timestamp) {

		if(use_short_term) {
			fprintf(stderr,"ERROR: You cannot use authentication secret (REST API) with short-term credentials mechanism.\n");
			exit(-1);
		}
		{
			char new_uname[1025];
			const unsigned long exp_time = 3600 * 24; /* one day */
			if(g_uname[0]) {
			  snprintf(new_uname,sizeof(new_uname),"%lu%c%s",(unsigned long)time(NULL) + exp_time,rest_api_separator, (char*)g_uname);
			} else {
			  snprintf(new_uname,sizeof(new_uname),"%lu", (unsigned long)time(NULL) + exp_time);
			}
			STRCPY(g_uname,new_uname);
		}
		{
			u08bits hmac[MAXSHASIZE];
			unsigned int hmac_len;

			switch(shatype) {
			case SHATYPE_SHA256:
				hmac_len = SHA256SIZEBYTES;
				break;
			default:
				hmac_len = SHA1SIZEBYTES;
			};

			hmac[0]=0;

			if(stun_calculate_hmac(g_uname, strlen((char*)g_uname), (u08bits*)g_auth_secret, strlen(g_auth_secret), hmac, &hmac_len, shatype)>=0) {
				size_t pwd_length = 0;
				char *pwd = base64_encode(hmac,hmac_len,&pwd_length);

				if(pwd) {
					if(pwd_length>0) {
						ns_bcopy(pwd,g_upwd,pwd_length);
						g_upwd[pwd_length]=0;
					}
				}
				free(pwd);
			}
		}
	}

	if(is_TCP_relay()) {
		dont_fragment = 0;
		no_rtcp = 1;
		c2c = 1;
		use_tcp = 1;
		do_not_use_channel = 1;
	}

	if(port == 0) {
		if(use_secure)
			port = DEFAULT_STUN_TLS_PORT;
		else
			port = DEFAULT_STUN_PORT;
	}

	if (clmessage_length < (int) sizeof(message_info))
		clmessage_length = (int) sizeof(message_info);

	const int max_header = 100;
	if(clmessage_length > (int)(STUN_BUFFER_SIZE-max_header)) {
		fprintf(stderr,"Message length was corrected to %d\n",(STUN_BUFFER_SIZE-max_header));
		clmessage_length = (int)(STUN_BUFFER_SIZE-max_header);
	}

	if (optind >= argc) {
		fprintf(stderr, "%s\n", Usage);
		exit(-1);
	}

	if (!c2c) {
		if (make_ioa_addr((const u08bits*) peer_address, peer_port, &peer_addr) < 0)
			return -1;
		if(peer_addr.ss.sa_family == AF_INET6)
			default_address_family = STUN_ATTRIBUTE_REQUESTED_ADDRESS_FAMILY_VALUE_IPV6;

	}

	/* SSL Init ==>> */

	if(use_secure) {

		SSL_load_error_strings();
		OpenSSL_add_ssl_algorithms();

		const char *csuite = "ALL"; //"AES256-SHA" "DH"
		if(use_null_cipher)
			csuite = "eNULL";
		else if(cipher_suite[0])
			csuite=cipher_suite;

		if(use_tcp) {
		  root_tls_ctx[root_tls_ctx_num] = SSL_CTX_new(SSLv23_client_method());
		  SSL_CTX_set_cipher_list(root_tls_ctx[root_tls_ctx_num], csuite);
		  root_tls_ctx_num++;
		  root_tls_ctx[root_tls_ctx_num] = SSL_CTX_new(SSLv3_client_method());
		  SSL_CTX_set_cipher_list(root_tls_ctx[root_tls_ctx_num], csuite);
		  root_tls_ctx_num++;
		  root_tls_ctx[root_tls_ctx_num] = SSL_CTX_new(TLSv1_client_method());
		  SSL_CTX_set_cipher_list(root_tls_ctx[root_tls_ctx_num], csuite);
		  root_tls_ctx_num++;
#if defined(SSL_TXT_TLSV1_1)
		  root_tls_ctx[root_tls_ctx_num] = SSL_CTX_new(TLSv1_1_client_method());
		  SSL_CTX_set_cipher_list(root_tls_ctx[root_tls_ctx_num], csuite);
		  root_tls_ctx_num++;
#if defined(SSL_TXT_TLSV1_2)
		  root_tls_ctx[root_tls_ctx_num] = SSL_CTX_new(TLSv1_2_client_method());
		  SSL_CTX_set_cipher_list(root_tls_ctx[root_tls_ctx_num], csuite);
		  root_tls_ctx_num++;
#endif
#endif
		} else {
#if defined(TURN_NO_DTLS)
		  fprintf(stderr,"ERROR: DTLS is not supported.\n");
		  exit(-1);
#else
		  if(OPENSSL_VERSION_NUMBER < 0x10000000L) {
		  	TURN_LOG_FUNC(TURN_LOG_LEVEL_WARNING, "WARNING: OpenSSL version is rather old, DTLS may not be working correctly.\n");
		  }
		  root_tls_ctx[root_tls_ctx_num] = SSL_CTX_new(DTLSv1_client_method());
		  SSL_CTX_set_cipher_list(root_tls_ctx[root_tls_ctx_num], csuite);
		  root_tls_ctx_num++;
#endif
		}

		int sslind = 0;
		for(sslind = 0; sslind<root_tls_ctx_num; sslind++) {

			if(cert_file[0]) {
				if (!SSL_CTX_use_certificate_chain_file(root_tls_ctx[sslind], cert_file)) {
					TURN_LOG_FUNC(TURN_LOG_LEVEL_ERROR, "\nERROR: no certificate found!\n");
					exit(-1);
				}
			}

			if (!SSL_CTX_use_PrivateKey_file(root_tls_ctx[sslind], pkey_file,
						SSL_FILETYPE_PEM)) {
				TURN_LOG_FUNC(TURN_LOG_LEVEL_ERROR, "\nERROR: no private key found!\n");
				exit(-1);
			}

			if(cert_file[0]) {
				if (!SSL_CTX_check_private_key(root_tls_ctx[sslind])) {
					TURN_LOG_FUNC(TURN_LOG_LEVEL_ERROR, "\nERROR: invalid private key!\n");
					exit(-1);
				}
			}

			if (ca_cert_file[0]) {
				if (!SSL_CTX_load_verify_locations(root_tls_ctx[sslind], ca_cert_file, NULL )) {
					TURN_LOG_FUNC(TURN_LOG_LEVEL_ERROR,
							"ERROR: cannot load CA from file: %s\n",
							ca_cert_file);
				}

				/* Set to require peer (client) certificate verification */
				SSL_CTX_set_verify(root_tls_ctx[sslind], SSL_VERIFY_PEER, NULL );

				/* Set the verification depth to 9 */
				SSL_CTX_set_verify_depth(root_tls_ctx[sslind], 9);
			} else {
				SSL_CTX_set_verify(root_tls_ctx[sslind], SSL_VERIFY_NONE, NULL );
			}

			if(!use_tcp)
				SSL_CTX_set_read_ahead(root_tls_ctx[sslind], 1);
		}
	}

	start_mclient(argv[optind], port, client_ifname, local_addr, messagenumber, mclient);

	return 0;
}