/*
 * This starts a minimal TLS server that only does a
 * handshake and then closes the connection.  This is
 * strictly used to test TLS session negotiation
 * behavior with EST.
 */
static void us1060c_start_tls_server (char *cipherstring)
{
    BIO *conn;
    BIO *listener;
    BIO *berr;
    char h_p[25];
    SSL *ssl;
    SSL_CTX *ssl_ctx = NULL;
    int nid, rv;
    EC_KEY *ecdh = NULL;

    berr = BIO_new_fp(stderr, BIO_NOCLOSE);

    ssl_ctx = SSL_CTX_new(SSLv23_server_method());
    if (!ssl_ctx) {
	printf("Failed to create SSL context\n");
	ERR_print_errors(berr);
	return;
    }

    SSL_CTX_set_mode(ssl_ctx, SSL_MODE_AUTO_RETRY);

    if (SSL_CTX_use_certificate_chain_file(ssl_ctx, US1060C_RSA_CERT) != 1) {
	printf("Failed to load server certificate\n");
	ERR_print_errors(berr);
	return;
    }
    if (SSL_CTX_use_PrivateKey_file(ssl_ctx, US1060C_RSA_KEY, SSL_FILETYPE_PEM) != 1) {
	printf("Failed to load server private key\n");
	ERR_print_errors(berr);
	return;
    }

    SSL_CTX_set_options(ssl_ctx, SSL_OP_NO_SSLv2 |
	                         SSL_OP_NO_SSLv3 |
				 SSL_OP_NO_TLSv1 |
                                 SSL_OP_SINGLE_ECDH_USE | 
				 SSL_OP_SINGLE_DH_USE |
			         SSL_OP_NO_TICKET);

    nid = OBJ_sn2nid("prime256v1");
    ecdh = EC_KEY_new_by_curve_name(nid);
    if (ecdh == NULL) {
	printf("Failed to retreive ECDH curve\n");
	ERR_print_errors(berr);
	return;
    }
    SSL_CTX_set_tmp_ecdh(ssl_ctx, ecdh);
    EC_KEY_free(ecdh);

    if (SSL_CTX_set_cipher_list(ssl_ctx, cipherstring) != 1) {
	printf("Failed to set server cipher list\n");
	ERR_print_errors(berr);
	return;
    }
    SSL_CTX_set_srp_username_callback(ssl_ctx, us1060_srp_cb);

    sprintf(h_p, "%s:%d", US1060C_SERVER_IP, US1060C_TLS_PORT);
    listener = BIO_new_accept(h_p);
    if (listener == NULL) {
	printf("IP connection failed\n");
	return;
    }
    BIO_set_bind_mode(listener, BIO_BIND_REUSEADDR);

    /*
     * The first call to do_accept binds the socket
     */
    if (BIO_do_accept(listener) <= 0) {
	printf("TCP bind failed\n");
	BIO_free_all(listener);
	return;
    }

    /*
     * The second call to do_accept waits for a new
     * connection request on the listener.
     * Note that we are in blocking mode for this socket
     */
    if (BIO_do_accept(listener) <= 0) {
	printf("TCP accept failed\n");
	BIO_free_all(listener);
	return;
    }
    conn = BIO_pop(listener);

    ssl = SSL_new(ssl_ctx);
    SSL_set_bio(ssl, conn, conn);
    /*
     * Now that we have everything ready, let's start waiting for
     * a client to contact us.  Normally we might using a pthread
     * or some other construct to avoid blocking on the main 
     * thread while waiting for an incoming connection.  This
     * code is simply a contrived example, we will wait on the
     * main thread for an incoming connection.
     */
    rv = SSL_accept(ssl);
    if (rv <= 0) {
	printf("\nFailed to complete TLS handshake %d\n", rv);
	ERR_print_errors(berr);
    }
#ifdef WIN32
    SLEEP(2);
#endif 
    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ssl_ctx);
    BIO_free(berr);
    (void)BIO_reset(listener);
    BIO_free_all(listener);
#ifndef WIN32
    pthread_exit(0);
#else
    ExitThread(0); 
#endif
}