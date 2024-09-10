void EnvironmentImpl::nodeIdImpl(NodeId& id)
{
	std::memset(&id, 0, sizeof(id));

	PIP_ADAPTER_INFO pAdapterInfo;
	PIP_ADAPTER_INFO pAdapter = 0;
	ULONG len    = sizeof(IP_ADAPTER_INFO);
	pAdapterInfo = reinterpret_cast<IP_ADAPTER_INFO*>(new char[len]);
	// Make an initial call to GetAdaptersInfo to get
	// the necessary size into len
	DWORD rc = GetAdaptersInfo(pAdapterInfo, &len);
	if (rc == ERROR_BUFFER_OVERFLOW)
	{
		delete [] reinterpret_cast<char*>(pAdapterInfo);
		pAdapterInfo = reinterpret_cast<IP_ADAPTER_INFO*>(new char[len]);
	}
	else if (rc != ERROR_SUCCESS)
	{
		return;
	}
	if (GetAdaptersInfo(pAdapterInfo, &len) == NO_ERROR)
	{
		pAdapter = pAdapterInfo;
		bool found = false;
		while (pAdapter && !found)
		{
			if (pAdapter->Type == MIB_IF_TYPE_ETHERNET && pAdapter->AddressLength == sizeof(id))
			{
				found = true;
				std::memcpy(&id, pAdapter->Address, pAdapter->AddressLength);
			}
			pAdapter = pAdapter->Next;
		}
	}
	delete [] reinterpret_cast<char*>(pAdapterInfo);
}