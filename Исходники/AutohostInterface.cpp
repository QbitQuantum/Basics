std::string AutohostInterface::TryBindSocket(
			boost::asio::ip::udp::socket& socket,
			const std::string& remoteIP, int remotePort,
			const std::string& localIP, int localPort)
{
	std::string errorMsg = "";

	ip::address localAddr;
	ip::address remoteAddr;
	boost::system::error_code err;
	try {
		socket.open(ip::udp::v6(), err); // test IP v6 support
		const bool supportsIPv6 = !err;

		remoteAddr = netcode::WrapIP(remoteIP, &err);
		if (err) {
			throw std::runtime_error("Failed to parse address " + remoteIP + ": " + err.message());
		}

		if (!supportsIPv6 && remoteAddr.is_v6()) {
			throw std::runtime_error("IP v6 not supported, can not use address " + remoteAddr.to_string());
		}

		if (localIP.empty()) {
			// use the "any" address as local "from"
			if (remoteAddr.is_v6()) {
				localAddr = ip::address_v6::any();
			} else {
				if (supportsIPv6) {
					socket.close();
				}
				socket.open(ip::udp::v4());
				localAddr = ip::address_v4::any();
			}
		} else {
			localAddr = netcode::WrapIP(localIP, &err);
			if (err) {
				throw std::runtime_error("Failed to parse local IP " + localIP + ": " + err.message());
			}
			if (localAddr.is_v6() != remoteAddr.is_v6()) {
				throw std::runtime_error("Local IP " + localAddr.to_string() + " and remote IP " + remoteAddr.to_string() + " are IP v4/v6 mixed");
			}
		}

		socket.bind(ip::udp::endpoint(localAddr, localPort));

		boost::asio::socket_base::non_blocking_io command(true);
		socket.io_control(command);

		// A similar, slighly less verbose message is already in GameServer
		//LogObject() << "[AutohostInterface] Connecting (UDP) to IP "
		//		<<  (remoteAddr.is_v6() ? "(v6)" : "(v4)") << " " << remoteAddr
		//		<< " Port " << remotePort;
		socket.connect(ip::udp::endpoint(remoteAddr, remotePort));
	} catch (std::runtime_error& e) { // includes also boost::system::system_error, as it inherits from runtime_error
		socket.close();
		errorMsg = e.what();
		if (errorMsg.empty()) {
			errorMsg = "Unknown problem";
		}
	}

	return errorMsg;
}