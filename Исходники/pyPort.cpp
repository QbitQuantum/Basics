list GetConns()
{
	DWORD bufsize  = 0;

	list l;

	std::vector<MIB_TCPROW_OWNER_PID>  TCPtables;
	std::vector<MIB_UDPROW_OWNER_PID>  UDPtables;

	DWORD ret= GetExtendedTcpTable(0, &bufsize, FALSE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0);
	char *buf = new char[bufsize];
	ret = GetExtendedTcpTable(buf, &bufsize, FALSE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0);
	if(ret == NO_ERROR )
	{
		MIB_TCPTABLE_OWNER_PID *pTCPTable = (MIB_TCPTABLE_OWNER_PID *)buf;
		TCPtables.assign(pTCPTable->table, pTCPTable->table+pTCPTable->dwNumEntries);

	}

	delete [] buf;

	bufsize = 0;
	ret= GetExtendedUdpTable(0, &bufsize, FALSE, AF_INET, UDP_TABLE_OWNER_PID, 0);
	buf = new char[bufsize];
	ret = GetExtendedUdpTable(buf, &bufsize, FALSE, AF_INET, UDP_TABLE_OWNER_PID, 0);
	if(ret == NO_ERROR )
	{
		MIB_UDPTABLE_OWNER_PID *pUDPTable = (MIB_UDPTABLE_OWNER_PID *)buf;
		UDPtables.assign(pUDPTable->table, pUDPTable->table+pUDPTable->dwNumEntries);

	}



	delete [] buf;
	
	for (DWORD a=0; a<TCPtables.size(); a++)
	{
		TCPConn Conn;
		MIB_TCPROW_OWNER_PID & row = TCPtables[a];
		Conn.dwLocalAddr = row.dwLocalAddr;
		Conn.dwLocalPort = ntohs((u_short)row.dwLocalPort);
		Conn.dwOwningPid = row.dwOwningPid;
		Conn.dwRemoteAddr = row.dwRemoteAddr;
		Conn.dwRemotePort = ntohs((u_short)row.dwRemotePort);
		Conn.State =(TCPSTATE) row.dwState;
		Conn.Type = L"tcp";
		l.append( object(Conn) );
	}

	return l;

}