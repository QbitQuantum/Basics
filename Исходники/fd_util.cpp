std::string GetLocalIP(int sock) {
	union {
		struct sockaddr sa;
		struct sockaddr_in ipv4;
		struct sockaddr_in6 ipv6;
	} server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	socklen_t len = sizeof(server_addr);
	if (getsockname(sock, (struct sockaddr *)&server_addr, &len) == 0) {
		char temp[64]{};

		// We clear the port below for WSAAddressToStringA.
		void *addr;
		if (server_addr.sa.sa_family == AF_INET6) {
			server_addr.ipv6.sin6_port = 0;
			addr = &server_addr.ipv6.sin6_addr;
		} else {
			server_addr.ipv4.sin_port = 0;
			addr = &server_addr.ipv4.sin_addr;
		}
#ifdef _WIN32
		DWORD len = (DWORD)sizeof(temp);
		// Windows XP doesn't support inet_ntop.
		if (WSAAddressToStringA((struct sockaddr *)&server_addr, sizeof(server_addr), nullptr, temp, &len) == 0) {
			return temp;
		}
#else
		const char *result = inet_ntop(server_addr.sa.sa_family, addr, temp, sizeof(temp));
		if (result) {
			return result;
		}
#endif
	}
	return "";
}