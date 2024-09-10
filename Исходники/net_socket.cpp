static int _inet_pton(int Family, const char * pszAddrString, void* pAddrBuf)
{
    struct sockaddr_storage tmpholder;
    int actualSize =  sizeof(sockaddr_storage);

    int result = WSAStringToAddressA((char *)pszAddrString, Family, NULL, (sockaddr*)&tmpholder, &actualSize);
    if (result) return -1;

    switch (Family) {
        case AF_INET:
            {
                struct sockaddr_in * ipv4 = reinterpret_cast< struct sockaddr_in *>(&tmpholder);
                memcpy(pAddrBuf, &(ipv4->sin_addr), sizeof(ipv4->sin_addr));
            }
            break;
        case AF_INET6:
            {
                struct sockaddr_in6 * ipv6 = reinterpret_cast< struct sockaddr_in6 *>(&tmpholder);
                memcpy(pAddrBuf, &(ipv6->sin6_addr), sizeof(ipv6->sin6_addr));
            }
            break;
    }
    return 1;
}