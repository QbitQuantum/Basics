/*=================================================================================================*/
E_SERVER_FSM_RESULT ssl_server_entry(SSL_SERVER_PARS parameters)
{

	/* server parameters */
	uint8_t				echo			= parameters.echo;
	char *				pc_filename		= parameters.pc_filename;
	char *				pc_ciphersuites	= parameters.pc_ciphersuites;
	uint16_t			u_port			= parameters.u_port;
	e_sslVer_t			versmin			= parameters.versmin;
	e_sslVer_t			versmax			= parameters.versmax;
	char *				key				= parameters.key;
	e_sslKeyType_t		keyType			= parameters.keyType;
	char *				keyParameters	= parameters.keyParameters;
	char **				certs			= parameters.ppc_certs;
	char **				CAcerts			= parameters.ppc_CAcerts;
	e_sslAuthLevel_t	authlevel		= parameters.authlevel;


	char c_filebuf[SSL_WRITE_BLOCK_LEN];
	size_t n;

	char	c_mode = 1;

	en_gciResult_t err;

	/* Check the state of the server */
	switch (i_state) {
	case SSL_SERVER_INIT:
		/*============================================================================*/
		/*
		 * General SSL Initialisation
		 */
		/*============================================================================*/
		/* Initialises the SSL module */
		SSL_init();

		/* Initialises the crypto */
		//TODO sw - where to become the user name + password ??
		err = gciInit(NULL, 0, NULL, 0);

		//OLD-CW: cw_crypto_init();
//		{
//			/*
//			 * Use some "random" bytes to init the PRNG
//			 */
//			uint8_t c_rand[] = { 0x42, 0x72, 0x75, 0x63, 0x65, 0x20, 0x53, 0x63, 0x68, //TODO sw - this step in gci_init
//					0x6E, 0x65, 0x69, 0x65, 0x72, 0x21, 0x0D, 0x0A, 0x00 };
//			cw_prng_init(c_rand, sizeof(c_rand));
//		}

		/*
		 * Initialisation of keymanager for DHE and DHE private key generation
		 */
		km_dhe_init();

		/*============================================================================*/
		/*
		 * Initialization of the SSL settings for the demonstration SSL context
		 */
		/*============================================================================*/

		/* Initialises the SSL context */
		sslSoc_initSett(&s_sslSett, keyType);

		/*
		 * Init the time-function pointer implicit to NULL, this will disable
		 * checking of the validity of the used certificates
		 * (To enable 'getCurrentTime' function should be used)
		 */
		sslSoc_setTimeFunc(&s_sslSett, NULL);

		/* Setting up the SSL version */
		sslSoc_setVer(&s_sslSett, versmin, versmax);

		/* Setting up the SSL timeout value */
		sslSoc_setSessTimeout(&s_sslSett, 600);

		/* Setting up the SSL authentification behavior */
		sslSoc_setAuthLvl(&s_sslSett, authlevel);

		/* Setting up read and write fonctions */
		sslSoc_setReadWrite(&s_sslSett, sslTarget_read, sslTarget_write);

		/* Initialize server CA certificates */
		if (CAcerts != NULL) {
			init_server_CA_certs(CAcerts);

		}

		/* ===== Initialize Server Certificates and private key ===== */

		s_cdbCert_t cdb_tmp;
		s_sslCertList_t * list_head = sslSoc_getCertChainList(&s_sslSett);

		if (certs != NULL) {
			int i = 0;
			while (certs[i] != NULL) {
				/*
				printf("certs[%i] = '%s'\n", i, certs[i]);
				 */
				cdb_initCert_linear(&server_cdb_certs[i], certs[i]);
				list_head = sslCert_addToList(list_head,
						&server_cert_list[i], NULL, &server_cdb_certs[i]);
				i++;
			}
		} else {
			/* use static pre-defined certificates if
			 * no external certificate has been provided */
			/*
			int i;
			for (i = 0; i < SSL_SERVERCERTS_NUM; ++i) {
				cdb_initCert_linear(&server_cdb_certs[i], server_certificates_[i]);
				list_head = SSL_cert_list_add(list_head, &server_cert_list[i], NULL, &server_cdb_certs[i]);
			}
			 */
		}

		sslSoc_setCertChainList (&s_sslSett, list_head);

		if (key != NULL) {
			cdb_initCert_linear(&cdb_tmp, key);
		} else {
			/*cdb_initCert_linear(&cdb_tmp, ServerPrivateKey);*/
		}
		switch(keyType)
		{
		case E_SSL_KEY_EC:
			if (sslSoc_setECCPrivKey(&s_sslSett, &cdb_tmp) != E_SSL_OK) {
				printf(DBG_STRING "Import of ECC private key failed", __FILE__, __LINE__);
				return (E_SERVER_FSM_ERROR);
			} /* if */
			break;

		case E_SSL_KEY_RSA:
			if (sslSoc_setRsaPrivKey(&s_sslSett, &cdb_tmp) != E_SSL_OK) {
				printf(DBG_STRING "Import of RSA private key failed", __FILE__, __LINE__);
				return (E_SERVER_FSM_ERROR);
			} /* if */
			break;

		default:
			return (E_SERVER_FSM_ERROR);
			break;
		} /* switch */

	case SSL_SERVER_REINIT:

		/*============================================================================*/
		/*
		 * Initialize socket specific features
		 */
		/*============================================================================*/

		/* Creates a socket */
#ifdef _WIN32
		if((srv_socdesc = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
		{
			printf("Could not create socket : %s\n" , WSAGetLastError());
			WSACleanup();
			return (E_SERVER_FSM_ERROR);
		}
#elif __linux
		if((srv_socdesc = socket(AF_INET , SOCK_STREAM , 0 )) < 0)
		{
			printf("Could not create socket : %s\n" , strerror(errno));
			return (E_SERVER_FSM_ERROR);
		}
#endif
		setsockopt(srv_socdesc, SOL_SOCKET, SO_REUSEADDR, &c_mode, sizeof(int));
		printf("\n\rSocket created.\n");

		/* Binding */
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = INADDR_ANY;
		server.sin_port = htons(u_port);

#ifdef _WIN32
		if( bind(srv_socdesc ,(struct sockaddr *)&server , sizeof(server)) == INVALID_SOCKET)
		{
			printf("Bind failed with error code : %s\n" , WSAGetLastError());
			WSACleanup();
			return (E_SERVER_FSM_ERROR);
		}
#elif __linux
		if( bind(srv_socdesc ,(struct sockaddr *)&server , sizeof(server)) < 0)
		{
			printf("Bind failed with error code : %s\n" , strerror(errno));
			return (E_SERVER_FSM_ERROR);
		}
#endif



		puts("Bind done");

		/* Listening */
		listen(srv_socdesc , 3);
		puts("Waiting for incoming connections...");

		i_state = SSL_SERVER_LISTEN;
		break;
		/* SSL_SERVER_INIT */

	case SSL_SERVER_LISTEN:
		i_addr_len = sizeof(struct sockaddr_in);
		cli_socdesc = accept(srv_socdesc , (struct sockaddr *)&client, &i_addr_len);
		if (cli_socdesc == INVALID_SOCKET)
		{
			break;
		}

		/* Nonblocking mode */
#ifdef _WIN32
		ioctlsocket(cli_socdesc, FIONBIO, (u_long *)&c_mode);
#elif __linux
		fcntl(cli_socdesc, F_SETFL, O_NONBLOCK);
#endif
		printf("\n\rConnection accepted\n");
		/* Checks if a SSL context is available */
		if ((ps_sslCtx = sslSoc_new ( &s_sslSett )) == NULL)
		{
			/* Not available */
			i_state = SSL_SERVER_CLOSE_ERR;
		}
		else
		{
			/* Available */
			sslSoc_setCtxFd(ps_sslCtx, cli_socdesc);

			/* set supported ciphersuites if list is provided */
			if (strlen(pc_ciphersuites) > 0) {
				sslSoc_setCtxCipList(ps_sslCtx, pc_ciphersuites);
			}

			int i=0;
			switch(keyType)
			{
			case E_SSL_KEY_EC:
				//loop all cipher suites provided
				//Remove all non-ECDSA cipher suites, as certificate cannot handle non-ECDSA
				for(i=0; i<SSL_CIPSPEC_COUNT; i++)
				{
					if( //remove every ECDHE curve
						ps_sslCtx->s_sslGut.ae_cipSpecs[i] != TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA &&
						ps_sslCtx->s_sslGut.ae_cipSpecs[i] != TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA  &&
						ps_sslCtx->s_sslGut.ae_cipSpecs[i] != TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA
					)
					{
						ps_sslCtx->s_sslGut.ae_cipSpecs[i] = TLS_NULL_WITH_NULL_NULL;
					}
				}


			break;
			case E_SSL_KEY_RSA:
			case E_SSL_KEY_UNDEFINED: //vpy: should be handled properly
				//Remove all ECDSA cipher suites, as certificate cannot handle ECDSA

				//loop all cipher suites provided
				for(i=0; i<SSL_CIPSPEC_COUNT; i++)
				{
					if( //remove every ECDHE curve
						ps_sslCtx->s_sslGut.ae_cipSpecs[i] == TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA ||
						ps_sslCtx->s_sslGut.ae_cipSpecs[i] == TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA  ||
						ps_sslCtx->s_sslGut.ae_cipSpecs[i] == TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA
					)
					{
						ps_sslCtx->s_sslGut.ae_cipSpecs[i] = TLS_NULL_WITH_NULL_NULL;
					}
				}
				break;
			}


			i_state = SSL_SERVER_ACCEPT;
			LOG_OK("Accept");
		} /* if ... else */
		break;
		/* SSL_SERVER_LISTEN */

	case SSL_SERVER_ACCEPT:
		/* Operates the SSL Handshake */
		switch(sslSoc_accept (ps_sslCtx)) {
		case E_SSL_AGAIN:
			break;
		case E_SSL_OK:
			/* print some connection specifics */
			printf("\n>INFO::Ciphers: RX = 0x%.4X, TX = 0x%.4X\n",
					ps_sslCtx->s_sslGut.e_rxCipSpec,
					ps_sslCtx->s_sslGut.e_txCipSpec);
			printf("\n>INFO::Version: 0x%.4X\n", ps_sslCtx->e_ver);

			i_state = SSL_SERVER_READ;
			/* Reads the current system time */
			l_timeStart = fp_getCurTime();
			l_Start = l_timeStart;
			l_bytesRead = 0;
			break;
		case E_SSL_ERROR:
		default:
			LOG_ERR("sslSoc_accept error");
			i_state = SSL_SERVER_CLOSE_ERR;
			ps_sslCtx->e_socState = E_SSL_SOCKET_UNUSED;
			break;
		} /* switch */

		break;
		/* SSL_SERVER_ACCEPT */

		case SSL_SERVER_READ:
			l_bytes = 0;
			/* Just read and show on console. */
			/* Read */
			memset(c_readBuf, 0, sizeof(c_readBuf));

			/* read from SSL socket */
			l_bytes = sslSoc_read(ps_sslCtx, c_readBuf, sizeof(c_readBuf));
			if (l_bytes > 0) {
				if (echo != 0) {
					/* server echo: transmit received byte string */
					memcpy(c_writeBuf, c_readBuf, l_bytes);
					l_bytesWrite = l_bytes;
					i_state = SSL_SERVER_WRITE;
				} else if (strncmp(c_readBuf, "GET / HTTP/1.1\r\n\r\n", 16) == 0) {

					/* open file to transmit */
					fp = fopen(pc_filename, "rb");

					if (fp == NULL) {
						/* could not open file => send an error message */
						l_bytesWrite = sprintf(c_writeBuf, "HTTP/1.1 404 Not Found\r\n\r\n");
						i_state = SSL_SERVER_WRITE;
					} else {

						/* determine the number of bytes in the file to put
						 * that piece of information into the HTTP header */
						n = 0;
						while (fgetc(fp) != EOF) {
							n++;
						}
						rewind(fp);

						printf("Transmitting file: '%s'\n", pc_filename);

						/* prepare HTTP header */
						l_bytesWrite = sprintf(c_writeBuf,
								"HTTP/1.1 200 OK\r\n"\
								"Content-Type: application/octet-stream\r\n"\
								"Content-Length: %d\r\n\r\n", n);

						/* next step: read first chunk of bytes from file */
						i_state = SSL_SERVER_READ_FILE;
					}
				}
				break;
			} else if (l_bytes < 0) {
				switch(l_bytes) {
				case E_SSL_ERROR:
					i_state = SSL_SERVER_CLOSING;
					break;

				case E_SSL_WANT_WRITE:
					i_state = SSL_SERVER_FLUSH;
					break;

				default:
					break;
				}
			} else if (l_bytes == E_SSL_AGAIN) {
				break;
			}

			i_state = SSL_SERVER_CLOSE;
			break;
			/* SSL_SERVER_READ */

		case SSL_SERVER_READ_FILE:

			n = 0;
			if (fp != NULL) {
				/* read chunk of bytes from file and copy to write buffer */
				n = fread(c_filebuf, 1, SSL_WRITE_BLOCK_LEN - l_bytesWrite - 100, fp);
			}
			memcpy(&(c_writeBuf[l_bytesWrite]), c_filebuf, n);
			l_bytesWrite += n;

			if (n > 0) {
				/* next step: send data just read from file to peer */
				i_state = SSL_SERVER_WRITE;
			} else {
				/* we have reached the end of the file: close file and connection */
				if (fp != NULL) {
					fclose(fp);
				}
				i_state = SSL_SERVER_CLOSING;
			}

			break; /* case SSL_SERVER_READ_FILE */

		case SSL_SERVER_WRITE:

			/* send data to peer */
			l_bytes = sslSoc_write(ps_sslCtx, (char*)c_writeBuf, l_bytesWrite);
			if (l_bytes > 0) {
				i_state = SSL_SERVER_FLUSH;
			} else {
				switch(l_bytes) {
				case E_SSL_ERROR:
					printf(DBG_STRING " sslSoc_write error %s", __FILE__, __LINE__, sslDiag_getError(ps_sslCtx));
					i_state = SSL_SERVER_CLOSING;
					break;

				case E_SSL_WANT_AGAIN:
					i_state = SSL_SERVER_READ;
					break;

				default:
					break;
				}
			}

			/* need to reset l_bytesWrite to zero because otherwise step
			 * SSL_SERVER_READ_FILE would *append* new data (thinking
			 * previous chunk of bytes from file is the HTTP header) */
			l_bytesWrite = 0;

			break; /* case SSL_SERVER_WRITE */

		case SSL_SERVER_FLUSH: {

			switch(sslSoc_flush(ps_sslCtx)) {
			case E_SSL_OK:
				if (echo != 0) {
					/* in echo mode: start listening again */
					i_state = SSL_SERVER_READ;
				} else {
					/* in normal mode: read next chunk of bytes from file */
					i_state = SSL_SERVER_READ_FILE;
				}
				break;
				/*
				 * It is not, so we can fall thru
				 */
			case E_SSL_WANT_AGAIN:
				i_state = SSL_SERVER_READ;
				break;
			case E_SSL_AGAIN:
				break;
			case E_SSL_ERROR:
			default:
				i_state = SSL_SERVER_CLOSING;
				break;
			}

		}/* SSL_SERVER_FLUSH */
		break;

		case SSL_SERVER_CLOSING:

		case SSL_SERVER_CLOSING_ERR:

			LOG_RAW("Shutting down SSL connection...");
			do {
				l_bytes = sslSoc_shutdown(ps_sslCtx);
				printf("sslSoc_shutdown(...) returned: %d\n", l_bytes);
				if (l_bytes == E_SSL_OK && i_state == SSL_SERVER_CLOSING) {
					/* connection successfully closed (passive close) */
					i_state = SSL_SERVER_CLOSE;
				} else if (l_bytes != E_SSL_AGAIN) {
					/* connection successfully closed (error case) */
					i_state = SSL_SERVER_CLOSE_ERR;
				}
			} while (l_bytes != E_SSL_OK && l_bytes != E_SSL_ERROR);

			printf("done!\n");
			break;

		case SSL_SERVER_CLOSE:
		case SSL_SERVER_CLOSE_ERR:

			sslSoc_free(ps_sslCtx);

			close(srv_socdesc);
			puts("Socket closed");

			E_SERVER_FSM_RESULT retval =
					(i_state == SSL_SERVER_CLOSE_ERR) ? E_SERVER_FSM_ERROR : E_SERVER_FSM_DONE;

			i_state = SSL_SERVER_REINIT;

			return retval;
			break;

	} /* switch */

	/* server FSM would like to be re-entered again */
	return E_SERVER_FSM_AGAIN;
}