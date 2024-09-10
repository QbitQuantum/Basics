void CConnectRemoteMachineWindow::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CguiconsoleDlg* dlg = static_cast<CguiconsoleDlg*>(theApp.m_pMainWnd);
	byte ips[4];

	if (0 == m_ip.GetAddress(ips[0],ips[1],ips[2],ips[3]))
	{
		AfxMessageBox(L"address is error!");
		return;
	}
	
	char strip[256];
	sprintf_s(strip, 256, "%d.%d.%d.%d", ips[0],ips[1],ips[2],ips[3]);
	
	KBEngine::u_int16_t port = 0;
	CString sport;
	m_port.GetWindowTextW(sport);
	char* csport = KBEngine::strutil::wchar2char(sport.GetBuffer(0));
	port = atoi(csport);
	std::string command = strip;
	command += ":";
	command += csport;
	free(csport);

	KBEngine::Mercury::EndPoint* endpoint = new KBEngine::Mercury::EndPoint();

	KBEngine::u_int32_t address;
	endpoint->convertAddress(strip, address);
	KBEngine::Mercury::Address addr(address, htons(port));

	if(addr.ip == 0)
	{
		::AfxMessageBox(L"address is error!");
		delete endpoint;
		return;
	}

	endpoint->socket(SOCK_STREAM);
	if (!endpoint->good())
	{
		AfxMessageBox(L"couldn't create a socket\n");
		delete endpoint;
		return;
	}

	endpoint->addr(addr);
	if(endpoint->connect(addr.port, addr.ip) == -1)
	{
		CString err;
		err.Format(L"connect server is error! %d", ::WSAGetLastError());
		AfxMessageBox(err);
		delete endpoint;
		return;
	}

	endpoint->setnonblocking(false);
	int8 findComponentTypes[] = {MESSAGELOG_TYPE, RESOURCEMGR_TYPE, BASEAPP_TYPE, CELLAPP_TYPE, BASEAPPMGR_TYPE, CELLAPPMGR_TYPE, LOGINAPP_TYPE, DBMGR_TYPE, BOTS_TYPE, UNKNOWN_COMPONENT_TYPE};
	int ifind = 0;

	while(true)
	{
		int8 findComponentType = findComponentTypes[ifind++];
		if(findComponentType == UNKNOWN_COMPONENT_TYPE)
		{
			//INFO_MSG("Componentbridge::process: not found %s, try again...\n",
			//	COMPONENT_NAME_EX(findComponentType));
			break;
		}

		KBEngine::Mercury::Bundle bhandler;
		bhandler.newMessage(KBEngine::MachineInterface::onFindInterfaceAddr);

		KBEngine::MachineInterface::onFindInterfaceAddrArgs7::staticAddToBundle(bhandler, KBEngine::getUserUID(), KBEngine::getUsername(), 
			CONSOLE_TYPE, g_componentID, findComponentType, 0, 0);

		bhandler.send(*endpoint);

		KBEngine::Mercury::TCPPacket packet;
		packet.resize(65535);

		endpoint->setnonblocking(true);
		KBEngine::sleep(300);
		packet.wpos(endpoint->recv(packet.data(), 65535));

		while(packet.opsize() > 0)
		{
			MachineInterface::onBroadcastInterfaceArgs22 args;
			
			try
			{
				args.createFromStream(packet);
			}catch(MemoryStreamException &)
			{
				goto END;
			}

			INFO_MSG(boost::format("CConnectRemoteMachineWindow::OnBnClickedOk: found %1%, addr:%2%:%3%\n") %
				COMPONENT_NAME_EX((COMPONENT_TYPE)args.componentType) % inet_ntoa((struct in_addr&)args.intaddr) % ntohs(args.intport));

			Components::getSingleton().addComponent(args.uid, args.username.c_str(), 
				(KBEngine::COMPONENT_TYPE)args.componentType, args.componentID, args.globalorderid, args.grouporderid, 
				args.intaddr, args.intport, args.extaddr, args.extport, args.extaddrEx, args.pid, args.cpu, args.mem, args.usedmem, 
				args.extradata, args.extradata1, args.extradata2, args.extradata3);

		}
	}
END:
	dlg->updateTree();
	delete endpoint;
	wchar_t* wcommand = KBEngine::strutil::char2wchar(command.c_str());
	bool found = false;
	std::deque<CString>::iterator iter = m_historyCommand.begin();
	for(; iter != m_historyCommand.end(); iter++)
	{
		if((*iter) == wcommand)
		{
			found = true;
			break;
		}
	}
	
	if(!found)
	{
		m_historyCommand.push_front(wcommand);
		if(m_historyCommand.size() > 10)
			m_historyCommand.pop_back();

		saveHistory();
	}

	free(wcommand);

	OnOK(); 
}