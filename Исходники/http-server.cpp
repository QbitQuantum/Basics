bool server::read_socket_from_parent(int fd_socket, boost::asio::ip::tcp::socket& socket)
{
	typedef boost::asio::ip::tcp::socket::native_type native_type;

#if __APPLE__
	// macos is special...
	assert(CMSG_SPACE(sizeof(int)) == 16);
#endif

	struct msghdr	msg;
	union {
	  struct cmsghdr	cm;
#if __APPLE__
	  char				control[16];
#else
	  char				control[CMSG_SPACE(sizeof(int))];
#endif
	} control_un;

	msg.msg_control = control_un.control;
	msg.msg_controllen = sizeof(control_un.control);
	msg.msg_name = NULL;
	msg.msg_namelen = 0;

	boost::asio::ip::tcp::socket::endpoint_type peer_endpoint;

	struct iovec iov[1];
	iov[0].iov_base = peer_endpoint.data();
	iov[0].iov_len = peer_endpoint.capacity();
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;

	bool result = false;
	int n = recvmsg(fd_socket, &msg, 0);
	if (n >= 0)
	{
		peer_endpoint.resize(n);
	
		struct cmsghdr* cmptr CMSG_FIRSTHDR(&msg);
		if (cmptr != NULL and cmptr->cmsg_len == CMSG_LEN(sizeof(int)))
		{
			if (cmptr->cmsg_level != SOL_SOCKET)
			 	cerr << "control level != SOL_SOCKET" << endl;
			else if (cmptr->cmsg_type != SCM_RIGHTS)
				cerr << "control type != SCM_RIGHTS";
			else
			{
				int fd = *(reinterpret_cast<native_type*>(CMSG_DATA(cmptr)));
				if (fd >= 0)
				{
					socket.assign(peer_endpoint.protocol(), fd);
					result = true;
				}
			}
		}
		else
			cerr << "No file descriptor was passed" << endl;
	}