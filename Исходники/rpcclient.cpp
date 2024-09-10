void RPCClient::net_process(const std::function<void(std::string)>& disconnect) {
	connected = true;

	uint8_t count = 0;
	while (true) {
		int content_length = -2;
		bool close_after_read = false;
		int max_read;
		char buf[2048];
		std::string line;

		while (true) {
			std::string::size_type line_break;
			while ((line_break = line.find("\r\n")) == std::string::npos) {
				if (line.find("\r") != std::string::npos)
					max_read = 1;
				else
					max_read = 2;

				if (read_all(buf, max_read, std::chrono::seconds(10)) != max_read)
					return disconnect("Failed to read server response");
				line.append(buf, buf + max_read);

				if (line.length() > 16384)
					return disconnect("Got header longer than 16k!");
			}

			std::string current_line(line.substr(0, line_break));
			line = line.substr(line_break + 2);

			if (content_length == -2) {
				if (current_line != std::string("HTTP/1.1 200 OK"))
					return disconnect("Got HTTP error message: " + asciifyString(current_line));
				content_length++;
			} else if (current_line.length()) {
				std::string::size_type colon(current_line.find(':'));
				if (colon == std::string::npos)
					return disconnect("Got Bad HTTP header line: " + asciifyString(current_line));
				if (current_line.compare(0, strlen("Connection: "), "Connection: ") == 0) {
					if (current_line.compare(strlen("Connection: "), strlen("close"), "close") == 0)
						close_after_read = true;
					else if (current_line.compare(strlen("Connection: "), strlen("keep-alive"), "keep-alive") != 0)
						return disconnect("Got Bad HTTP Connection header line: " + asciifyString(current_line));
				} else if (current_line.compare(0, strlen("Content-Length: "), "Content-Length: ") == 0) {
					try {
						size_t endpos;
						content_length = std::stoi(&(current_line.c_str())[strlen("Content-Length: ")], &endpos);
						if (content_length < 0 || endpos != current_line.length() - strlen("Content-Length: "))
							return disconnect("Got Bad HTTP Content-Length header line: " + asciifyString(current_line));
					} catch (std::exception& e) {
						return disconnect("Got Bad HTTP Content-Length header line: " + asciifyString(current_line));
					}
				}
			} else if (content_length < 0)
				return disconnect("Got to end of HTTP headers without a Content-Length");
			else
				break;
		}

		if (content_length < 0 || content_length > 1024*1024*100)
			return disconnect("Got unreasonably large response size");

		//Dumb JSON parser that mostly assumes valid (minimal-size) JSON...
		static const std::string expected_start("{\"result\":{");
		{
			char resp[expected_start.length()];
			if (read_all(resp, expected_start.length()) != (ssize_t)expected_start.length())
				return disconnect("Failed to read response");
			if (memcmp(resp, &expected_start[0], expected_start.length()) != 0)
				return disconnect("Got result which was not an object");
		}

		std::vector<unsigned char> resp(content_length - expected_start.length());
		if (read_all((char*)&resp[0], content_length - expected_start.length()) != content_length - (ssize_t)expected_start.length())
			return disconnect("Failed to read response");
		auto it = resp.begin();

		//These do not move
		std::list<CTxMemPoolEntry> txn;
		//These index into txn
		std::vector<CTxMemPoolEntry*> vectorToSort;
		std::unordered_map<std::string, CTxMemPoolEntry*> hashToEntry;
		std::unordered_multimap<std::string, CTxMemPoolEntry*> txnWaitingOnDeps;

		// These are values/flags about the current status of the parser
		int32_t stringStart = -1, fieldValueStart = -1;
		std::string txHash, fieldString;
		long tx_size = -1; uint64_t tx_fee = -1; double tx_prio = -1;
		bool inTx = false, inFieldString = false, inFieldValue = false;
		std::unordered_set<std::string> txDeps;

		static const std::string expected_end("},\"error\":null,\"id\":1}\n");
		while (it < resp.end() - expected_end.length()) {
			while ((*it == ' ') && it < resp.end() - 1) it++;
			switch(*it) {
			case '"':
				if (stringStart != -1) {
					if (!inTx)
						txHash = std::string(resp.begin() + stringStart, it);
					else if (inFieldString)
						fieldString = std::string(resp.begin() + stringStart, it);
					else if (inFieldValue)
						return disconnect("got string as a field value");
					stringStart = -1;
				} else
					stringStart = it - resp.begin() + 1;
				break;
			case ':':
				if (stringStart != -1)
					return disconnect("Got : in a string (all strings should have been hex");
				if (inFieldString) {
					inFieldValue = true;
					inFieldString = false;
					fieldValueStart = it - resp.begin() + 1;
				} else if (inFieldValue)
					return disconnect("Got : in an unexpected place");
				break;
			case ',':
				if (stringStart != -1)
					return disconnect("Got , in a string (all strings should have been hex");
				if (inFieldValue) {
					inFieldValue = false;
					inFieldString = true;
					if (fieldString == "size") {
						try {
							tx_size = std::stol(std::string(resp.begin() + fieldValueStart, it));
						} catch (std::exception& e) {
							return disconnect("transaction size could not be parsed");
						}
					} else if (fieldString == "fee") {
						try {
							tx_fee = uint64_t(std::stod(std::string(resp.begin() + fieldValueStart, it)) * 100000000);
						} catch (std::exception& e) {
							return disconnect("transaction value could not be parsed");
						}
					} else if (fieldString == "currentpriority") {
						try {
							tx_prio = std::stod(std::string(resp.begin() + fieldValueStart, it));
						} catch (std::exception& e) {
							return disconnect("transaction prio could not be parsed");
						}
					}
				} else if (inTx)
					return disconnect("Got unexpected ,");
				break;
			case '[':
			{
				it++;
				int32_t depStringStart = -1;
				while (*it != ']' && it < resp.end() - 1) {
					if (*it == '"') {
						if (depStringStart != -1) {
							txDeps.insert(std::string(resp.begin() + depStringStart, it));
							depStringStart = -1;
						} else
							depStringStart = it - resp.begin() + 1;
					}
					it++;
				}
				if (*it != ']' || depStringStart != -1)
					return disconnect("Missing array end character (])");
				break;
			}
			case '{':
				if (stringStart != -1)
					return disconnect("Got { in a string (all strings should have been hex");
				else if (!inTx) {
					inTx = true;
					inFieldString = true;
				} else
					return disconnect("Got JSON object start when we weren't expecting one");
				break;
			case '}':
				if (inTx) {
					if (inFieldValue) {
						inFieldValue = false;
						if (fieldString == "size") {
							try {
								tx_size = std::stol(std::string(resp.begin() + fieldValueStart, it));
							} catch (std::exception& e) {
								return disconnect("transaction size could not be parsed");
							}
						} else if (fieldString == "fee") {
							try {
								tx_fee = uint64_t(std::stod(std::string(resp.begin() + fieldValueStart, it)) * 100000000);
							} catch (std::exception& e) {
								return disconnect("transaction value could not be parsed");
							}
						} else if (fieldString == "currentpriority") {
							try {
								tx_prio = std::stod(std::string(resp.begin() + fieldValueStart, it));
							} catch (std::exception& e) {
								return disconnect("transaction prio could not be parsed");
							}
						}
					} else
						return disconnect("Got unepxecpted }");

					if (tx_size < 0)
						return disconnect("Did not get transaction size");
					else if (tx_fee < 0)
						return disconnect("Did not get transaction fee");
					else if (tx_prio < 0)
						return disconnect("Did not get transaction prio");

					std::vector<unsigned char> hash;
					if (!hex_str_to_reverse_vector(txHash, hash) || hash.size() != 32)
						return disconnect("got bad hash");

					txn.emplace_back(tx_fee, tx_size, tx_prio, hash, txDeps.size());
					if (!hashToEntry.insert(std::make_pair(txHash, &txn.back())).second)
						return disconnect("Duplicate transaction");

					if (txDeps.empty())
						vectorToSort.push_back(&txn.back());
					else {
						for (const std::string& dep : txDeps) {
							auto depIt = hashToEntry.find(dep);
							if (depIt == hashToEntry.end())
								txnWaitingOnDeps.insert(std::make_pair(dep, &txn.back()));
							else
								depIt->second->setDeps.insert(&txn.back());
						}
					}

					auto waitingIts = txnWaitingOnDeps.equal_range(txHash);
					for (auto waitingIt = waitingIts.first; waitingIt != waitingIts.second; waitingIt++)
						txn.back().setDeps.insert(waitingIt->second);
					txnWaitingOnDeps.erase(txHash);

					inTx = false;
					tx_size = -1;
					tx_fee = -1;
					txDeps.clear();
				} else
					return disconnect("Global JSON object closed before the end");
				break;
			}
			it++;
		}
		if (it != resp.end() - expected_end.length() || memcmp(&(*it), &expected_end[0], expected_end.length()) != 0)
			return disconnect("JSON object was not closed at the end");

		if (!txnWaitingOnDeps.empty())
			return disconnect("Tx depended on another one which did not exist");

		std::vector<std::pair<std::vector<unsigned char>, size_t> > txn_selected;
		std::function<bool (const CTxMemPoolEntry* a, const CTxMemPoolEntry* b)> comp = [](const CTxMemPoolEntry* a, const CTxMemPoolEntry* b) {
			return a->feePerKb < b->feePerKb || (a->feePerKb == b->feePerKb && a->prio < b->prio);
		};
		std::make_heap(vectorToSort.begin(), vectorToSort.end(), comp);

		uint64_t minFeePerKbSelected = 4000000000;
		unsigned minFeePerKbTxnCount = 0;
		uint64_t totalSizeSelected = 0;
		while (totalSizeSelected < 9*MAX_FAS_TOTAL_SIZE/10 && vectorToSort.size()) {
			std::pop_heap(vectorToSort.begin(), vectorToSort.end(), comp);
			CTxMemPoolEntry* e = vectorToSort.back();
			vectorToSort.pop_back();
			if (e->size <= MAX_RELAY_TRANSACTION_BYTES) {
				for (CTxMemPoolEntry* dep : e->setDeps)
					if ((--dep->reqCount) == 0) {
						vectorToSort.push_back(dep);
						std::push_heap(vectorToSort.begin(), vectorToSort.end(), comp);
					}
				txn_selected.push_back(std::make_pair(e->hash, e->size));
				totalSizeSelected += e->size;
				if (e->feePerKb == minFeePerKbSelected)
					minFeePerKbTxnCount++;
				else if (e->feePerKb < minFeePerKbSelected) {
					minFeePerKbSelected = e->feePerKb;
					minFeePerKbTxnCount = 1;
				}
			}
		}

		unsigned minFeePerKbTxnSkipped = 0;
		while (vectorToSort.size()) {
			std::pop_heap(vectorToSort.begin(), vectorToSort.end(), comp);
			CTxMemPoolEntry* e = vectorToSort.back();
			vectorToSort.pop_back();
			if (e->feePerKb != minFeePerKbSelected)
				break;
			minFeePerKbTxnSkipped++;
		}

		if (++count == 0 && minFeePerKbTxnSkipped > 1 && minFeePerKbTxnCount > 1)
			printf("WARNING: Skipped %u txn while accepting %u identical-fee txn\n", minFeePerKbTxnSkipped, minFeePerKbTxnCount);

		txn_for_block_func(txn_selected, txn.size());
		awaiting_response = false;

		if (close_after_read)
			return disconnect("Got Connection: close");
	}
}