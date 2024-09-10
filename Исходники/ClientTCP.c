int main(int argc, char *argv[])
{
	int sockfd, numbytes;
	char buf[MAX_PACKET_LEN];
	struct addrinfo hints, *servinfo, *p;
	int status;
	char s[INET6_ADDRSTRLEN];

	// Command Line arguments will fill these out
	char* hostname;
	char* port;
	unsigned char operation;
	char* message_in;
	
	if (argc != 5) 
	{
		fprintf(stderr, "Usage Error: Params\n");
		exit(1);
	}

	// Get the params from command line
	hostname = argv[1];
	port = argv[2];
	operation = (unsigned char)atoi(argv[3]);
	message_in = argv[4];

	if (DEBUG) {
		printf("argv[1] or hostname: %s\n", argv[1]);
		printf("argv[2] or port: %s\n", argv[2]);
		printf("argv[3] or operation: %s\n", argv[3]);
		printf("argv[4] or message: %s\n", argv[4]);
	}

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((status = getaddrinfo(hostname, port, &hints, &servinfo)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 1;
	}

	// Loop through all the results and connect to the first we can
	for (p = servinfo; p != NULL; p = p->ai_next)
	{
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
		{
			perror("Socket error");
			continue;
		}

		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("Connect error");
			continue;
		}

		break;
	}

	if (p == NULL)
	{
		fprintf(stderr, "Failed to connect!\n");
		return 2;
	}

	if (DEBUG) {
		inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);

		printf("Connected to: %s\n", s);
	}

	freeaddrinfo(servinfo); 	// All done with this structure

	// Create the outgoing packet and fill it in
	tx_packet packet_out;

	strcpy(packet_out.message, message_in);
	packet_out.TML = htons(sizeof(packet_out.TML) + sizeof(packet_out.RID)
		+ sizeof(packet_out.operation) + strlen(packet_out.message));
	packet_out.operation = operation;
	
	// Create a random RID, between 0 and 60,000
	// Bug: If you send multiple packets within 1 second of each other they will
	// have the same RID. Caused by time() only updating every second.  
	srand(time(NULL));
	unsigned short random = rand() % 600001; 
	packet_out.RID = htons(random);

	if (DEBUG) {
		printf("packet_out.TML: %d\n", ntohs(packet_out.TML));
		printf("packet_out.RID: %d\n", ntohs(packet_out.RID));
		printf("packet_out.TML: %d\n", packet_out.operation);
		printf("packet_out.TML: %s\n", packet_out.message);
	}

	if (send(sockfd, (char *)&packet_out, ntohs(packet_out.TML), 0) == -1)
	{
		perror("Send Error");
	}

	// Depending on the operation we requested will decide what kind of packet we will recieve
	
	// vLength was requested
	if (operation == V_LENGTH)
	{
	
		// Prepare the packet
		int numbytes_rec_vLength;
		rx_vLength packet_in_vLength;
		
		if ((numbytes_rec_vLength = recv(sockfd, 
			(char *)&packet_in_vLength, MAX_PACKET_LEN, 0)) == -1) 
		{
			perror("recv error");
			exit(1);
		}

		if(DEBUG) {
			printf("Packet Recieved!\n");
			printf("packet_in_vLength.TML: %d\n", ntohs(packet_in_vLength.TML));
			printf("packet_in_vLength.RID: %d\n", ntohs(packet_in_vLength.RID));
			printf("packet_in_vLength.vLength: %d\n", ntohs(packet_in_vLength.vLength));
		}
	}

	// disVowel was requested
	if (operation == DISEMVOWEL)
	{
	
		// Prepare the packet
		int numbytes_rec_disVowel;
		rx_disVowel packet_in_disVowel;
		
		if ((numbytes_rec_disVowel = recv(sockfd, 
			(char *)&packet_in_disVowel, MAX_PACKET_LEN, 0)) == -1) 
		{
			perror("recv error");
			exit(1);
		}

		// Add the null terminator, just in case. -4 becuase of header
		packet_in_disVowel.message[numbytes_rec_disVowel - 4] = '\0';

		if(DEBUG) {
			printf("Packet Recieved!\n");
			printf("packet_in_disVowel.TML: %d\n", ntohs(packet_in_disVowel.TML));
			printf("packet_in_disVowel.RID: %d\n", ntohs(packet_in_disVowel.RID));
			printf("packet_in_disVowel.message: %s\n", packet_in_disVowel.message);
		}
	}

	close(sockfd);

	return 0;
}