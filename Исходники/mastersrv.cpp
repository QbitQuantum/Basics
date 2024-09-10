int main(int argc, char **argv) // ignore_convention
{
	int64 LastBuild = 0;
	NETADDR BindAddr;

	dbg_logger_stdout();
	net_init();

	mem_zero(&BindAddr, sizeof(BindAddr));
	BindAddr.port = MASTERSERVER_PORT;
		
	m_NetOp.Open(BindAddr, 0);

	BindAddr.port = MASTERSERVER_PORT+1;
	m_NetChecker.Open(BindAddr, 0);
	// TODO: check socket for errors
	
	//mem_copy(data.header, SERVERBROWSE_LIST, sizeof(SERVERBROWSE_LIST));
	mem_copy(m_CountData.m_Header, SERVERBROWSE_COUNT, sizeof(SERVERBROWSE_COUNT));
	
	dbg_msg("mastersrv", "started");
	
	while(1)
	{
		m_NetOp.Update();
		m_NetChecker.Update();
		
		// process m_aPackets
		CNetChunk Packet;
		while(m_NetOp.Recv(&Packet))
		{
			if(Packet.m_DataSize == sizeof(SERVERBROWSE_HEARTBEAT)+2 &&
				mem_comp(Packet.m_pData, SERVERBROWSE_HEARTBEAT, sizeof(SERVERBROWSE_HEARTBEAT)) == 0)
			{
				NETADDR Alt;
				unsigned char *d = (unsigned char *)Packet.m_pData;
				Alt = Packet.m_Address;
				Alt.port =
					(d[sizeof(SERVERBROWSE_HEARTBEAT)]<<8) |
					d[sizeof(SERVERBROWSE_HEARTBEAT)+1];
				
				// add it
				AddCheckserver(&Packet.m_Address, &Alt);
			}
			else if(Packet.m_DataSize == sizeof(SERVERBROWSE_GETCOUNT) &&
				mem_comp(Packet.m_pData, SERVERBROWSE_GETCOUNT, sizeof(SERVERBROWSE_GETCOUNT)) == 0)
			{
				dbg_msg("mastersrv", "count requested, responding with %d", m_NumServers);
				
				CNetChunk p;
				p.m_ClientID = -1;
				p.m_Address = Packet.m_Address;
				p.m_Flags = NETSENDFLAG_CONNLESS;
				p.m_DataSize = sizeof(m_CountData);
				p.m_pData = &m_CountData;
				m_CountData.m_High = (m_NumServers>>8)&0xff;
				m_CountData.m_Low = m_NumServers&0xff;
				m_NetOp.Send(&p);
			}
			else if(Packet.m_DataSize == sizeof(SERVERBROWSE_GETLIST) &&
				mem_comp(Packet.m_pData, SERVERBROWSE_GETLIST, sizeof(SERVERBROWSE_GETLIST)) == 0)
			{
				// someone requested the list
				dbg_msg("mastersrv", "requested, responding with %d m_aServers", m_NumServers);
				CNetChunk p;
				p.m_ClientID = -1;
				p.m_Address = Packet.m_Address;
				p.m_Flags = NETSENDFLAG_CONNLESS;
				
				for(int i = 0; i < m_NumPackets; i++)
				{
					p.m_DataSize = m_aPackets[i].m_Size;
					p.m_pData = &m_aPackets[i].m_Data;
					m_NetOp.Send(&p);
				}
			}
		}