int crashreport_send(char *fname)
{
	char buf[1024];
	char header[512], footer[512];
	char delimiter[41];
	int filesize;
	int n;
	FILE *fd;
	SSL_CTX *ctx_client;
	BIO *socket = NULL;
	
	filesize = getfilesize(fname);
	if (filesize < 0)
		return 0;
	
	for (n = 0; n < sizeof(delimiter); n++)
		delimiter[n] = getrandom8()%26 + 'a';
	delimiter[sizeof(delimiter)-1] = '\0';
	
	snprintf(header, sizeof(header), "--%s\r\n"
	                           "Content-Disposition: form-data; name=\"upload\"; filename=\"crash.txt\"\r\n"
	                           "Content-Type: text/plain\r\n"
	                           "\r\n",
	                           delimiter);
	snprintf(footer, sizeof(footer), "\r\n--%s--\r\n", delimiter);

	ctx_client = crashreport_init_ssl();
	if (!ctx_client)
	{
		printf("ERROR: SSL initalization failure (I)\n");
		return 0;
	}
	
	socket = BIO_new_ssl_connect(ctx_client);
	if (!socket)
	{
		printf("ERROR: SSL initalization failure (II)\n");
		return 0;
	}
	
	BIO_set_conn_hostname(socket, CRASH_REPORT_HOST ":443");

	if (BIO_do_connect(socket) != 1)
	{
		printf("ERROR: Could not connect to %s\n", CRASH_REPORT_HOST);
		return 0;
	}
	
	if (BIO_do_handshake(socket) != 1)
	{
		printf("ERROR: Could not connect to %s (SSL handshake failed)\n", CRASH_REPORT_HOST);
		return 0;
	}
	
	snprintf(buf, sizeof(buf), "POST /crash.php HTTP/1.1\r\n"
	                    "User-Agent: UnrealIRCd %s\r\n"
	                    "Host: %s\r\n"
	                    "Accept: */*\r\n"
	                    "Content-Length: %d\r\n"
	                    "Expect: 100-continue\r\n"
	                    "Content-Type: multipart/form-data; boundary=%s\r\n"
	                    "\r\n",
	                    VERSIONONLY,
	                    CRASH_REPORT_HOST,
	                    (int)(filesize+strlen(header)+strlen(footer)),
	                    delimiter);
	
	BIO_puts(socket, buf);
	
	memset(buf, 0, sizeof(buf));
	n = BIO_read(socket, buf, 255);
	if ((n < 0) || strncmp(buf, "HTTP/1.1 100", 12))
	{
		printf("Error transmitting bug report (stage II, n=%d)\n", n);
		return 0;
	}
	
	fd = fopen(fname, "rb");
	if (!fd)
		return 0;

	BIO_puts(socket, header);
	
	while ((fgets(buf, sizeof(buf), fd)))
	{
		BIO_puts(socket, buf);
	}
	fclose(fd);

	BIO_puts(socket, footer);

	do { } while(BIO_should_retry(socket)); /* make sure we are really finished (you never know with SSL) */
	
	BIO_free_all(socket);
	
	SSL_CTX_free(ctx_client);
	
	return 1;
}