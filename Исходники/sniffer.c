/*
 * Initialize the server extension
 */
DWORD __declspec(dllexport) InitServerExtension(Remote *remote)
{
	DWORD index;

	dprintf("[SERVER] Registering command handlers...");
	for (index = 0; customCommands[index].method; index++) {
		dprintf("Registering command index %d", index);
		dprintf("  Command: %s", customCommands[index].method);
		dprintf(" Register: 0x%.8x", command_register);
		command_register(&customCommands[index]);
	}

	dprintf("[SERVER] Memory reset of open_captures...");
	memset(open_captures, 0, sizeof(open_captures));

#ifdef _WIN32
	// initialize structures for the packet sniffer sdk
	hMgr = NULL;
	hErr = 0;

	dprintf("[SERVER] Memory reset of include/exclude port lists...");
	// wipe the include/exclude ports empty
	memset(sniffer_includeports, 0, sizeof(sniffer_includeports));
	memset(sniffer_excludeports, 0, sizeof(sniffer_excludeports));
	sniffer_includeports[0] = -1;
	sniffer_excludeports[0] = -1;
#endif

	dprintf("[SERVER] Getting the peer name of our socket...");
	// get the address/port of the connected control socket
	peername4 = NULL;
	peername6 = NULL;
	peername_len = sizeof(peername);
	getpeername(remote->fd, &peername, &peername_len);
	if(peername.sa_family == PF_INET)  peername4 = (struct sockaddr_in *)&peername;

	dprintf("[SERVER] Getting the IPv6 peer name of our socket...");
	if(peername.sa_family == PF_INET6) peername6 = (struct sockaddr_in6 *)&peername;

	dprintf("[SERVER] Creating a lock...");
	snifferm = lock_create();

#ifdef _WIN32
	return hErr;
#else
	if(peername4 || peername6) {
		int port;
		char buf[256];		// future proof :-)

		memset(buf, 0, sizeof(buf));

		if(peername4) {
			inet_ntop(AF_INET, &peername4->sin_addr, buf, sizeof(buf)-1);
			port = ntohs(peername4->sin_port);
		} else {
			inet_ntop(AF_INET6, &peername6->sin6_addr, buf, sizeof(buf)-1);
			port = ntohs(peername6->sin6_port);
		}

		asprintf(&packet_filter, "not (ip%s host %s and tcp port %d)", peername4 ? "" : "6", buf, port);
		dprintf("so our filter is '%s'", packet_filter);
	} else {
		dprintf("hold on to your seats. no filter applied :~(");
	}

	return ERROR_SUCCESS;
#endif

}