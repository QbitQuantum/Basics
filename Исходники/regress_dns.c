static void
dns_server(void)
{
	int sock;
	struct sockaddr_in my_addr;
	struct evdns_server_port *port;
	struct in_addr resolve_addr;

	dns_ok = 1;
	fprintf(stdout, "DNS server support: ");

	/* Add ourself as the only nameserver, and make sure we really are
	 * the only nameserver. */
	evdns_nameserver_ip_add("127.0.0.1:35353");
	if (evdns_count_nameservers() != 1) {
		fprintf(stdout, "Couldn't set up.\n");
		exit(1);
	}

	/* Now configure a nameserver port. */
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == -1) {
		perror("socket");
		exit(1);
	}
#ifdef WIN32
	{
		u_long nonblocking = 1;
		ioctlsocket(sock, FIONBIO, &nonblocking);
	}
#else
	fcntl(sock, F_SETFL, O_NONBLOCK);
#endif
	memset(&my_addr, 0, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(35353);
	my_addr.sin_addr.s_addr = htonl(0x7f000001UL);
	if (bind(sock, (struct sockaddr*)&my_addr, sizeof(my_addr)) < 0) {
		perror("bind");
		exit (1);
	}
	port = evdns_add_server_port(sock, 0, dns_server_request_cb, NULL);

	/* Send two queries. */
	evdns_resolve_ipv4("zz.example.com", DNS_QUERY_NO_SEARCH,
					   dns_server_gethostbyname_cb, NULL);
	evdns_resolve_ipv6("zz.example.com", DNS_QUERY_NO_SEARCH,
					   dns_server_gethostbyname_cb, NULL);
	resolve_addr.s_addr = htonl(0xc0a80b0bUL); /* 192.168.11.11 */
	evdns_resolve_reverse(&resolve_addr, 0,
						  dns_server_gethostbyname_cb, NULL);

	event_dispatch();

	if (dns_ok) {
		fprintf(stdout, "OK\n");
	} else {
		fprintf(stdout, "FAILED\n");
		exit(1);
	}

	evdns_close_server_port(port);
	evdns_shutdown(0); /* remove ourself as nameserver. */
#ifdef WIN32
	closesocket(sock);
#else
	close(sock);
#endif
}