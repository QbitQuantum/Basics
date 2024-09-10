int main(int argc, char **argv)
{
	int op, ret;

	hints.ai_port_space = RDMA_PS_UDP;
	while ((op = getopt(argc, argv, "s:b:c:C:S:t:p:P:f:")) != -1) {
		switch (op) {
		case 's':
			dst_addr = optarg;
			break;
		case 'b':
			src_addr = optarg;
			break;
		case 'c':
			connections = atoi(optarg);
			break;
		case 'C':
			message_count = atoi(optarg);
			break;
		case 'S':
			message_size = atoi(optarg);
			break;
		case 't':
			set_tos = 1;
			tos = (uint8_t) strtoul(optarg, NULL, 0);
			break;
		case 'p': /* for backwards compatibility - use -P */
			hints.ai_port_space = strtol(optarg, NULL, 0);
			break;
		case 'f':
			if (!strncasecmp("ip", optarg, 2)) {
				hints.ai_flags = RAI_NUMERICHOST;
			} else if (!strncasecmp("gid", optarg, 3)) {
				hints.ai_flags = RAI_NUMERICHOST | RAI_FAMILY;
				hints.ai_family = AF_IB;
			} else if (strncasecmp("name", optarg, 4)) {
				fprintf(stderr, "Warning: unknown address format\n");
			}
			break;
		case 'P':
			if (!strncasecmp("ipoib", optarg, 5)) {
				hints.ai_port_space = RDMA_PS_IPOIB;
			} else if (strncasecmp("udp", optarg, 3)) {
				fprintf(stderr, "Warning: unknown port space format\n");
			}
			break;
		default:
			printf("usage: %s\n", argv[0]);
			printf("\t[-s server_address]\n");
			printf("\t[-b bind_address]\n");
			printf("\t[-f address_format]\n");
			printf("\t    name, ip, ipv6, or gid\n");
			printf("\t[-P port_space]\n");
			printf("\t    udp or ipoib\n");
			printf("\t[-c connections]\n");
			printf("\t[-C message_count]\n");
			printf("\t[-S message_size]\n");
			printf("\t[-t type_of_service]\n");
			printf("\t[-p port_space - %#x for UDP (default), "
			       "%#x for IPOIB]\n", RDMA_PS_UDP, RDMA_PS_IPOIB);
			exit(1);
		}
	}

	test.connects_left = connections;

	test.channel = rdma_create_event_channel();
	if (!test.channel) {
		perror("failed to create event channel");
		exit(1);
	}

	if (alloc_nodes())
		exit(1);

	if (dst_addr) {
		ret = run_client();
	} else {
		hints.ai_flags |= RAI_PASSIVE;
		ret = run_server();
	}

	printf("test complete\n");
	destroy_nodes();
	rdma_destroy_event_channel(test.channel);
	if (test.rai)
		rdma_freeaddrinfo(test.rai);

	printf("return status %d\n", ret);
	return ret;
}