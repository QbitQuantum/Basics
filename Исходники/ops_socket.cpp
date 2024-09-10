bool Socket::init(const char *ip, unsigned int port, int type, bool block)
{
	int optval = 1;
	struct sockaddr_in addr;
	socklen_t addrLen;

	if  ( (this->fd = socket(AF_INET, type, 0)) == -1 ) 
	{   
		KY_LOG_ERROR("socket error, errno(%d)", errno);
		return false;
	}   

	// SO_REUSEADDR 允许在bind()过程中本地地址可重复使用
	if ( !setSockOpt(this->fd, SOL_SOCKET, SO_REUSEADDR, (void *)&optval, sizeof(optval)) )
	{
		return false;
	}

	if ( block == false )
	{
		if ( this->setNonblock() == false )
		{
			return false;
		}
	}

	Socket::initSockAddr( addr, ip, port );

	if( bind(this->fd, (struct sockaddr *)&addr, sizeof(addr)) == -1 )
	{
		KY_LOG_ERROR("bind error, errno(%d)", errno);
		return false;
	}

	if ( port == SOCKET_PORT_ANY )
	{
		addrLen = sizeof(addr);
		// 如果端口为ANY，则获取系统所分配的端口
		getsockname(this->fd, (struct sockaddr *)&(addr), &addrLen);
	}

	//snprintf(this->ip, "%s", ip);
	this->saveLocal( addr );
	return true;
}