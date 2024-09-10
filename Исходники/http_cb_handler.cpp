//-------------------------------------------------------------------------------------
int HTTPCBHandler::handleInputNotification(int fd)
{
	if(fd == *pEndPoint_)
	{
		u_int16_t port;
		u_int32_t addr;

		Network::EndPoint* newclient = pEndPoint_->accept(&port, &addr);

		if(newclient == NULL)
		{
			ERROR_MSG(fmt::format("HTTPCBHandler::handleInputNotification: accept is error:{}.\n", kbe_strerror()));
			return 0;
		}

		INFO_MSG(fmt::format("HTTPCBHandler:handleInputNotification: newclient = {}\n",
			newclient->c_str()));
		
		newclient->setnonblocking(true);
		CLIENT& client = clients_[*newclient];
		client.endpoint = KBEShared_ptr< Network::EndPoint >(newclient);
		client.state = 0;
		Loginapp::getSingleton().networkInterface().dispatcher().registerReadFileDescriptor(*newclient, this);
	}
	else
	{
		std::map< int, CLIENT >::iterator iter = clients_.find(fd);
		if(iter == clients_.end())
		{
			ERROR_MSG(fmt::format("HTTPCBHandler:handleInputNotification: fd({}) not found!\n",
				fd));
			return 0;
		}

		CLIENT& client = iter->second;
		Network::EndPoint* newclient = iter->second.endpoint.get();

		char buffer[1024];
		int len = newclient->recv(&buffer, 1024);

		if(len <= 0)
		{
			ERROR_MSG(fmt::format("HTTPCBHandler:handleInputNotification: recv error, newclient = {}, recv={}.\n",
				newclient->c_str(), len));
		
			if(len == 0)
			{
				Loginapp::getSingleton().networkInterface().dispatcher().deregisterReadFileDescriptor(*newclient);
				clients_.erase(iter);
			}
			return 0;
		}

		if(client.state == 1)
		{
			Loginapp::getSingleton().networkInterface().dispatcher().deregisterReadFileDescriptor(*newclient);
			clients_.erase(iter);
		}

		int type = 0;
		std::string s = buffer;
		
		std::string keys = "<policy-file-request/>";
		std::string::size_type fi0 = s.find(keys);
		if(fi0 != std::string::npos)
		{
			if(client.state != 1)
			{
				std::string response = "<?xml version='1.0'?><cross-domain-policy><allow-access-from domain=""*"" to-ports=""*"" /></cross-domain-policy>";
				iter->second.endpoint->send(response.c_str(), response.size());
				Loginapp::getSingleton().networkInterface().dispatcher().deregisterReadFileDescriptor(*newclient);
				clients_.erase(iter);
			}

			return 0;
		}

		keys = "accountactivate_";
		std::string::size_type fi1 = s.find(keys);
		if(fi1 == std::string::npos)
		{
			keys = "resetpassword_";
			fi1 = s.find(keys);
			if(fi1 == std::string::npos)
			{
				keys = "bindmail_";
				fi1 = s.find(keys);
				if(fi1 != std::string::npos)
				{
					type = 3;
				}
			}
			else
			{
				type = 2;
			}
		}
		else
		{
			type = 1;
		}

		std::string::size_type fi2 = s.find("?");
		std::string::size_type fi3 = s.find(" HTTP/");

		if(fi2 == std::string::npos || fi2 > fi3)
			fi2 = fi3;

		if(fi2 <= fi1)
		{
			return 0;
		}

		std::string code;
		if(fi1 != std::string::npos && fi2 != std::string::npos)
		{
			int ilen = keys.size();
			code.assign(s.c_str() + fi1 + ilen, fi2 - (fi1 + ilen));
		}

		client.state = 1;
		
		code = KBEngine::strutil::kbe_trim(code);

		if(code.size() > 0)
		{
			INFO_MSG(fmt::format("HTTPCBHandler:handleInputNotification: code = {}\n",
				code.c_str()));

			client.code = code;

			Components::COMPONENTS& cts = Components::getSingleton().getComponents(DBMGR_TYPE);
			Components::ComponentInfos* dbmgrinfos = NULL;

			if(cts.size() > 0)
				dbmgrinfos = &(*cts.begin());

			if(dbmgrinfos == NULL || dbmgrinfos->pChannel == NULL || dbmgrinfos->cid == 0)
			{
				return 0;
			}

			std::string hellomessage;

			if(type == 1)
			{
				// Ïòdbmgr¼¤»îÕËºÅ
				Network::Bundle* pBundle = Network::Bundle::ObjPool().createObject();
				(*pBundle).newMessage(DbmgrInterface::accountActivate);
				(*pBundle) << code;
				dbmgrinfos->pChannel->send(pBundle);

				hellomessage = g_kbeSrvConfig.emailAtivationInfo_.backlink_hello_message;
			}
			else if(type == 2)
			{
				std::string::size_type fi1 = s.find("password="******"&", fi1);

				std::string password;
				
				if(fi1 != std::string::npos && fi2 != std::string::npos)
				{
					client.state = 2;
					if(fi1 < fi2)
					{
						int ilen = strlen("password="******"username="******"&", fi1);

					std::string username;
					
					if(fi1 != std::string::npos && fi2 != std::string::npos)
					{
						if(fi1 < fi2)
						{
							int ilen = strlen("username="******"username="******" HTTP/");
				
				if(fi1 != std::string::npos && fi2 != std::string::npos)
				{
					if(fi1 < fi2)
					{
						int ilen = strlen("username="******"${backlink}", fmt::format("http://{}:{}/{}{}", 
					Loginapp::getSingleton().networkInterface().extaddr().ipAsString(),
					g_kbeSrvConfig.getLoginApp().http_cbport,
					keys,
					code));

				KBEngine::strutil::kbe_replace(hellomessage, "${code}", code);

				std::string response = fmt::format("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: {}\r\n\r\n{}", 
					hellomessage.size(), hellomessage);

				newclient->send(response.c_str(), response.size());
			}

			client.state = 2;
		}
		else
		{
			if(client.state != 2)
			{
				Loginapp::getSingleton().networkInterface().dispatcher().deregisterReadFileDescriptor(*newclient);
				clients_.erase(iter);
			}
		}
	}

	return 0;
}