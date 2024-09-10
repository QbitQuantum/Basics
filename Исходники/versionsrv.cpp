int main(int argc, char **argv) // ignore_convention
{
	NETADDR BindAddr;

	dbg_logger_stdout();
	net_init();

	mem_zero(&BindAddr, sizeof(BindAddr));
	BindAddr.type = NETTYPE_ALL;
	BindAddr.port = VERSIONSRV_PORT;
	if(!g_NetOp.Open(BindAddr, 0))
	{
		dbg_msg("mastersrv", "couldn't start network");
		return -1;
	}

	BuildPackets();

	ReadNews();
	ReadServerList();

	dbg_msg("versionsrv", "started");

	while(1)
	{
		g_NetOp.Update();

		// process packets
		CNetChunk Packet;
		while(g_NetOp.Recv(&Packet))
		{
			if(Packet.m_DataSize == sizeof(VERSIONSRV_GETVERSION) &&
				mem_comp(Packet.m_pData, VERSIONSRV_GETVERSION, sizeof(VERSIONSRV_GETVERSION)) == 0)
			{
				SendVer(&Packet.m_Address);

				char aAddrStr[NETADDR_MAXSTRSIZE];
				net_addr_str(&Packet.m_Address, aAddrStr, sizeof(aAddrStr), false);
				dbg_msg("versionsrv", "version request by %s", aAddrStr);
			}

			if(Packet.m_DataSize == sizeof(VERSIONSRV_GETNEWS) &&
				mem_comp(Packet.m_pData, VERSIONSRV_GETNEWS, sizeof(VERSIONSRV_GETNEWS)) == 0)
			{
				SendNews(&Packet.m_Address);
			}

			if(Packet.m_DataSize == sizeof(VERSIONSRV_GETMAPLIST) &&
				mem_comp(Packet.m_pData, VERSIONSRV_GETMAPLIST, sizeof(VERSIONSRV_GETMAPLIST)) == 0)
			{
				CNetChunk p;
				p.m_ClientID = -1;
				p.m_Address = Packet.m_Address;
				p.m_Flags = NETSENDFLAG_CONNLESS;

				for(int i = 0; i < m_NumPackets; i++)
				{
					p.m_DataSize = m_aPackets[i].m_Size;
					p.m_pData = &m_aPackets[i].m_Data;
					g_NetOp.Send(&p);
				}
			}

			if(m_ServerListLoaded &&
				Packet.m_DataSize == sizeof(VERSIONSRV_GETDDNETLIST) + 4 &&
				mem_comp(Packet.m_pData, VERSIONSRV_GETDDNETLIST, sizeof(VERSIONSRV_GETDDNETLIST)) == 0)
			{
				char aToken[4];
				mem_copy(aToken, (char*)Packet.m_pData+sizeof(VERSIONSRV_GETDDNETLIST), 4);

				SendServerList(&Packet.m_Address, aToken);
			}
		}

		// wait for input
		net_socket_read_wait(g_NetOp.m_Socket, 1000000);
	}

	return 0;
}