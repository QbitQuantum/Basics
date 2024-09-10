int main(int argc, char* argv[]){

	if (argc != 3){ //check usage
		printf("Two arguments required: [Hostname/IP] [DNS server IP]\n");
	}
	else{

		char *lookup = argv[1];
		char *dns = argv[2];

		printf("Lookup  : %s\n", lookup);

		/*
		START LOOKUP
		*/

		WSADATA wsaData;

		//Initialize WinSock; once per program run
		WORD wVersionRequested = MAKEWORD(2, 2);
		if (WSAStartup(wVersionRequested, &wsaData) != 0) {
			printf("WSAStartup error %d\n", WSAGetLastError());
			WSACleanup();
			return 0;
		}

		// open a UDP socket
		SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
		if (sock == INVALID_SOCKET)
		{
			printf("socket() generated error %d\n", WSAGetLastError());
			WSACleanup();
			return 0;
		}

		// bind the UDP socket to me
		struct sockaddr_in local;
		memset(&local, 0, sizeof(local));
		local.sin_family = AF_INET;
		local.sin_port = htons(0);
		local.sin_addr.s_addr = INADDR_ANY;
		if (bind(sock, (struct sockaddr*)&local, sizeof(local)) == SOCKET_ERROR){
			printf("bind() failed with error %d\n", WSAGetLastError());
			WSACleanup();
			return 0;
		}

		//set up where to send queries to
		struct sockaddr_in remote;
		memset(&remote, 0, sizeof(remote));
		remote.sin_family = AF_INET;
		remote.sin_addr.s_addr = inet_addr(dns); //server's IP
		remote.sin_port = htons(53); //DNS port on server
		int sendersize = sizeof(remote);
		int packet_size = strlen(lookup) + 2 + sizeof(FixedDNSheader) + sizeof(QueryHeader);
		char *packet = new char[packet_size];

		DWORD IP = inet_addr(lookup);
		if (IP == INADDR_NONE){ //hostname, do a forward lookup, type-A
			char *host = new char[strlen(lookup) + 1];
			for (int i = 0; i < strlen(lookup); i++){
				host[i] = lookup[i];
			}
			host[strlen(lookup)] = '\0';

			printf("Query   : %s, ", host);

			FixedDNSheader *dh = (FixedDNSheader *)packet;
			QueryHeader *qh = (QueryHeader*)(packet + packet_size - sizeof(QueryHeader));
			int txid = rand();
			dh->txid = htons(txid);
			dh->flags = htons(DNS_QUERY | DNS_RD | DNS_STDQUERY);
			dh->nQuestions = htons(1);
			dh->nAnswers = htons(0);
			dh->nAuthority = htons(0);
			dh->nAdditional = htons(0);
			qh->qType = htons(DNS_A);
			qh->qClass = htons(DNS_INET);

			printf("type 1, TXID 0x%x\n", txid);

			createRequest((char*)(dh + 1), host);

		}
		else{ //IP, do a reverse lookup, type-PTR
			char ip[35];
			int a, b, c, d;
			sscanf_s(lookup, "%d.%d.%d.%d", &a, &b, &c, &d);
			sprintf_s(ip, "%d.%d.%d.%d.in-addr.arpa", d, c, b, a);

			printf("Query   : %s, ", ip);

			FixedDNSheader *dh = (FixedDNSheader *)packet;
			QueryHeader *qh = (QueryHeader*)(packet + packet_size - sizeof(QueryHeader));
			int txid = rand();
			dh->txid = htons(txid);
			dh->flags = htons(DNS_QUERY | DNS_RD | DNS_STDQUERY);
			dh->nQuestions = htons(1);
			dh->nAnswers = htons(0);
			dh->nAuthority = htons(0);
			dh->nAdditional = htons(0);
			qh->qType = htons(DNS_PTR);
			qh->qClass = htons(DNS_INET);

			printf("type 12, TXID 0x%x\n", txid);

			createRequest((char*)(dh + 1), ip);

		}

		printf("Server  : %s\n", dns);
		printf("******************************\n");

		char *recvBuf = new char[4001];
		recvBuf[4000] = '\0';
		bool received = false;
		int bytes = 0;
		int k = 0;

		while (received == false){

			if (k == 3){
				break;
			}

			clock_t total_time = clock();

			printf("Attempt %d with %d bytes... ", k, packet_size);

			if (sendto(sock, packet, packet_size, 0, (struct sockaddr*)&remote, sizeof(remote)) == SOCKET_ERROR){
				printf("sendto() failed with error %d\n", WSAGetLastError());
				WSACleanup();
				return 0;
			}

			fd_set monitor;
			FD_ZERO(&monitor);
			FD_SET(sock, &monitor);
			struct timeval timer;
			timer.tv_sec = 10;
			timer.tv_usec = 0;

			if (select(sock, &monitor, NULL, NULL, &timer) > 0){ //wait for a response forever, only 1 packet
				struct sockaddr_in response;
				if ((bytes = recvfrom(sock, recvBuf, strlen(recvBuf), 0, (struct sockaddr*)&response, &sendersize)) == SOCKET_ERROR){
					printf("recvfrom() failed with error %d\n", WSAGetLastError());
					WSACleanup();
					return 0;
				}
				printf("response in %d ms with %d bytes\n", (clock() - total_time), bytes);
				if (memcmp(&response.sin_addr, &remote.sin_addr, sizeof(DWORD)) != 0 || response.sin_port != remote.sin_port){
					printf("revfrom() bogus reply, quitting\n");
					WSACleanup();
					return 0;
				}
				int mismatch = parseResponse(recvBuf, bytes, packet, packet_size);
				if (mismatch == -1){
					printf("  TXID does not match\n");
					WSACleanup();
					return 0;
				}
				received = true;
			}
			else{
				k++;
				printf("timeout in %d ms\n", clock() - total_time);
			}

		}
		//print summary
		WSACleanup();
	}
	return 0;
}