const char *convertToIpv4(unsigned char *addr)
{
    struct in_addr in;
    memcpy(&in,addr,4);
    return inet_ntoa(in);
}