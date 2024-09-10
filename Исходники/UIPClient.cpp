/**
 * @brief
 * @note
 * @param
 * @retval
 */
int UIPClient::connect(const char* host, uint16_t port) {

    // Look up the host first
    int         ret = 0;
#if UIP_UDP
    DNSClient   dns;
    IPAddress   remote_addr;

    dns.begin(UIPEthernetClass::_dnsServerAddress);
    ret = dns.getHostByName(host, remote_addr);
    if(ret == 1) {
        return connect(remote_addr, port);
    }
#endif
    return ret;
}