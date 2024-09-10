	void on_udp_receive(error_code const& ec, size_t bytes_transferred, udp::endpoint* from, char* buffer, int size)
	{
		if (ec)
		{
			std::printf("%s: UDP tracker, read failed: %s\n", time_now_string(), ec.message().c_str());
			return;
		}

		if (bytes_transferred < 16)
		{
			std::printf("%s: UDP message too short (from: %s)\n", time_now_string(), print_endpoint(*from).c_str());
			return;
		}

		if (m_abort)
		{
			return;
		}

		std::printf("%s: UDP message %d bytes\n", time_now_string(), int(bytes_transferred));

		char* ptr = buffer;
		detail::read_uint64(ptr);
		std::uint32_t const action = detail::read_uint32(ptr);
		std::uint32_t const transaction_id = detail::read_uint32(ptr);

		error_code e;

		switch (action)
		{
			case 0: // connect

				std::printf("%s: UDP connect from %s\n", time_now_string()
					, print_endpoint(*from).c_str());
				ptr = buffer;
				detail::write_uint32(0, ptr); // action = connect
				detail::write_uint32(transaction_id, ptr); // transaction_id
				detail::write_uint64(10, ptr); // connection_id
				m_socket.send_to(boost::asio::buffer(buffer, 16), *from, 0, e);
				if (e) std::printf("%s: UDP send_to failed. ERROR: %s\n"
					, time_now_string(), e.message().c_str());
				else std::printf("%s: UDP sent response to: %s\n"
					, time_now_string(), print_endpoint(*from).c_str());
				break;

			case 1: // announce

				++m_udp_announces;
				std::printf("%s: UDP announce [%d]\n", time_now_string()
					, int(m_udp_announces));
				ptr = buffer;
				detail::write_uint32(1, ptr); // action = announce
				detail::write_uint32(transaction_id, ptr); // transaction_id
				detail::write_uint32(1800, ptr); // interval
				detail::write_uint32(1, ptr); // incomplete
				detail::write_uint32(1, ptr); // complete
				// 0 peers
				m_socket.send_to(boost::asio::buffer(buffer, 20), *from, 0, e);
				if (e) std::printf("%s: UDP send_to failed. ERROR: %s\n"
					, time_now_string(), e.message().c_str());
				else std::printf("%s: UDP sent response to: %s\n"
					, time_now_string(), print_endpoint(*from).c_str());
				break;
			case 2:
				// ignore scrapes
				std::printf("%s: UDP scrape (ignored)\n", time_now_string());
				break;
			default:
				std::printf("%s: UDP unknown message: %d\n", time_now_string()
					, action);
				break;
		}

		m_socket.async_receive_from(
			boost::asio::buffer(buffer, size), *from, 0
			, std::bind(&udp_tracker::on_udp_receive, this, _1, _2, from, buffer, size));
	}