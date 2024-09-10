bool pop3_client::pop3_list(acl::socket_stream& conn, std::vector<size_t>& out)
{
	if (conn.puts("LIST") == -1)
	{
		logger_error("send LIST to pop3 server(%s) error %s, "
			"user: %s", pop3_ip_.c_str(), acl::last_serror(),
			auth_account_.c_str());
		return false;
	}

	acl::string line;
	if (conn.gets(line) == false)
	{
		logger_error("gets LIST's reply from server(%s) error(%s), "
			"user: %s", pop3_ip_.c_str(), acl::last_serror(),
			auth_account_.c_str());
		return false;
	}
	if (line.ncompare("+OK", 3, false) != 0)
	{
		logger_error("LIST's reply(%s) error from server %s, user: %s",
			line.c_str(), pop3_ip_.c_str(), auth_account_.c_str());
		return false;
	}

	logger("LIST's first reply: %s", line.c_str());

	while (true)
	{
		if (conn.gets(line) == false)
		{
			logger_error("LIST's reply error %s, from server %s, "
				"user %s", acl::last_serror(),
				pop3_ip_.c_str(), auth_account_.c_str());
			return false;
		}

		logger("LIST: %s", line.c_str());

		if (line == ".")
			break;
		char* ptr = line.c_str();
		char* p1 = acl_mystrtok(&ptr, " \t");
		if (ptr == NULL || *ptr == 0)
		{
			logger_error("invalid LIST's reply(%s) from server %s, "
				"user %s", p1, pop3_ip_.c_str(),
				auth_account_.c_str());
			return false;
		}
		int len = atoi(ptr);
		if (len <= 0)
		{
			logger_error("invalid LIST size(%d) from server %s, "
				"user %s", len, pop3_ip_.c_str(),
				auth_account_.c_str());
			return false;
		}
		out.push_back((size_t) len);
		meter_.total_size += len;
	}
	meter_.total_list = out.size();
	return true;
}