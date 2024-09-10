bool NetUtil::is_valid_ipv4(const char* ipstr)
{
#ifdef WIN32
	WSADATA info;
	memset(&info, 0, sizeof(info));
	WSAStartup(MAKEWORD(2, 0), &info);

	sockaddr sa;
	int len = sizeof(sa);
	int ret = WSAStringToAddressA(const_cast<char*>(ipstr), AF_INET, NULL, &sa, &len);
	
	WSACleanup();
	return ret == 0;
#else
    struct in_addr ia;

    if (inet_pton(AF_INET, ipstr, &ia) == 0) {
        return false;
    }
    return true;
#endif
}