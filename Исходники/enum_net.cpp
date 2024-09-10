	std::vector<ip_route> enum_routes(io_service& ios, error_code& ec)
	{
		std::vector<ip_route> ret;
	
#if TORRENT_USE_SYSCTL
/*
		struct rt_msg
		{
			rt_msghdr m_rtm;
			char buf[512];
		};

		rt_msg m;
		int len = sizeof(rt_msg);
		bzero(&m, len);
		m.m_rtm.rtm_type = RTM_GET;
		m.m_rtm.rtm_flags = RTF_UP | RTF_GATEWAY;
		m.m_rtm.rtm_version = RTM_VERSION;
		m.m_rtm.rtm_addrs = RTA_DST | RTA_GATEWAY | RTA_NETMASK;
		m.m_rtm.rtm_seq = 0;
		m.m_rtm.rtm_msglen = len;

		int s = socket(PF_ROUTE, SOCK_RAW, AF_UNSPEC);
		if (s == -1)
		{
			ec = error_code(errno, asio::error::system_category);
			return std::vector<ip_route>();
		}

		int n = write(s, &m, len);
		if (n == -1)
		{
			ec = error_code(errno, asio::error::system_category);
			close(s);
			return std::vector<ip_route>();
		}
		else if (n != len)
		{
			ec = asio::error::operation_not_supported;
			close(s);
			return std::vector<ip_route>();
		}
		bzero(&m, len);

		n = read(s, &m, len);
		if (n == -1)
		{
			ec = error_code(errno, asio::error::system_category);
			close(s);
			return std::vector<ip_route>();
		}

		for (rt_msghdr* ptr = &m.m_rtm; (char*)ptr < ((char*)&m.m_rtm) + n; ptr = (rt_msghdr*)(((char*)ptr) + ptr->rtm_msglen))
		{
			std::cout << " rtm_msglen: " << ptr->rtm_msglen << std::endl;
			std::cout << " rtm_type: " << ptr->rtm_type << std::endl;
			if (ptr->rtm_errno)
			{
				ec = error_code(ptr->rtm_errno, asio::error::system_category);
				return std::vector<ip_route>();
			}
			if (m.m_rtm.rtm_flags & RTF_UP == 0
				|| m.m_rtm.rtm_flags & RTF_GATEWAY == 0)
			{
				ec = asio::error::operation_not_supported;
				return address_v4::any();
			}
			if (ptr->rtm_addrs & RTA_DST == 0
				|| ptr->rtm_addrs & RTA_GATEWAY == 0
				|| ptr->rtm_addrs & RTA_NETMASK == 0)
			{
				ec = asio::error::operation_not_supported;
				return std::vector<ip_route>();
			}
			if (ptr->rtm_msglen > len - ((char*)ptr - ((char*)&m.m_rtm)))
			{
				ec = asio::error::operation_not_supported;
				return std::vector<ip_route>();
			}
			int min_len = sizeof(rt_msghdr) + 2 * sizeof(sockaddr_in);
			if (m.m_rtm.rtm_msglen < min_len)
			{
				ec = asio::error::operation_not_supported;
				return std::vector<ip_route>();
			}

			ip_route r;
			// destination
			char* p = m.buf;
			sockaddr_in* sin = (sockaddr_in*)p;
			r.destination = sockaddr_to_address((sockaddr*)p);

			// gateway
			p += sin->sin_len;
			sin = (sockaddr_in*)p;
			r.gateway = sockaddr_to_address((sockaddr*)p);

			// netmask
			p += sin->sin_len;
			sin = (sockaddr_in*)p;
			r.netmask = sockaddr_to_address((sockaddr*)p);
			ret.push_back(r);
		}
		close(s);
*/
	int mib[6] = { CTL_NET, PF_ROUTE, 0, AF_UNSPEC, NET_RT_DUMP, 0};

	size_t needed = 0;
#ifdef TORRENT_OS2
	if (__libsocket_sysctl(mib, 6, 0, &needed, 0, 0) < 0)
#else
	if (sysctl(mib, 6, 0, &needed, 0, 0) < 0)
#endif
	{
		ec = error_code(errno, asio::error::system_category);
		return std::vector<ip_route>();
	}

	if (needed <= 0)
	{
		return std::vector<ip_route>();
	}

	boost::scoped_array<char> buf(new (std::nothrow) char[needed]);
	if (buf.get() == 0)
	{
		ec = asio::error::no_memory;
		return std::vector<ip_route>();
	}

#ifdef TORRENT_OS2
	if (__libsocket_sysctl(mib, 6, buf.get(), &needed, 0, 0) < 0)
#else
	if (sysctl(mib, 6, buf.get(), &needed, 0, 0) < 0)
#endif
	{
		ec = error_code(errno, asio::error::system_category);
		return std::vector<ip_route>();
	}

	char* end = buf.get() + needed;

	int s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
	{
		ec = error_code(errno, asio::error::system_category);
		return std::vector<ip_route>();
	}
	rt_msghdr* rtm;
	for (char* next = buf.get(); next < end; next += rtm->rtm_msglen)
	{
		rtm = (rt_msghdr*)next;
		if (rtm->rtm_version != RTM_VERSION)
			continue;
		
		ip_route r;
		if (parse_route(s, rtm, &r)) ret.push_back(r);
	}
	close(s);
	
#elif TORRENT_USE_GETIPFORWARDTABLE
/*
	move this to enum_net_interfaces
		// Load Iphlpapi library
		HMODULE iphlp = LoadLibraryA("Iphlpapi.dll");
		if (!iphlp)
		{
			ec = asio::error::operation_not_supported;
			return std::vector<ip_route>();
		}

		// Get GetAdaptersInfo() pointer
		typedef DWORD (WINAPI *GetAdaptersInfo_t)(PIP_ADAPTER_INFO, PULONG);
		GetAdaptersInfo_t GetAdaptersInfo = (GetAdaptersInfo_t)GetProcAddress(iphlp, "GetAdaptersInfo");
		if (!GetAdaptersInfo)
		{
			FreeLibrary(iphlp);
			ec = asio::error::operation_not_supported;
			return std::vector<ip_route>();
		}

		PIP_ADAPTER_INFO adapter_info = 0;
		ULONG out_buf_size = 0;
		if (GetAdaptersInfo(adapter_info, &out_buf_size) != ERROR_BUFFER_OVERFLOW)
		{
			FreeLibrary(iphlp);
			ec = asio::error::operation_not_supported;
			return std::vector<ip_route>();
		}

		adapter_info = (IP_ADAPTER_INFO*)malloc(out_buf_size);
		if (!adapter_info)
		{
			FreeLibrary(iphlp);
			ec = asio::error::no_memory;
			return std::vector<ip_route>();
		}

		if (GetAdaptersInfo(adapter_info, &out_buf_size) == NO_ERROR)
		{
			for (PIP_ADAPTER_INFO adapter = adapter_info;
				adapter != 0; adapter = adapter->Next)
			{

				ip_route r;
				r.destination = address::from_string(adapter->IpAddressList.IpAddress.String, ec);
				r.gateway = address::from_string(adapter->GatewayList.IpAddress.String, ec);
				r.netmask = address::from_string(adapter->IpAddressList.IpMask.String, ec);
				strncpy(r.name, adapter->AdapterName, sizeof(r.name));

				if (ec)
				{
					ec = error_code();
					continue;
				}
				ret.push_back(r);
			}
		}

		// Free memory
		free(adapter_info);
		FreeLibrary(iphlp);
*/

		// Load Iphlpapi library
		HMODULE iphlp = LoadLibraryA("Iphlpapi.dll");
		if (!iphlp)
		{
			ec = asio::error::operation_not_supported;
			return std::vector<ip_route>();
		}

		typedef DWORD (WINAPI *GetIfEntry_t)(PMIB_IFROW pIfRow);
		GetIfEntry_t GetIfEntry = (GetIfEntry_t)GetProcAddress(iphlp, "GetIfEntry");
		if (!GetIfEntry)
		{
			ec = asio::error::operation_not_supported;
			return std::vector<ip_route>();
		}

#if _WIN32_WINNT >= 0x0600
		typedef DWORD (WINAPI *GetIpForwardTable2_t)(
			ADDRESS_FAMILY, PMIB_IPFORWARD_TABLE2*);
		typedef void (WINAPI *FreeMibTable_t)(PVOID Memory);
			
		GetIpForwardTable2_t GetIpForwardTable2 = (GetIpForwardTable2_t)GetProcAddress(
			iphlp, "GetIpForwardTable2");
		FreeMibTable_t FreeMibTable = (FreeMibTable_t)GetProcAddress(
			iphlp, "FreeMibTable");
		if (GetIpForwardTable2 && FreeMibTable)
		{
			MIB_IPFORWARD_TABLE2* routes = NULL;
			int res = GetIpForwardTable2(AF_UNSPEC, &routes);
			if (res == NO_ERROR)
			{
				for (int i = 0; i < routes->NumEntries; ++i)
				{
					ip_route r;
					r.gateway = sockaddr_to_address((const sockaddr*)&routes->Table[i].NextHop);
					r.destination = sockaddr_to_address(
						(const sockaddr*)&routes->Table[i].DestinationPrefix.Prefix);
					r.netmask = build_netmask(routes->Table[i].SitePrefixLength
						, routes->Table[i].DestinationPrefix.Prefix.si_family);
					MIB_IFROW ifentry;
					ifentry.dwIndex = routes->Table[i].InterfaceIndex;
					if (GetIfEntry(&ifentry) == NO_ERROR)
					{
						wcstombs(r.name, ifentry.wszName, sizeof(r.name));
						r.mtu = ifentry.dwMtu;
						ret.push_back(r);
					}
				}
			}
			if (routes) FreeMibTable(routes);
			FreeLibrary(iphlp);
			return ret;
		}
#endif

		// Get GetIpForwardTable() pointer
		typedef DWORD (WINAPI *GetIpForwardTable_t)(PMIB_IPFORWARDTABLE pIpForwardTable,PULONG pdwSize,BOOL bOrder);
			
		GetIpForwardTable_t GetIpForwardTable = (GetIpForwardTable_t)GetProcAddress(
			iphlp, "GetIpForwardTable");
		if (!GetIpForwardTable)
		{
			FreeLibrary(iphlp);
			ec = asio::error::operation_not_supported;
			return std::vector<ip_route>();
		}

		MIB_IPFORWARDTABLE* routes = NULL;
		ULONG out_buf_size = 0;
		if (GetIpForwardTable(routes, &out_buf_size, FALSE) != ERROR_INSUFFICIENT_BUFFER)
		{
			FreeLibrary(iphlp);
			ec = asio::error::operation_not_supported;
			return std::vector<ip_route>();
		}

		routes = (MIB_IPFORWARDTABLE*)malloc(out_buf_size);
		if (!routes)
		{
			FreeLibrary(iphlp);
			ec = asio::error::no_memory;
			return std::vector<ip_route>();
		}

		if (GetIpForwardTable(routes, &out_buf_size, FALSE) == NO_ERROR)
		{
			for (int i = 0; i < routes->dwNumEntries; ++i)
			{
				ip_route r;
				r.destination = inaddr_to_address((in_addr const*)&routes->table[i].dwForwardDest);
				r.netmask = inaddr_to_address((in_addr const*)&routes->table[i].dwForwardMask);
				r.gateway = inaddr_to_address((in_addr const*)&routes->table[i].dwForwardNextHop);
				MIB_IFROW ifentry;
				ifentry.dwIndex = routes->table[i].dwForwardIfIndex;
				if (GetIfEntry(&ifentry) == NO_ERROR)
				{
					wcstombs(r.name, ifentry.wszName, sizeof(r.name));
					r.name[sizeof(r.name)-1] = 0;
					r.mtu = ifentry.dwMtu;
					ret.push_back(r);
				}
			}
		}

		// Free memory
		free(routes);
		FreeLibrary(iphlp);
#elif TORRENT_USE_NETLINK
		enum { BUFSIZE = 8192 };

		int sock = socket(PF_ROUTE, SOCK_DGRAM, NETLINK_ROUTE);
		if (sock < 0)
		{
			ec = error_code(errno, asio::error::system_category);
			return std::vector<ip_route>();
		}

		int seq = 0;

		char msg[BUFSIZE];
		memset(msg, 0, BUFSIZE);
		nlmsghdr* nl_msg = (nlmsghdr*)msg;

		nl_msg->nlmsg_len = NLMSG_LENGTH(sizeof(rtmsg));
		nl_msg->nlmsg_type = RTM_GETROUTE;
		nl_msg->nlmsg_flags = NLM_F_DUMP | NLM_F_REQUEST;
		nl_msg->nlmsg_seq = seq++;
		nl_msg->nlmsg_pid = getpid();

		if (send(sock, nl_msg, nl_msg->nlmsg_len, 0) < 0)
		{
			ec = error_code(errno, asio::error::system_category);
			close(sock);
			return std::vector<ip_route>();
		}

		int len = read_nl_sock(sock, msg, BUFSIZE, seq, getpid());
		if (len < 0)
		{
			ec = error_code(errno, asio::error::system_category);
			close(sock);
			return std::vector<ip_route>();
		}

		int s = socket(AF_INET, SOCK_DGRAM, 0);
		if (s < 0)
		{
			ec = error_code(errno, asio::error::system_category);
			return std::vector<ip_route>();
		}
		for (; NLMSG_OK(nl_msg, len); nl_msg = NLMSG_NEXT(nl_msg, len))
		{
			ip_route r;
			if (parse_route(s, nl_msg, &r)) ret.push_back(r);
		}
		close(s);
		close(sock);

#endif
		return ret;
	}