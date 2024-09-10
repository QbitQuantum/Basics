	void net_process() {
		while (true) {
			struct bitcoin_msg_header header;
			if (read_all(sock, (char*)&header, sizeof(header)) != sizeof(header))
				return disconnect("failed to read message header");

			if (header.magic != BITCOIN_MAGIC)
				return disconnect("invalid magic bytes");

			struct timeval start_read;
			gettimeofday(&start_read, NULL);

			header.length = le32toh(header.length);
			if (header.length > 5000000)
				return disconnect("got message too large");

			auto msg = std::make_shared<std::vector<unsigned char> > (sizeof(struct bitcoin_msg_header) + uint32_t(header.length));
			if (read_all(sock, (char*)&(*msg)[sizeof(struct bitcoin_msg_header)], header.length) != int(header.length))
				return disconnect("failed to read message");

			unsigned char fullhash[32];
			CSHA256 hash;
			hash.Write(&(*msg)[sizeof(struct bitcoin_msg_header)], header.length).Finalize(fullhash);
			hash.Reset().Write(fullhash, sizeof(fullhash)).Finalize(fullhash);
			if (memcmp((char*)fullhash, header.checksum, sizeof(header.checksum)))
				return disconnect("got invalid message checksum");

			if (!strncmp(header.command, "version", strlen("version"))) {
				if (connected != 0)
					return disconnect("got invalid version");
				connected = 1;

				if (header.length < sizeof(struct bitcoin_version_start))
					return disconnect("got short version");
				struct bitcoin_version_start *their_version = (struct bitcoin_version_start*) &(*msg)[sizeof(struct bitcoin_msg_header)];

				printf("%s Protocol version %u\n", host.c_str(), le32toh(their_version->protocol_version));

				struct bitcoin_version_with_header version_msg;
				version_msg.version.start.timestamp = htole64(time(0));
				memcpy(((char*)&version_msg.version.end.user_agent) + 27, location, 7);
				static_assert(BITCOIN_UA_LENGTH == 27 + 7 + 2 /* 27 + 7 + '/' + '\0' */, "BITCOIN_UA changed in header but file not updated");

				prepare_message("version", (unsigned char*)&version_msg, sizeof(struct bitcoin_version));
				if (send_all(sock, (char*)&version_msg, sizeof(struct bitcoin_version_with_header)) != sizeof(struct bitcoin_version_with_header))
					return disconnect("failed to send version message");

				struct bitcoin_msg_header verack_header;
				prepare_message("verack", (unsigned char*)&verack_header, 0);
				if (send_all(sock, (char*)&verack_header, sizeof(struct bitcoin_msg_header)) != sizeof(struct bitcoin_msg_header))
					return disconnect("failed to send verack");

				continue;
			} else if (!strncmp(header.command, "verack", strlen("verack"))) {
				if (connected != 1)
					return disconnect("got invalid verack");
				connected = 2;
				send_mutex.unlock();

				continue;
			}

			if (connected != 2)
				return disconnect("got non-version, non-verack before version+verack");

			if (!strncmp(header.command, "ping", strlen("ping"))) {
				memcpy(&header.command, "pong", sizeof("pong"));
				memcpy(&(*msg)[0], &header, sizeof(struct bitcoin_msg_header));
				std::lock_guard<std::mutex> lock(send_mutex);
				if (send_all(sock, (char*)&(*msg)[0], sizeof(struct bitcoin_msg_header) + header.length) != int64_t(sizeof(struct bitcoin_msg_header) + header.length))
					return disconnect("failed to send pong");
				continue;
			} else if (!strncmp(header.command, "inv", strlen("inv"))) {
				std::lock_guard<std::mutex> lock(send_mutex);

				try {
					std::set<std::vector<unsigned char> > setRequestBlocks;
					std::set<std::vector<unsigned char> > setRequestTxn;

					std::vector<unsigned char>::const_iterator it = msg->begin();
					it += sizeof(struct bitcoin_msg_header);
					uint64_t count = read_varint(it, msg->end());
					if (count > 50000)
						return disconnect("inv count > MAX_INV_SZ");

					uint32_t MSG_TX = htole32(1);
					uint32_t MSG_BLOCK = htole32(2);

					for (uint64_t i = 0; i < count; i++) {
						move_forward(it, 4 + 32, msg->end());
						std::vector<unsigned char> hash(it-32, it);

						const uint32_t type = (*(it-(1+32)) << 24) | (*(it-(2+32)) << 16) | (*(it-(3+32)) << 8) | *(it-(4+32));
						if (type == MSG_TX) {
							if (!txnAlreadySeen.insert(hash).second)
								continue;
							setRequestTxn.insert(hash);
						} else if (type == MSG_BLOCK) {
							if (!blocksAlreadySeen.insert(hash).second)
								continue;
							setRequestBlocks.insert(hash);
						} else
							return disconnect("unknown inv type");
					}

					if (setRequestBlocks.size()) {
						std::vector<unsigned char> getdataMsg;
						std::vector<unsigned char> invCount = varint(setRequestBlocks.size());
						getdataMsg.reserve(sizeof(struct bitcoin_msg_header) + invCount.size() + setRequestBlocks.size()*36);

						getdataMsg.insert(getdataMsg.end(), sizeof(struct bitcoin_msg_header), 0);
						getdataMsg.insert(getdataMsg.end(), invCount.begin(), invCount.end());

						for (auto& hash : setRequestBlocks) {
							getdataMsg.insert(getdataMsg.end(), (unsigned char*)&MSG_BLOCK, ((unsigned char*)&MSG_BLOCK) + 4);
							getdataMsg.insert(getdataMsg.end(), hash.begin(), hash.end());
						}

						prepare_message("getdata", (unsigned char*)&getdataMsg[0], invCount.size() + setRequestBlocks.size()*36);
						if (send_all(sock, (char*)&getdataMsg[0], sizeof(struct bitcoin_msg_header) + invCount.size() + setRequestBlocks.size()*36) !=
								int(sizeof(struct bitcoin_msg_header) + invCount.size() + setRequestBlocks.size()*36))
							return disconnect("error sending getdata");

						for (auto& hash : setRequestBlocks) {
							struct timeval tv;
							gettimeofday(&tv, NULL);
							for (unsigned int i = 0; i < hash.size(); i++)
								printf("%02x", hash[hash.size() - i - 1]);
							printf(" requested from %s at %lu\n", host.c_str(), uint64_t(tv.tv_sec) * 1000 + uint64_t(tv.tv_usec) / 1000);
						}
					}

					if (setRequestTxn.size()) {
						std::vector<unsigned char> getdataMsg;
						std::vector<unsigned char> invCount = varint(setRequestTxn.size());
						getdataMsg.reserve(sizeof(struct bitcoin_msg_header) + invCount.size() + setRequestTxn.size()*36);

						getdataMsg.insert(getdataMsg.end(), sizeof(struct bitcoin_msg_header), 0);
						getdataMsg.insert(getdataMsg.end(), invCount.begin(), invCount.end());

						for (const std::vector<unsigned char>& hash : setRequestTxn) {
							getdataMsg.insert(getdataMsg.end(), (unsigned char*)&MSG_TX, ((unsigned char*)&MSG_TX) + 4);
							getdataMsg.insert(getdataMsg.end(), hash.begin(), hash.end());
						}

						prepare_message("getdata", (unsigned char*)&getdataMsg[0], invCount.size() + setRequestTxn.size()*36);
						if (send_all(sock, (char*)&getdataMsg[0], sizeof(struct bitcoin_msg_header) + invCount.size() + setRequestTxn.size()*36) !=
								int(sizeof(struct bitcoin_msg_header) + invCount.size() + setRequestTxn.size()*36))
							return disconnect("error sending getdata");
					}
				} catch (read_exception) {
					return disconnect("failed to process inv");
				}
				continue;
			}

			memcpy(&(*msg)[0], &header, sizeof(struct bitcoin_msg_header));
			if (!strncmp(header.command, "block", strlen("block"))) {
				provide_block(this, msg, start_read);
			} else if (!strncmp(header.command, "tx", strlen("tx"))) {
				provide_transaction(this, msg);
			}
		}
	}