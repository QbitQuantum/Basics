	bool winsock2_streambuf::connect(const std::wstring & host, const std::wstring & service)
	{
		if (is_open())
		{
			m_lasterror = std::make_error_code(std::errc::already_connected);
			return false;
		}

		addrinfo_type * addr = nullptr;
		bool res = do_resolve(host.c_str(), service.c_str(), &addr);
		if (!res) return false;

		assert(addr);
		res = do_connect(addr);

		FreeAddrInfo(addr);
		return res;
	}