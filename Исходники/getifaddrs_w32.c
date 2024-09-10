int ROKEN_LIB_FUNCTION
rk_getifaddrs(struct ifaddrs **ifpp)
{
    SOCKET s = INVALID_SOCKET;
    size_t il_len = 8192;
    int ret = -1;
    INTERFACE_INFO *il = NULL;

    *ifpp = NULL;

    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == INVALID_SOCKET)
	return -1;

    for (;;) {
	DWORD cbret = 0;

	il = malloc(il_len);
	if (!il)
	    break;

	ZeroMemory(il, il_len);

	if (WSAIoctl(s, SIO_GET_INTERFACE_LIST, NULL, 0,
		     (LPVOID) il, (DWORD) il_len, &cbret,
		     NULL, NULL) == 0) {
	    il_len = cbret;
	    break;
	}

	free (il);
	il = NULL;

	if (WSAGetLastError() == WSAEFAULT && cbret > il_len) {
	    il_len = cbret;
	} else {
	    break;
	}
    }

    if (!il)
	goto _exit;

    /* il is an array of INTERFACE_INFO structures.  il_len has the
       actual size of the buffer.  The number of elements is
       il_len/sizeof(INTERFACE_INFO) */

    {
	size_t n = il_len / sizeof(INTERFACE_INFO);
	size_t i;

	for (i = 0; i < n; i++ ) {
	    struct ifaddrs *ifp;

	    ifp = malloc(sizeof(*ifp));
	    if (ifp == NULL)
		break;

	    ZeroMemory(ifp, sizeof(*ifp));

	    ifp->ifa_next = NULL;
	    ifp->ifa_name = NULL;
	    ifp->ifa_flags = il[i].iiFlags;
	    ifp->ifa_addr = dupaddr(&il[i].iiAddress);
	    ifp->ifa_netmask = dupaddr(&il[i].iiNetmask);
	    ifp->ifa_broadaddr = dupaddr(&il[i].iiBroadcastAddress);
	    ifp->ifa_data = NULL;

	    *ifpp = ifp;
	    ifpp = &ifp->ifa_next;
	}

	if (i == n)
	    ret = 0;
    }

 _exit:

    if (s != INVALID_SOCKET)
	closesocket(s);

    if (il)
	free (il);

    return ret;
}