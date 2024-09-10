void dummy_server_process(const accept_server_socket_ret_t &sock,
			  const LIBCXX_NAMESPACE::fd &terminator,
			  bool passive,
			  bool ignore_port=false)
{
	auto sock_terminated=
		LIBCXX_NAMESPACE::fdtimeoutconfig::terminate_fd(terminator)
		(sock.first);

	auto stream=sock_terminated->getiostream();

	std::string cmd,line;
	LIBCXX_NAMESPACE::fdptr dataconn;
	LIBCXX_NAMESPACE::sockaddrptr dataconnaddr;
	LIBCXX_NAMESPACE::fdptr openconn;

	bool received_allo=false;

	auto make_conn=[&]
		{
			if (!dataconn.null())
			{
				LIBCXX_NAMESPACE::fd newsock=dataconn->accept();

				return new_server_socket(newsock);
			}

			auto sock=LIBCXX_NAMESPACE::fd::base
			::socket(dataconnaddr->family(), SOCK_STREAM, 0);

			sock->connect(dataconnaddr);

			return new_server_socket(sock);
		};

	do
	{
		line.clear();
		line.reserve(cmd.size());

		for (auto b=cmd.begin(), e=cmd.end(); b != e; ++b)
		{
			if ((unsigned char)*b == 255) // telnet escape
			{
				if (++b == e)
					break;
				continue;
			}
			line.push_back(*b);
		}

		if (line.substr(0, 8) == "AUTH TLS")
		{
			(*stream) << "226 Ok\r\n" << std::flush;

			stream=new_server_socket(sock_terminated)
				->getiostream();
			continue;
		}

		if (line.substr(0, 4) == "PASV" && passive)
		{
			received_allo=false;
			dataconn=({
					std::list<LIBCXX_NAMESPACE::fd> fds;

					LIBCXX_NAMESPACE::netaddr
						::create(sock.second
							 ->address(),
							 0)->bind(fds, false);

					fds.front();
				});

			dataconn->listen();
			dataconnaddr=LIBCXX_NAMESPACE::sockaddrptr();
			auto sockname=dataconn->getsockname();

			std::string portname=({
					std::ostringstream o;

					int portnum=sockname->port();
					o << sockname->address() << "."
					  << portnum / 256 << "."
					  << portnum % 256;

					o.str();
				});