int
eXosip_guess_ip_for_via (int family, char *address, int size)
{
	/* w2000 and W95/98 */
	unsigned long  best_interface_index;
	DWORD hr;

	/* NT4 (sp4 only?) */
	PMIB_IPFORWARDTABLE ipfwdt;
	DWORD siz_ipfwd_table = 0;
	unsigned int ipf_cnt;

	address[0] = '\0';
	best_interface_index = -1;
	/* w2000 and W95/98 only */
	hr = GetBestInterface(inet_addr("217.12.3.11"),&best_interface_index);
	if (hr)
	{
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			hr,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPSTR) &lpMsgBuf, 0, NULL);

		OSIP_TRACE (osip_trace (__FILE__, __LINE__, OSIP_INFO4, NULL,
					 "GetBestInterface: %s\r\n", lpMsgBuf));
		best_interface_index = -1;
	}

	if (best_interface_index != -1)
	{ /* probably W2000 or W95/W98 */
		char *servername;
		char *serverip;
		char *netmask;
		OSIP_TRACE (osip_trace (__FILE__, __LINE__, OSIP_INFO4, NULL,
					 "Default Interface found %i\r\n", best_interface_index));

		if (0 == ppl_dns_get_local_fqdn(&servername, &serverip, &netmask,
						best_interface_index))
		{
			osip_strncpy(address, serverip, size);
			osip_free(servername);
			osip_free(serverip);
			osip_free(netmask);
			return 0;
		}
		return -1;
	}


	if (!GetIpForwardTable(NULL, &siz_ipfwd_table, FALSE) == ERROR_INSUFFICIENT_BUFFER
		|| !(ipfwdt = (PMIB_IPFORWARDTABLE) alloca (siz_ipfwd_table)))
	{
		OSIP_TRACE (osip_trace (__FILE__, __LINE__, OSIP_INFO4, NULL,
			"Allocation error\r\n"));
		return -1;
	}


	/* NT4 (sp4 support only?) */
	if (!GetIpForwardTable(ipfwdt, &siz_ipfwd_table, FALSE))
	{
		for (ipf_cnt = 0; ipf_cnt < ipfwdt->dwNumEntries; ++ipf_cnt) 
		{
			if (ipfwdt->table[ipf_cnt].dwForwardDest == 0)
			{ /* default gateway found */
				char *servername;
				char *serverip;
				char *netmask;
				OSIP_TRACE (osip_trace (__FILE__, __LINE__, OSIP_INFO4, NULL,
					"Default Interface found %i\r\n", ipfwdt->table[ipf_cnt].dwForwardIfIndex));

				if (0 ==  ppl_dns_get_local_fqdn(&servername,
								 &serverip,
								 &netmask,
								 ipfwdt->table[ipf_cnt].dwForwardIfIndex))
				{
					osip_strncpy(address, serverip, size);
					osip_free(servername);
					osip_free(serverip);
					osip_free(netmask);
					return 0;
				}
				return -1;
			}
		}

	}
	/* no default gateway interface found */
	return -1;
}