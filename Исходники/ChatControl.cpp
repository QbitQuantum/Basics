void CChatControl::GetConnect()
{
	// Test for internet connection 
	if(!m_autPrefs->GetLanMode() && !m_InetTested)
	{
		CWinThread* pThread = AfxBeginThread(TestInetThread, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
		AssignThreadToCPU(pThread, CPU_0);
		pThread->ResumeThread();

		return;
	}

	if(m_autPrefs->GetLanMode())
	{
		if(m_pPrefs->m_InternalIRC)
		{
			CString Host = m_pPrefs->m_InternalIRCAddr;

			int pos = Host.Find(":");

			if(pos != -1)
				AddServer( Host.Left(Host.Find(":")), atoi(Host.Mid(Host.Find(":") + 1)));
			else
				AddServer(m_pPrefs->m_InternalIRCAddr, 6667);
		}

		return;
	}

	// If its for chat
	if(m_pDoc->m_pViewChat)
		if(m_pPrefs->m_PrefNet == "GnuDefault")
		{
			AddServer("irc.freenode.net", 6667);
			return;
		}
			

	// Connect to random server on default network
	for(int i = 0; i < m_pPrefs->m_ChatNets.size(); i++)		
		if(m_pPrefs->m_ChatNets[i].Name == m_pPrefs->m_PrefNet)
			if(m_pPrefs->m_ChatNets[i].Servers.size())
			{
				int servpos = rand() % m_pPrefs->m_ChatNets[i].Servers.size() + 0;
				CString Parse = m_pPrefs->m_ChatNets[i].Servers[servpos];
				
				// Take first server from list, and move it to the back
				//pPrefs->m_ChatNets[i].Servers.erase( pPrefs->m_ChatNets[i].Servers.begin() );
				//pPrefs->m_ChatNets[i].Servers.push_back(Parse);
		
				int colon = Parse.Find( _T(":") );

				if(colon != -1)
				{
					std::vector<UINT> PortList;

					CString Server   = Parse.Left(colon);
					CString PortString = Parse.Mid(colon + 1) + ",";
					
					int pos = 0;
					while(PortString.Find( _T(","), pos) != -1)
					{
						UINT port = atoi(PortString.Mid(pos, PortString.Find( _T(","), pos) - pos));
						PortList.push_back(port);

						pos = PortString.Find( _T(","), pos) + 1;
					}

					if(PortList.size())
					{	
						int portpos = rand() % PortList.size() + 0;
						AddServer(Server, PortList[portpos]);

						return;
					}
				}
			}
}