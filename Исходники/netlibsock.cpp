bool NetlibStringToAddress(const char* str, SOCKADDR_INET_M* addr)
{
	if (!str) return false;

	int len = sizeof(SOCKADDR_INET_M);
	return !WSAStringToAddressA((char*)str, AF_INET6, NULL, (PSOCKADDR)addr, &len);
}