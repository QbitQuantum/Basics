void PortCache::RebuildUdpTable()
{
	// Clear the table
	//RtlZeroMemory(_udpPortTable, sizeof(_udpPortTable));
	_mapUdpPortTableEx.clear();

	DWORD dwRetValue = NO_ERROR;
	DWORD dwBufferSize = 0;

	//解释如同RebuildTcpTable
	PMIB_UDPTABLE_OWNER_PID pTable = NULL;
	dwRetValue = GetExtendedUdpTable(NULL, &dwBufferSize,
		FALSE, AF_INET, UDP_TABLE_OWNER_PID, 0);
	if (dwRetValue != ERROR_INSUFFICIENT_BUFFER)
	{
		printf("Failed to snapshot UDP endpoints.\n");
		return;
	}

	//解释如同RebuildTcpTable
	pTable = (PMIB_UDPTABLE_OWNER_PID)HeapAlloc(GetProcessHeap(), 0, dwBufferSize);
	dwRetValue = GetExtendedUdpTable(pTable, &dwBufferSize,
		FALSE, AF_INET, UDP_TABLE_OWNER_PID, 0);

	if (dwRetValue != NO_ERROR)
	{
		printf("Failed to snapshot UDP endpoints.\n");
		HeapFree(GetProcessHeap(), 0, pTable);
		return;
	}

	// Rebuild the table
	for (unsigned int i = 0; i < pTable->dwNumEntries; i++)
	{
		int nTemp = ntohs((unsigned short)pTable->table[i].dwLocalPort);
		//_udpPortTable[nTemp] =
		//	pTable->table[i].dwOwningPid;
		_mapUdpPortTableEx[nTemp] = pTable->table[i];
	}
	HeapFree(GetProcessHeap(), 0, pTable);
}