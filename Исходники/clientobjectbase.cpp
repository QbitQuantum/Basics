//-------------------------------------------------------------------------------------
Mercury::Channel* ClientObjectBase::initLoginappChannel(std::string accountName, std::string passwd, std::string ip, KBEngine::uint32 port)
{
	Mercury::EndPoint* pEndpoint = new Mercury::EndPoint();
	
	pEndpoint->socket(SOCK_STREAM);
	if (!pEndpoint->good())
	{
		ERROR_MSG("ClientObjectBase::initLoginappChannel: couldn't create a socket\n");
		delete pEndpoint;
		return NULL;
	}
	

	u_int32_t address;
	pEndpoint->convertAddress(ip.c_str(), address);
	if(pEndpoint->connect(htons(port), address) == -1)
	{
		ERROR_MSG(boost::format("ClientObjectBase::initLoginappChannel: connect server is error(%1%)!\n") %
			kbe_strerror());

		delete pEndpoint;
		return NULL;
	}

	Mercury::Address addr(ip.c_str(), port);
	pEndpoint->addr(addr);

	pServerChannel_->endpoint(pEndpoint);
	pEndpoint->setnonblocking(true);
	pEndpoint->setnodelay(true);

	password_ = passwd;
	name_ = accountName;
	return pServerChannel_;
}