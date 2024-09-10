void CStartServerWindow::OnBnClickedButton2()
{
	CString s;

	if(m_layoutlist.GetCurSel() < 0 || m_layoutlist.GetCurSel() > m_layoutlist.GetCount())
	{
		::AfxMessageBox(L"please select a layout!");
		return;
	}

	m_layoutlist.GetLBText(m_layoutlist.GetCurSel(), s);

	char* cs = KBEngine::strutil::wchar2char(s.GetBuffer(0));
	KBEUnordered_map< std::string, std::vector<CStartServerWindow::LAYOUT_ITEM> >::iterator iter = 
		layouts_.find(cs);

	free(cs);

	if(iter == layouts_.end())
	{
		::AfxMessageBox(L"please select a layout!");
		return;
	}

	std::vector<CStartServerWindow::LAYOUT_ITEM>::iterator iter1 = iter->second.begin();
	for(; iter1 != iter->second.end(); iter1++)
	{
		LAYOUT_ITEM& item = (*iter1);

		KBEngine::COMPONENT_TYPE ctype = KBEngine::ComponentName2ComponentType(item.componentName.c_str());

		std::vector<std::string> vec;
		KBEngine::strutil::kbe_split(item.addr, ':', vec);
		if(vec.size() != 2)
		{
			continue;
		}

		KBEngine::Mercury::EndPoint* endpoint = new KBEngine::Mercury::EndPoint();
		
		KBEngine::u_int32_t address;
		endpoint->convertAddress(vec[0].c_str(), address);
		KBEngine::Mercury::Address addr(address, htons(atoi(vec[1].c_str())));

		if(addr.ip == 0)
		{
			::AfxMessageBox(L"address is error!");
			delete endpoint;
			continue;
		}

		endpoint->socket(SOCK_STREAM);
		if (!endpoint->good())
		{
			AfxMessageBox(L"couldn't create a socket\n");
			delete endpoint;
			continue;
		}

		endpoint->addr(addr);
		if(endpoint->connect(addr.port, addr.ip) == -1)
		{
			CString err;
			err.Format(L"connect server is error! %d", ::WSAGetLastError());
			AfxMessageBox(err);
			delete endpoint;
			continue;
		}
		
		endpoint->setnonblocking(true);

		KBEngine::Mercury::Bundle bundle;
		bundle.newMessage(KBEngine::MachineInterface::startserver);
		bundle << KBEngine::getUserUID();
		bundle << ctype;
		bundle.send(*endpoint);

		KBEngine::Mercury::TCPPacket packet;
		packet.resize(1024);

		fd_set	fds;
		struct timeval tv = { 0, 1000000 }; // 1000ms

		FD_ZERO( &fds );
		FD_SET((int)(*endpoint), &fds);
		
		int selgot = select((*endpoint)+1, &fds, NULL, NULL, &tv);
		if(selgot == 0)
		{
			delete endpoint;
			continue;	// 超时可能对方繁忙
		}
		else if(selgot == -1)
		{
			delete endpoint;
			continue;
		}
		else
		{
			endpoint->recv(packet.data(), 1024);
		}

		bool success = true;
		packet << success;

		if(success)
		{
			for(int row = 0; row < m_list.GetItemCount(); row++)
			{
				CString name = m_list.GetItemText(row, 0);
				CString addr = m_list.GetItemText(row, 1); 
				CString running = m_list.GetItemText(row, 2); 

				char* cs1 = KBEngine::strutil::wchar2char(name.GetBuffer(0));
				char* cs2 = KBEngine::strutil::wchar2char(addr.GetBuffer(0));

				if(item.componentName == cs1 && item.addr == cs2 && running == L"false")
				{
					free(cs1);
					free(cs2);
					m_list.SetItemText(row, 2, L"true");
					break;
				}

				free(cs1);
				free(cs2);
			}
		}

		delete endpoint;
	}
}