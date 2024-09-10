/* The program expects at most four arguments: host in IP format, port
 * number to connect to, proxy in IP format and proxy port number.
 * If last two are specified, host can be in any format proxy will
 * understand (since this is an example for SSL programming, host name
 * resolving code is left out).
 *
 * Default values are "127.0.0.1", 443. If any proxy parameter is
 * omitted, the program will connect directly to the host.
 */
int main(int argc, char *argv[])
{
	char buffer[4096]; /* This should be dynamically allocated */
	const char *request = "GET / HTTP/1.0\r\n\r\n";
	BOOL is_ok = FALSE;
	X509 *server_cert;
	SSL_CTX *ctx;
	BIO *bio_err;
	SSL *ssl;

	if (Init())
	{
		/* Basic intialization. Next few steps (up to SSL_new()) need
		 * to be done only once per AmiSSL opener.
		 */
		SSLeay_add_ssl_algorithms();
		SSL_load_error_strings();

		/* Note: BIO writing routines are prepared for NULL BIO handle */
		if((bio_err = BIO_new(BIO_s_file())) != NULL)
			BIO_set_fp_amiga(bio_err, GetStdErr(), BIO_NOCLOSE | BIO_FP_TEXT);

		/* Get a new SSL context */
		if((ctx = SSL_CTX_new(SSLv23_client_method())) != NULL)
		{
			/* Basic certificate handling. OpenSSL documentation has more
			 * information on this.
			 */
			SSL_CTX_set_default_verify_paths(ctx);
			SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT,
			                   NULL);

			/* The following needs to be done once per socket */
			if((ssl = SSL_new(ctx)) != NULL)
			{
				int sock;

				/* Connect to the HTTPS server, directly or through a proxy */
				if (argc > 4)
					sock = ConnectToServer(argv[1], atol(argv[2]), argv[3],
					                       atol(argv[4]));
				else
					sock = ConnectToServer(argv[1] ? argv[1] : (char *)"127.0.0.1",
					                       argc > 2 ? atol(argv[2]) : 443,
					                       NULL, 0);

				/* Check if connection was established */
				if (sock >= 0)
				{
					int ssl_err = 0;

					/* Associate the socket with the ssl structure */
					SSL_set_fd(ssl, sock);

					/* Perform SSL handshake */
					if((ssl_err = SSL_connect(ssl)) >= 0)
					{
						Printf("SSL connection using %s\n", SSL_get_cipher(ssl));

						/* Certificate checking. This example is *very* basic */
						if((server_cert = SSL_get_peer_certificate(ssl)))
						{
							char *str;

							Printf("Server certificate:\n");

							if((str = X509_NAME_oneline(X509_get_subject_name(server_cert), 0, 0)))
							{
								Printf("\tSubject: %s\n", str);
								OPENSSL_free(str);
							}
							else
								FPrintf(GetStdErr(), "Warning: couldn't read subject name in certificate!\n");

							if((str = X509_NAME_oneline(X509_get_issuer_name(server_cert),
							                            0, 0)) != NULL)
							{
								Printf("\tIssuer: %s\n", str);
								OPENSSL_free(str);
							}
							else
								FPrintf(GetStdErr(), "Warning: couldn't read issuer name in certificate!\n");

							X509_free(server_cert);

							/* Send a HTTP request. Again, this is just
							 * a very basic example.
							 */
							if ((ssl_err = SSL_write(ssl, request, strlen(request)))
							    > 0)
							{
								/* Dump everything to output */
								while ((ssl_err = SSL_read(ssl, buffer,
								                           sizeof(buffer) - 1))
								       > 0)
									FWrite(Output(), buffer, ssl_err, 1);

								FFlush(Output());

								/* This is not entirely true, check
								 * the SSL_read documentation
								 */
								is_ok = ssl_err == 0;
							}
							else
								FPrintf(GetStdErr(), "Couldn't write request!\n");
						}
						else
							FPrintf(GetStdErr(), "Couldn't get server certificate!\n");
					}
					else
						FPrintf(GetStdErr(), "Couldn't establish SSL connection!\n");

					/* If there were errors, print them */
					if (ssl_err < 0)
						ERR_print_errors(bio_err);

					/* Send SSL close notification and close the socket */
					SSL_shutdown(ssl);
					CloseSocket(sock);
				}
				else
					FPrintf(GetStdErr(), "Couldn't connect to host!\n");

        
			  FPrintf(GetStdErr(), "before SSL_free()\n");
				SSL_free(ssl);
			}
			else
				FPrintf(GetStdErr(), "Couldn't create new SSL handle!\n");

			FPrintf(GetStdErr(), "before SSL_CTX_free()\n");
			SSL_CTX_free(ctx);
		}
		else
			FPrintf(GetStdErr(), "Couldn't create new context!\n");

	  FPrintf(GetStdErr(), "before Cleanup()\n");
		Cleanup();
	}

	FPrintf(GetStdErr(), "before end of main()\n");
	return(is_ok ? RETURN_OK : RETURN_ERROR);
}