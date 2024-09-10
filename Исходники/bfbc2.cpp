	bfbc2::server_info bfbc2::QueryServerInfo(sf::TcpSocket &socket) {

		server_info serverInfo;

		std::cout << "Sending serverInfo query..." << std::endl;

		if (socket.send(serverInfo_QueryPacket, sizeof(serverInfo_QueryPacket)) == sf::Socket::Status::Done) {

			std::cout << "Success! Waiting for response..." << std::endl;

			char buffer[PACKETSIZE];
			std::size_t received = 0;

			// receive response
			if (socket.receive(buffer, sizeof(buffer), received) == sf::Socket::Status::Done) {				

				if (received > 0) {

					std::cout << "Success! Processing..." << std::endl;

					// skip header.
					int index = 8;

					// get number of WORDs in packet, then store them for parsing.
					uint32_t numofwords = (static_cast<uint32_t>(buffer[index]) ) +
						(static_cast<uint32_t>(buffer[index + 1]) << 8) +
						(static_cast<uint32_t>(buffer[index + 2]) << 16)  +
						(static_cast<uint32_t>(buffer[index + 3]) << 24);

					// skip numwords
					index += 4;

					// extract the content of each word.
					std::vector<std::string> content;
					for (uint32_t i = 0; i < numofwords; i++) {
						content.push_back(GetWordContent(buffer, index));
					}

					// checks to see if we have the correct results
					if (!content.empty() && content.size() == 24) {

						//
						//	CHECKING FOR OK RESPONSE (.at(0)) & & IF ACCEPTINGPLAYERS )
						//
						if (content.at(0) == "OK") {

							if (content.at(12) == "AcceptingPlayers") {

								serverInfo.ip = socket.getRemoteAddress();
								serverInfo.name = content.at(1);
								serverInfo.playersonline = atoi(content.at(2).c_str());
								serverInfo.maxplayers = atoi(content.at(3).c_str());
								serverInfo.gamemode = content.at(4);
								std::string mapstring = content.at(5);

								// change map string to lowercase, as the map filename is stored in the server .cfg,
								// and the server admin can make it upper or lower case.
								std::transform(mapstring.begin(), mapstring.end(), mapstring.begin(), ::tolower);

								std::string map;

								if (mapstring.find("001") != std::string::npos) { map = "Panama Canal"; }
								else if (mapstring.find("mp_002") != std::string::npos) { map = "Valparaiso"; }
								else if (mapstring.find("003") != std::string::npos) { map = "Laguna Alta"; }
								else if (mapstring.find("004") != std::string::npos) { map = "Isla Inocentes"; }
								else if (mapstring.find("mp_005") != std::string::npos) { map = "Atacama Desert"; }
								else if (mapstring.find("006") != std::string::npos) { map = "Arica Harbor"; }
								else if (mapstring.find("007") != std::string::npos) { map = "White Pass"; }
								else if (mapstring.find("008") != std::string::npos) { map = "Nelson Bay"; }
								else if (mapstring.find("009") != std::string::npos) { map = "Laguna Presa"; }
								else if (mapstring.find("012") != std::string::npos) { map = "Port Valdez"; }
								else if (mapstring.find("oasis") != std::string::npos) { map = "Oasis"; }
								else if (mapstring.find("sp_005") != std::string::npos) { map = "Heavy Metal"; }
								else if (mapstring.find("sp_002") != std::string::npos) { map = "Cold War"; }
								else if (mapstring.find("harvest") != std::string::npos) { map = "Harvest Day"; }

								serverInfo.map = map;

							}

						}

					}

				}

			} // socket.receive

		} // socket.send

		// if send, receive, or content check fails anywhere, server_info.ip will return sf::IpAddress::None
		return serverInfo;

	}