int main(int argc, char **argv)  {
	int optval = 1;
	int print_help = 0;
	int send_packets = 5;
	int fastmode = 0;
	int c;
	struct sockaddr_in si_me;
	struct mt_packet packet;
	int i;

	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);

	while (1) {
		c = getopt(argc, argv, "fs:c:hv?");

		if (c == -1) {
			break;
		}

		switch (c) {
			case 'f':
				fastmode = 1;
				break;

			case 's':
				ping_size = atoi(optarg) - 18;
				break;

			case 'v':
				print_version();
				exit(0);
				break;

			case 'c':
				send_packets = atoi(optarg);
				break;

			case 'h':
			case '?':
				print_help = 1;
				break;

		}
	}

	/* We don't want people to use this for the wrong reasons */
	if (fastmode && (send_packets <= 0 || send_packets > 100)) {
		fprintf(stderr, _("Number of packets to send must be more than 0 and up to 100 in fast mode.\n"));
		return 1;
	}

	if (argc - optind < 1 || print_help) {
		print_version();
		fprintf(stderr, _("Usage: %s <MAC> [-h] [-f] [-c <count>] [-s <packet size>]\n"), argv[0]);

		if (print_help) {
			fprintf(stderr, _("\nParameters:\n"
			"  MAC       MAC-Address of the RouterOS/mactelnetd device.\n"
			"  -f        Fast mode, do not wait before sending next ping request.\n"
			"  -s        Specify size of ping packet.\n"
			"  -c        Number of packets to send. (0 = unlimited)\n"
			"  -h        This help.\n"
			"\n"));
		}
		return 1;
	}

	if (ping_size > ETH_FRAME_LEN - 42) {
		fprintf(stderr, _("Packet size must be between 18 and %d\n"), ETH_FRAME_LEN - 42 + 18);
		exit(1);
	}

	/* Mikrotik RouterOS does not answer unless the packet has the correct recipient mac-address in
	 * the ethernet frame. Unlike real MacTelnet connections where the OS is ok with it being a
	 * broadcast mac address.
	 */
	if (geteuid() != 0) {
		fprintf(stderr, _("You need to have root privileges to use %s.\n"), argv[0]);
		return 1;
	}

	/* Get mac-address from string, or check for hostname via mndp */
	if (!query_mndp_or_mac(argv[optind], dstmac, 1)) {
		/* No valid mac address found, abort */
		return 1;
	}

	sockfd = net_init_raw_socket();

	insockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (insockfd < 0) {
		perror("insockfd");
		return 1;
	}

	/* Set initialize address/port */
	memset((char *) &si_me, 0, sizeof(si_me));
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(MT_MACTELNET_PORT);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);

	setsockopt(insockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof (optval));

	/* Bind to specified address/port */
	if (bind(insockfd, (struct sockaddr *)&si_me, sizeof(si_me))==-1) {
		fprintf(stderr, _("Error binding to %s:%d\n"), inet_ntoa(si_me.sin_addr), MT_MNDP_PORT);
		return 1;
	}

	/* Listen address*/
	inet_pton(AF_INET, (char *)"0.0.0.0", &sourceip);

	/* Set up global info about the connection */
	inet_pton(AF_INET, (char *)"255.255.255.255", &destip);

	srand(time(NULL));

	/* Enumerate available interfaces */
	net_get_interfaces(&interfaces);

	if (ping_size < sizeof(struct timeval)) {
		ping_size = sizeof(struct timeval);
	}

	signal(SIGINT, display_results);

	for (i = 0; i < send_packets || send_packets <= 0; ++i) {
		fd_set read_fds;
		static struct timeval lasttimestamp;
		int reads, result;
		struct timeval timeout;
		int ii;
		int sent = 0;
		int waitforpacket;
		struct timeval timestamp;
		unsigned char pingdata[MT_PACKET_LEN];
		struct net_interface *interface;

		gettimeofday(&timestamp, NULL);
		memcpy(pingdata, &timestamp, sizeof(timestamp));
		for (ii = sizeof(timestamp); ii < ping_size; ++ii) {
			pingdata[ii] = rand() % 256;
		}

		LL_FOREACH(interfaces, interface) {
			if (!interface->has_mac) {
				continue;
			}

			init_pingpacket(&packet, interface->mac_addr, dstmac);
			add_packetdata(&packet, pingdata, ping_size);
			result = net_send_udp(sockfd, interface, interface->mac_addr, dstmac, &sourceip, MT_MACTELNET_PORT, &destip, MT_MACTELNET_PORT, packet.data, packet.size);

			if (result > 0) {
				sent++;
			}

		}
		if (sent == 0) {
			fprintf(stderr, _("Error sending packet.\n"));
			continue;
		}
		ping_sent++;

		FD_ZERO(&read_fds);
		FD_SET(insockfd, &read_fds);

		timeout.tv_sec = 1;
		timeout.tv_usec = 0;

		waitforpacket = 1;

		while (waitforpacket) {
			/* Wait for data or timeout */
			reads = select(insockfd+1, &read_fds, NULL, NULL, &timeout);
			if (reads <= 0) {
				waitforpacket = 0;
				fprintf(stderr, _("%s ping timeout\n"), ether_ntoa((struct ether_addr *)&dstmac));
				break;
			}

			unsigned char buff[MT_PACKET_LEN];
			struct sockaddr_in saddress;
			unsigned int slen = sizeof(saddress);
			struct mt_mactelnet_hdr pkthdr;

			result = recvfrom(insockfd, buff, sizeof(buff), 0, (struct sockaddr *)&saddress, &slen);
			/* Check for exact size */
			if (result != 18 + ping_size) {
				continue;
			}
			parse_packet(buff, &pkthdr);

			/* TODO: Check that we are the receiving host */
			if (pkthdr.ptype != MT_PTYPE_PONG) {
				/* Wait for the correct packet */
				continue;
			}
			
			struct timeval pongtimestamp;
			struct timeval nowtimestamp;

			waitforpacket = 0;
			gettimeofday(&nowtimestamp, NULL);

			memcpy(&pongtimestamp, pkthdr.data - 4, sizeof(pongtimestamp));
			if (memcmp(pkthdr.data - 4, pingdata, ping_size) == 0) {
				float diff = toddiff(&nowtimestamp, &pongtimestamp) / 1000.0f;

				if (diff < min_ms) {
					min_ms = diff;
				}

				if (diff > max_ms) {
					max_ms = diff;
				}

				avg_ms += diff;

				printf(_("%s %d byte, ping time %.2f ms%s\n"), ether_ntoa((struct ether_addr *)&(pkthdr.srcaddr)), result, diff, (char *)(memcmp(&pongtimestamp,&lasttimestamp,sizeof(lasttimestamp)) == 0 ? " DUP" : ""));
			} else {
				printf(_("%s Reply of %d bytes of unequal data\n"), ether_ntoa((struct ether_addr *)&(pkthdr.srcaddr)), result);
			}
			pong_received++;
			memcpy(&lasttimestamp, &pongtimestamp, sizeof(pongtimestamp));
			if (!fastmode) {
				sleep(1);
			}
		}
	}

	/* Display statistics and exit */
	display_results();

	return 0;
}