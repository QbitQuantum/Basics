PortSet PortsManager::GetNowPorts()
{
	PortSet newPorts;

	PMIB_TCPTABLE pTcpTable;
	DWORD dwSize = 0;
	DWORD dwRetVal = 0;
	unsigned short *port_ptr;
	DWORD i;

	/* Get size required by GetTcpTable() */
	if (GetTcpTable(NULL, &dwSize, 0) == ERROR_INSUFFICIENT_BUFFER) {
		pTcpTable = (MIB_TCPTABLE *) malloc (dwSize);
	}

	/* Get actual data using GetTcpTable() */
	if ((dwRetVal = GetTcpTable(pTcpTable, &dwSize, 0)) == NO_ERROR) {
		if (pTcpTable->dwNumEntries > 0) {
			for (i=0; i<pTcpTable->dwNumEntries; i++) {
				//addr_ptr = (char *)&pTcpTable->table[i].dwLocalAddr;
				//port_ptr = (unsigned short *)&pTcpTable->table[i].dwLocalPort;
				//addr_ptr = (char *)&pTcpTable->table[i].dwRemoteAddr;
				port_ptr = (unsigned short *)&pTcpTable->table[i].dwRemotePort;
				DWORD state = pTcpTable->table[i].dwState;
				newPorts.insert(Port(*port_ptr, state));
			}
		}
	}
	free(pTcpTable);
	return newPorts;
}