const char *custom_inet_ntop(int af, const void *src, char *dst, int cnt)
{
	struct sockaddr_in srcaddr;

	memset(&srcaddr, 0, sizeof(struct sockaddr_in));
	memcpy(&(srcaddr.sin_addr), src, sizeof(srcaddr.sin_addr));

	srcaddr.sin_family = af;
	if (WSAAddressToStringA((struct sockaddr *) &srcaddr, sizeof(struct sockaddr_in), 0, dst, (LPDWORD) &cnt) != 0)
	{

		wxLogInfo(wxT("SSH error: WSAAddressToStringA failed with error code %d"), WSAGetLastError());
		return NULL;
	}
	return dst;
}