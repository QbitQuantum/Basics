void CNetLogViewer::Execute(void*)
{
TRY_CATCH

	/// Adding internal clients for tests
	/*{
		INetLogClient* newClient;
		tstring clientName;
		clientName = Format(_T("%s:%s"),"192.168.0.5","iexplore.exe");
		SYSTEMTIME sysTime = static_cast<SYSTEMTIME>(cDate().GetNow().AddCountDays(0));
		DATE date;
		SystemTimeToVariantTime(&sysTime,&date);
		CNetLogClient::CreateInstance(&newClient);
		newClient->put_RecentReply(date);
		newClient->put_Name(CComBSTR(clientName.c_str()));
		newClient->put_IP(CComBSTR("192.168.0.5"));
		m_clients[clientName] = newClient;
		OnClientFound(newClient);
	}
	{
		INetLogClient* newClient;
		tstring clientName;
		clientName = Format(_T("%s:%s"),"192.168.0.3","NWLTest.exe");
		SYSTEMTIME sysTime = static_cast<SYSTEMTIME>(cDate().GetNow().AddCountDays(1));
		DATE date;
		SystemTimeToVariantTime(&sysTime,&date);
		CNetLogClient::CreateInstance(&newClient);
		newClient->put_RecentReply(date);
		newClient->put_Name(CComBSTR(clientName.c_str()));
		newClient->put_IP(CComBSTR("192.168.0.3"));
		m_clients[clientName] = newClient;
		OnClientFound(newClient);
	}*/

	
	/// Last bCast send time
	cDate lastBCast;
	tstring fromIp;
	unsigned int fromPort;
	char buf[MAX_PATH + 1];
	buf[MAX_PATH] = 0;
	INetLogClient* newClient;
	tstring clientName;
	std::map<tstring, CComPtr<INetLogClient> >::iterator client;
	while(!Terminated())
	{
		/// Freing time quant
		/// Sleep is used instead of SwitchToThread(), cause it forces Dispatcher to switch context
		/// while SwitchToThread switches context only there are scheduled threads
		/// and whis is totally not what we want, cause it will result in 100% CPU usage
		Sleep(1); 	
		
		/// Sending broadcast request
		if (lastBCast < cDate().GetNow().AddMilliSecs(0 - REQUESTS_INTERVAL))
		{
			SendBroadCastRequest();
			lastBCast.GetNow();
			//(cMsgBoxLog()).Add(_MESSAGE_,"BCast sent");

			if (Terminated())
				break;
			/// Cleaning up timed out clients
			CleanUpTimedOutClients();
		}

		if (Terminated())
			break;
		/// Receiving alive replys from clients
		SUDPListenerMsg *msg;
		while (m_udpSocket.GetReadyDataCount())
		{
			memset(buf,0,MAX_PATH); /// TODO:remove
			if (SOCKET_ERROR == m_udpSocket.ReceiveFrom(fromIp, fromPort, buf, MAX_PATH))
			{
				Log.Add(MCSocketStreamException(_T("failed to m_udpSocket.ReceiveFrom")));
				break;
			}
			/// Creating client
			msg = reinterpret_cast<SUDPListenerMsg*>(buf);
			clientName = Format(_T("%s:%d at %s"), msg->m_data, msg->m_process, fromIp.c_str());
			client = m_clients.find(clientName);
			if (client != m_clients.end())
			{
				SYSTEMTIME sysTime = static_cast<SYSTEMTIME>(cDate().GetNow());
				DATE date;
				SystemTimeToVariantTime(&sysTime,&date);
				client->second->put_RecentReply(date);
				client->second->put_TCPPort(msg->m_tcpPort);
				//client
			} else
			{
				CNetLogClient::CreateInstance(&newClient);
				newClient->put_Name(CComBSTR(clientName.c_str()));
				newClient->put_IP(CComBSTR(fromIp.c_str()));
				newClient->put_TCPPort(msg->m_tcpPort);
				m_clients[clientName] = newClient;
				OnClientFound(newClient);
			}
		}
	}

CATCH_LOG()
}