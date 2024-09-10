std::string get_domain_ip(const std::string& domain) {
	AUTO_LOG_FUNCTION;
	struct addrinfo *result = nullptr;
	struct addrinfo *ptr = nullptr;
	struct addrinfo hints;

	struct sockaddr_in  *sockaddr_ipv4;
	//    struct sockaddr_in6 *sockaddr_ipv6;
	LPSOCKADDR sockaddr_ip;

	char ipstringbuffer[46];
	DWORD ipbufferlength = 46;

	//--------------------------------
	// Setup the hints address info structure
	// which is passed to the getaddrinfo() function
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	std::string ip;

	do {

		//--------------------------------
		// Call getaddrinfo(). If the call succeeds,
		// the result variable will hold a linked list
		// of addrinfo structures containing response
		// information
		DWORD dwRetval = getaddrinfo(domain.c_str(), "0", &hints, &result);
		if (dwRetval != 0) {
			JLOGA("getaddrinfo failed with error: %d\n", dwRetval);
			break;
		}

		JLOGA("getaddrinfo returned success\n");

		// Retrieve each address and print out the hex bytes
		int i = 0;
		int iRetval = 0;
		bool ok = false;
		for (ptr = result; ptr != nullptr; ptr = ptr->ai_next) {
			JLOGA("getaddrinfo response %d\n", i++);
			JLOGA("\tFlags: 0x%x\n", ptr->ai_flags);
			JLOGA("\tFamily: ");
			switch (ptr->ai_family) {
			case AF_UNSPEC:
				JLOGA("Unspecified\n");
				break;
			case AF_INET:
				JLOGA("AF_INET (IPv4)\n");
				sockaddr_ipv4 = (struct sockaddr_in *) ptr->ai_addr;
				ip = inet_ntoa(sockaddr_ipv4->sin_addr);
				JLOGA("\tIPv4 address %s\n", ip.c_str());
				ok = true;
				break;
			case AF_INET6:
				JLOGA("AF_INET6 (IPv6)\n");
				// the InetNtop function is available on Windows Vista and later
				// sockaddr_ipv6 = (struct sockaddr_in6 *) ptr->ai_addr;
				// printf("\tIPv6 address %s\n",
				//    InetNtop(AF_INET6, &sockaddr_ipv6->sin6_addr, ipstringbuffer, 46) );

				// We use WSAAddressToString since it is supported on Windows XP and later
				sockaddr_ip = (LPSOCKADDR)ptr->ai_addr;
				// The buffer length is changed by each call to WSAAddresstoString
				// So we need to set it for each iteration through the loop for safety
				ipbufferlength = 46;
				iRetval = WSAAddressToStringA(sockaddr_ip, (DWORD)ptr->ai_addrlen, nullptr,
											  ipstringbuffer, &ipbufferlength);
				if (iRetval)
					JLOGA("WSAAddressToString failed with %u\n", WSAGetLastError());
				else
					JLOGA("\tIPv6 address %s\n", ipstringbuffer);
				break;
			case AF_NETBIOS:
				JLOGA("AF_NETBIOS (NetBIOS)\n");
				break;
			default:
				JLOGA("Other %ld\n", ptr->ai_family);
				break;
			}
			JLOGA("\tSocket type: ");
			switch (ptr->ai_socktype) {
			case 0:
				JLOGA("Unspecified\n");
				break;
			case SOCK_STREAM:
				JLOGA("SOCK_STREAM (stream)\n");
				break;
			case SOCK_DGRAM:
				JLOGA("SOCK_DGRAM (datagram) \n");
				break;
			case SOCK_RAW:
				JLOGA("SOCK_RAW (raw) \n");
				break;
			case SOCK_RDM:
				JLOGA("SOCK_RDM (reliable message datagram)\n");
				break;
			case SOCK_SEQPACKET:
				JLOGA("SOCK_SEQPACKET (pseudo-stream packet)\n");
				break;
			default:
				JLOGA("Other %ld\n", ptr->ai_socktype);
				break;
			}
			JLOGA("\tProtocol: ");
			switch (ptr->ai_protocol) {
			case 0:
				JLOGA("Unspecified\n");
				break;
			case IPPROTO_TCP:
				JLOGA("IPPROTO_TCP (TCP)\n");
				break;
			case IPPROTO_UDP:
				JLOGA("IPPROTO_UDP (UDP) \n");
				break;
			default:
				JLOGA("Other %ld\n", ptr->ai_protocol);
				break;
			}
			JLOGA("\tLength of this sockaddr: %d\n", ptr->ai_addrlen);
			JLOGA("\tCanonical name: %s\n", ptr->ai_canonname);

			if (ok) {
				break;
			}
		}

		freeaddrinfo(result);

		if (ok) {
			return ip;
		}
	} while (false);

	return "";
}