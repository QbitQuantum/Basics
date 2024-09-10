/*
=============
Sys_SockaddrToString
=============
*/
static void Sys_SockaddrToString(char *dest, int destlen, struct sockaddr *input)
{
#ifdef FEATURE_IPV6
	socklen_t inputlen;

	if (input->sa_family == AF_INET6)
	{
		inputlen = sizeof(struct sockaddr_in6);
	}
	else
	{
		inputlen = sizeof(struct sockaddr_in);
	}

	if (getnameinfo(input, inputlen, dest, destlen, NULL, 0, NI_NUMERICHOST) && destlen > 0)
	{
		*dest = '\0';
	}
#else // IPV4
#ifdef __MORPHOS__
	char *addr = Inet_NtoA(((struct sockaddr_in *)input)->sin_addr.s_addr);
#else
	char *addr = inet_ntoa(((struct sockaddr_in *)input)->sin_addr);
#endif

	Q_strncpyz(dest, addr, destlen);
#endif
}