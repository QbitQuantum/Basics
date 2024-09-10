//convert a hostname to an ip address
int GroveStreams::dnsLookup(const char* hostname, IPAddress& addr)
{
    int ret = 0;
    DNSClient dns;

    dns.begin(Ethernet.dnsServerIP());
    ret = dns.getHostByName(hostname, addr);
    return ret;
}