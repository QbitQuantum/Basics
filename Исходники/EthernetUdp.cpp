int EthernetUDP::beginPacket(const char *host, uint16_t port)
{
	// Look up the host first
	int ret = 0;
	DNSClient dns;
	IPAddress remote_addr;

	dns.begin(Ethernet.dnsServerIP());
	ret = dns.getHostByName(host, remote_addr);
	if (ret == 1)
		return beginPacket(remote_addr, port);
	else
		return ret;
}