void PcapLiveDeviceList::setDnsServers()
{
#ifdef WIN32
	FIXED_INFO * fixedInfo;
	ULONG    ulOutBufLen;
	DWORD    dwRetVal;
	IP_ADDR_STRING * pIPAddr;

	uint8_t buf1[sizeof(FIXED_INFO)];
	fixedInfo = (FIXED_INFO *) buf1;
	ulOutBufLen = sizeof( FIXED_INFO );

	dwRetVal = GetNetworkParams( fixedInfo, &ulOutBufLen );
	uint8_t buf2[ulOutBufLen];
	if(ERROR_BUFFER_OVERFLOW == dwRetVal)
	{
		fixedInfo = (FIXED_INFO *)buf2;
	}

	if ((dwRetVal = GetNetworkParams( fixedInfo, &ulOutBufLen )) != 0)
		LOG_ERROR("Call to GetNetworkParams failed. Return Value: %08lx\n", dwRetVal);
	else
	{
		m_DnsServers.push_back(IPv4Address(fixedInfo->DnsServerList.IpAddress.String));
		int i = 1;
		LOG_DEBUG("Default DNS server IP #%d: %s\n", i++, fixedInfo->DnsServerList.IpAddress.String );

		pIPAddr = fixedInfo->DnsServerList.Next;
		while ( pIPAddr )
		{
			m_DnsServers.push_back(IPv4Address(pIPAddr->IpAddress.String));
			LOG_DEBUG("Default DNS server IP #%d: %s\n", i++, pIPAddr->IpAddress.String);
			pIPAddr = pIPAddr -> Next;
		}
	}
#elif LINUX
	std::string command = "nmcli dev list | grep IP4.DNS";
	std::string dnsServersInfo = executeShellCommand(command);
	if (dnsServersInfo == "")
	{
		LOG_DEBUG("Error retrieving DNS server list: call to nmcli gave no output");
		return;
	}

	std::istringstream stream(dnsServersInfo);
	std::string line;
	int i = 1;
	while(std::getline(stream, line))
	{
		std::istringstream lineStream(line);
		std::string headline;
		std::string dnsIP;
		lineStream >> headline;
		lineStream >> dnsIP;
		IPv4Address dnsIPAddr(dnsIP);
		if (!dnsIPAddr.isValid())
			continue;

		if (std::find(m_DnsServers.begin(), m_DnsServers.end(), dnsIPAddr) == m_DnsServers.end())
		{
			m_DnsServers.push_back(dnsIPAddr);
			LOG_DEBUG("Default DNS server IP #%d: %s\n", i++, dnsIPAddr.toString().c_str());
		}
	}
#elif MAC_OS_X

	SCDynamicStoreRef dynRef = SCDynamicStoreCreate(kCFAllocatorSystemDefault, CFSTR("iked"), NULL, NULL);
	if (dynRef == NULL)
	{
		LOG_DEBUG("Couldn't set DNS server list: failed to retrieve SCDynamicStore");
		return;
	}

	CFDictionaryRef dnsDict = (CFDictionaryRef)SCDynamicStoreCopyValue(dynRef,CFSTR("State:/Network/Global/DNS"));

	if (dnsDict == NULL)
	{
		LOG_DEBUG("Couldn't set DNS server list: failed to get DNS dictionary");
		CFRelease(dynRef);
		return;
	}

	CFArrayRef serverAddresses = (CFArrayRef)CFDictionaryGetValue(dnsDict, CFSTR("ServerAddresses"));

	if (serverAddresses == NULL)
	{
		LOG_DEBUG("Couldn't set DNS server list: server addresses array is null");
		CFRelease(dynRef);
		CFRelease(dnsDict);
		return;
	}

	CFIndex count = CFArrayGetCount(serverAddresses);
	for (CFIndex i = 0; i < count; i++)
	{
		CFStringRef serverAddress = (CFStringRef)CFArrayGetValueAtIndex(serverAddresses, i);

		if (serverAddress == NULL)
			continue;

		uint8_t buf[20];
		char* serverAddressCString = (char*)buf;
		CFStringGetCString(serverAddress, serverAddressCString, 20, kCFStringEncodingUTF8);
		m_DnsServers.push_back(IPv4Address(serverAddressCString));
		LOG_DEBUG("Default DNS server IP #%d: %s\n", (int)(i+1), serverAddressCString);
	}

	CFRelease(dynRef);
	CFRelease(dnsDict);
#endif
}