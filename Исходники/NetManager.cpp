bool NetManager::SelectAdapter(int index)
{
	// get adapter
	m_adapter = m_deviceList;
	for (int i = 0; i < index; i++)
	{
		m_adapter = m_adapter->next;
		if (m_adapter == nullptr)
			return false;
	}

	// get adapter infomation
	CString ip, gateway;
	MacAddress mac;

	IP_ADAPTER_INFO adapterInfo[16];
	DWORD bufSize = sizeof(adapterInfo);
	DWORD status = GetAdaptersInfo(adapterInfo, &bufSize);
	if (status != ERROR_SUCCESS)
		return false;

	CString name = m_adapter->name;
	for (PIP_ADAPTER_INFO pInfo = adapterInfo; pInfo != nullptr; pInfo = pInfo->Next)
	{
		if (name.Find(pInfo->AdapterName) != -1)
		{
			ip = pInfo->IpAddressList.IpAddress.String;
			mac = *(MacAddress*)pInfo->Address;
			gateway = pInfo->GatewayList.IpAddress.String;
			break;
		}
	}
	if (ip == "")
		return false;

	// fill variables
	m_selfIp = ip;
	m_selfMac = mac;
	m_selfGateway = gateway;

	return true;
}