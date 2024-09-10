int DnsNameToIp(std::string name, std::string* ipv4)
{
	if (name.empty() || name == "")
	{
		return -1;
	}

	DNS_A_DATA dnsRet;

	PDNS_RECORD pDnsRecord;

	DNS_STATUS status = DnsQuery_A((PCSTR)name.c_str(), DNS_TYPE_A, DNS_QUERY_STANDARD, NULL, &pDnsRecord, NULL);

	if (status == 0)
	{
		IN_ADDR ipaddr;
		if (pDnsRecord)
			ipaddr.S_un.S_addr = (pDnsRecord->Data.A.IpAddress);

		*ipv4 = inet_ntoa(ipaddr);
	}

	return status;
}