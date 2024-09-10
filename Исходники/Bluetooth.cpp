int RhoBluetoothManager::DiscoverDevices() {
	LOG(INFO)  + "RhoBluetoothManager::DiscoverDevices() START";
	WSAQUERYSET		wsaq;
	HANDLE			hLookup;
	RhoDeviceList *	tempDevice;

	union {
		CHAR buf[5000];
		double __unused;	// ensure proper alignment
	};

	LPWSAQUERYSET pwsaResults = (LPWSAQUERYSET) buf;
	DWORD dwSize  = sizeof(buf);
	BOOL bHaveName;

	ZeroMemory(&wsaq, sizeof(wsaq));
	wsaq.dwSize = sizeof(wsaq);
	wsaq.dwNameSpace = NS_BTH;
	wsaq.lpcsaBuffer = NULL;

	if (ERROR_SUCCESS != WSALookupServiceBegin (&wsaq, LUP_CONTAINERS, &hLookup))
	{
		LOG(INFO)  + "RhoBluetoothManager::DiscoverDevices() return ERROR";
		return WSAGetLastError();
	}

	ZeroMemory(pwsaResults, sizeof(WSAQUERYSET));
	pwsaResults->dwSize = sizeof(WSAQUERYSET);
	pwsaResults->dwNameSpace = NS_BTH;
	pwsaResults->lpBlob = NULL;

	if(m_pStart)
	{
		for(m_pCurrentDevice=m_pStart;m_pCurrentDevice;)
		{
			RhoDeviceList *temp=m_pCurrentDevice;
			m_pCurrentDevice=m_pCurrentDevice->NextDevice;
			free(temp);
		}
	}
	m_pEnd=m_pStart=NULL;
	m_iNumDevices=0;
	while (true)
	{	
		if(WSALookupServiceNext (hLookup, LUP_RETURN_NAME | LUP_RETURN_ADDR, &dwSize, pwsaResults)!=ERROR_SUCCESS)
			break;
		ASSERT (pwsaResults->dwNumberOfCsAddrs == 1);
		//Populate the link list		
		tempDevice=(RhoDeviceList*)malloc(sizeof(RhoDeviceList));
		tempDevice->NextDevice=NULL;
		if(m_pStart==NULL)
		{
			m_pStart = tempDevice;
			m_pEnd=m_pStart;
		}
		else
		{
			m_pEnd->NextDevice =tempDevice;
			m_pEnd=tempDevice;
		}
		m_iNumDevices++;
		m_pEnd->bthAddress = ((SOCKADDR_BTH *)pwsaResults->lpcsaBuffer->RemoteAddr.lpSockaddr)->btAddr;
		bHaveName = pwsaResults->lpszServiceInstanceName && *(pwsaResults->lpszServiceInstanceName);
		//If device name is available, add to node
		StringCchPrintf(m_pEnd->bthName, ARRAYSIZE(m_pEnd->bthName),L"%s",bHaveName ? pwsaResults->lpszServiceInstanceName : L"");
		{
			char name[1024];
			WideCharToMultiByte(CP_UTF8, 0, m_pEnd->bthName, -1, name, 1024, 0, 0);
			LOG(INFO)  + "RhoBluetoothManager::DiscoverDevices() FOUND = "+name;
		}
	}

	WSALookupServiceEnd(hLookup);
	LOG(INFO)  + "RhoBluetoothManager::DiscoverDevices() FINISH";
	//	LeaveCriticalSection(&criticalSection);
	return 0;
}