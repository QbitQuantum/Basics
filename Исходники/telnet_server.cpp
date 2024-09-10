//-------------------------------------------------------------------------------------
int	TelnetServer::handleInputNotification(int fd)
{
	KBE_ASSERT(listener_ == fd);

	int tickcount = 0;

	while(tickcount ++ < 1024)
	{
		Network::EndPoint* pNewEndPoint = listener_.accept();
		if(pNewEndPoint == NULL){

			if(tickcount == 1)
			{
				WARNING_MSG(fmt::format("TelnetServer::handleInputNotification: accept endpoint({}) {}!\n",
					 fd, kbe_strerror()));
			}

			break;
		}
		else
		{
			TelnetHandler* pTelnetHandler = new TelnetHandler(pNewEndPoint, this, pNetworkInterface_, passwd_.size() > 0 ? 
				TelnetHandler::TELNET_STATE_PASSWD : (TelnetHandler::TELNET_STATE)this->deflayer());

			if(!pDispatcher_->registerReadFileDescriptor((*pNewEndPoint), pTelnetHandler))
			{
				ERROR_MSG(fmt::format("TelnetServer::start:: registerReadFileDescriptor(pTelnetHandler) is failed! addr={}\n", 
					pNewEndPoint->c_str()));
				
				delete pTelnetHandler;
				continue;
			}

			INFO_MSG(fmt::format("TelnetServer::handleInputNotification: new handler({})!\n",
				pNewEndPoint->c_str()));

			handlers_[(*pNewEndPoint)].reset(pTelnetHandler);

			std::string s;

			if(passwd_.size() > 0)
			{
				s = "password:";
			}
			else
			{
				s = pTelnetHandler->getWelcome();
			}

			pNewEndPoint->send(s.c_str(), (int)s.size());
		}
	}

	return 0;
}