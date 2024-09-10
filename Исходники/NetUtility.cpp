	bool CheckNetworkAlive()
	{
		bool bRet = false;

		DWORD dwTableSize = 0;
		PMIB_IFTABLE lpTable = NULL;

		// Get struct size
		if (ERROR_INSUFFICIENT_BUFFER != GetIfTable(NULL, &dwTableSize, FALSE))
		{
			return bRet;
		}

		// Allocate memory
		lpTable = (PMIB_IFTABLE) new char[dwTableSize];
		if (NULL == lpTable)
		{
			return bRet;
		}

		// Get Info
		if (ERROR_SUCCESS != GetIfTable(lpTable, &dwTableSize, FALSE))
		{
			delete [] lpTable;
			return bRet;
		}

		for (DWORD i=0; i<lpTable->dwNumEntries; ++i)
		{
			if(( lpTable->table[i].dwType == MIB_IF_TYPE_ETHERNET || 
				lpTable->table[i].dwType == MIB_IF_TYPE_PPP) && 
				( lpTable->table[i].dwOperStatus == MIB_IF_OPER_STATUS_CONNECTED ||
				lpTable->table[i].dwOperStatus ==  MIB_IF_OPER_STATUS_OPERATIONAL))
			{
				if(IsIPAvailable())
				{
					bRet = true;
					break;
				}
			}
		}

		if (NULL != lpTable)
		{
			delete [] lpTable;
		}

		return bRet;
	}