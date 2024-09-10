static void enable_listen(EVENT_KERNEL *ev, ACL_EVENT_FDTABLE *fdp)
{
	const char *myname = "enable_listen";
	ACL_SOCKET sock;
	DWORD ReceiveLen = 0;

	sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP,
		0, 0, WSA_FLAG_OVERLAPPED);

	memset(&fdp->event_read->overlapped, 0,
		sizeof(fdp->event_read->overlapped));

	fdp->stream->type |= ACL_VSTREAM_TYPE_LISTEN_IOCP;
	fdp->stream->iocp_sock = sock;

	if (AcceptEx(ACL_VSTREAM_SOCK(fdp->stream), sock,
		fdp->event_read->myAddrBlock, 0,
		ACCEPT_ADDRESS_LENGTH, ACCEPT_ADDRESS_LENGTH,
		&ReceiveLen, &fdp->event_read->overlapped) == FALSE
		&& acl_last_error() !=ERROR_IO_PENDING)
	{
		acl_msg_warn("%s(%d): AcceptEx error(%s)",
			myname, __LINE__, acl_last_serror());
	}
}