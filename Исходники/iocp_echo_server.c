static void create_iocp_accept(void)
{
	BOOL bRet;

	memset(&ac, 0, sizeof(ac));

	/* Create simple socket for acceptance */
	ac.sockfd = socket(PF_INET, SOCK_STREAM, 0);
	DIE(ac.sockfd == INVALID_SOCKET, "socket");

	/* Launch overlapped connection accept through AcceptEx. */
	bRet = AcceptEx(
			listenfd,
			ac.sockfd,
			ac.buffer,
			0,
			128,
			128,
			&ac.len,
			&ac.ov);
	DIE(bRet == FALSE && WSAGetLastError() != ERROR_IO_PENDING, "AcceptEx");
}