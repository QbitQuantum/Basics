int EthernetClient::connect(const char * host, uint16_t port)
{
	DNSClient dns; // Look up the host first
	IPAddress remote_addr;

	if (sockindex < MAX_SOCK_NUM) {
		if (Ethernet.socketStatus(sockindex) != SnSR::CLOSED) {
			Ethernet.socketDisconnect(sockindex); // TODO: should we call stop()?
		}
		sockindex = MAX_SOCK_NUM;
	}
	dns.begin(Ethernet.dnsServerIP());
	if (!dns.getHostByName(host, remote_addr)) return 0; // TODO: use _timeout
	return connect(remote_addr, port);
}