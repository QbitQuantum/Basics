void MeetingConnImpl::run()
{
	Poco::Timespan span(2*1000);
	char buffer[1500*10] = {0};
	SocketAddress sender;
	Poco::Int32 n;
	m_recvLen = 0;
	memset(m_TempRecvBuf,0,sizeof(m_TempRecvBuf));
	//探测是否连接成功;
	Poco::Timespan spanTimeOut(10,0);
	Socket::SocketList readList;
	Socket::SocketList writeList;
	Socket::SocketList errList;

	Timestamp timeHeart;
	Timestamp timeTimeout;
	Timespan errorSpan(1000);
	span = Timespan(1000*100);

	writeList.push_back(*m_pSock);
	errList.push_back(*m_pSock);

	if(Socket::select(readList,writeList,errList,spanTimeOut))
	{
		if(writeList.size()>0)
		{
			m_bRawSockConnected = true;
			m_pIMeetingEvent->OnNetEvent(NET_EVENT_CONNECT_SUCCESS,"connect success");
			
		}
		else
		{
			//连接不上
			m_pIMeetingEvent->OnNetEvent(NET_EVENT_TIME_OUT,"connect login server time out");
			goto OnError;
		}
	}
	else
	{

		m_pIMeetingEvent->OnNetEvent(NET_EVENT_TIME_OUT,"connect login server time out");
		goto OnError;
	}

	if(m_bRawSockConnected)
	{
		//发送握手协议1
		char msg[512];
		sprintf(msg,"{\"cmd\":\"handSharke1\",\"cmdVar\":%d}\r\n",MeetingFrameImpl::GetInstance()->GetVersion());
		try
		{
			if(m_bRawSockConnected)
				m_pSock->sendBytes(msg,strlen(msg));
		}
		catch(NetException&)
		{
			m_bRawSockConnected = false;
			m_bStop = true;
			m_pIMeetingEvent->OnNetEvent(NET_EVENT_LOST_CONNECTION,"server has a error");
			goto OnError;
		}
	}

	
	m_recvLen = 0;
	m_lastTime = 0;

	while(!m_bStop &&m_bRawSockConnected)
	{
		char c = '\r';
		char c2 = '\n';
		if(!m_bStop && m_pSock->poll(errorSpan,Socket::SELECT_ERROR))
		{
			if(m_bHasLogined)
			{
				m_bRawSockConnected = false;
				m_pIMeetingEvent->OnNetEvent(NET_EVENT_LOST_CONNECTION,"Proxy Server Error");
			}
			goto OnError;
		}

		if(!m_bStop && m_pSock->poll(span, Socket::SELECT_READ))
		{
			try
			{
				if(m_pSock->available()<=0)
				{
					if(m_bHasLogined)
					{
						m_bRawSockConnected = false;
						m_pIMeetingEvent->OnNetEvent(NET_EVENT_LOST_CONNECTION,"Proxy Server Error");
					}
					goto OnError;
				}

				if(m_bStop)
				{
					m_bHasLogined = m_bLogicServerConnected = m_bRawSockConnected = false;
					return;
				}

				memset(buffer,0,sizeof(buffer));
				n = m_pSock->receiveBytes(buffer,sizeof(buffer));
				m_lastTime = Timestamp();
				if(n>0)
				{
					//切包，拼包
					ProcessRawCommand(buffer,n);
				}
				else
				{
					if(!m_bStop)
						m_pIMeetingEvent->OnNetEvent(NET_EVENT_LOST_CONNECTION,"lost connection");
					goto OnError;
				}
			}
			catch (Poco::Exception& exc)
			{
				std::cerr << "AA_proxy_Server: " << exc.displayText() << std::endl;
				if(!m_bStop)
					m_pIMeetingEvent->OnNetEvent(NET_EVENT_LOST_CONNECTION,"proxy server error");
				goto OnError;
				return;
			}
		}
		//一分钟发一次心跳
		if(timeHeart.elapsed()>30*1000*1000)
		{
			char *msg2="{\"cmd\":\"ping\"}\r\n";
			if(m_bLogicServerConnected)
				m_pSock->sendBytes(msg2,strlen(msg2));
			timeHeart = Timestamp();
		}
		// 70秒没有收到数据，掉线了;
		if(timeTimeout.elapsed() >30*1000*1000)
		{  
			if(m_lastTime.elapsed()>35*1000*1000)
			{
				m_pIMeetingEvent->OnNetEvent(NET_EVENT_LOST_CONNECTION,"lost connection");
				goto OnError;
			}
			timeTimeout = Timestamp();
		}

		if(m_bHasLogined == true && m_bLogicServerConnected == true)
		{
			//如果已经登录成功，检测缓冲区有没有要发送的数据，发送数据
			{
				FastMutex::ScopedLock autoLock(m_lock);
				while(m_sendBufList.size()>0)
				{
					char * strSend = m_sendBufList.front();
					if(m_pSock!=NULL)
					{
						m_pSock->sendBytes(strSend,strlen(strSend));
						m_sendBufList.pop();
						delete strSend;
					}
					else
					{
						break;
					}
					
				}
			}
		}
		else if(m_tryLoginCount<5)
		{
			//发送登录数据
			if(m_bLogicServerConnected == true)
			{
				if(m_tryLoginCount == 0)
				{
					m_pSock->sendBytes(m_strLogin,strlen(m_strLogin));
					m_tryLoginCount++;
					m_lastLoginTime = Timestamp();
				}
				else
				{
					if(m_lastLoginTime.elapsed() >1000*5*1000)
					{
						m_pSock->sendBytes(m_strLogin,strlen(m_strLogin));
						m_tryLoginCount++;
						m_lastLoginTime = Timestamp();
					}
				}
			}
			
		}
	}//end while

	//把没有发送的数据发送完
	{
		FastMutex::ScopedLock autoLock(m_lock);
		while(m_sendBufList.size()>0)
		{
			char * strSend = m_sendBufList.front();
			if(m_pSock!=NULL)
			{
				m_pSock->sendBytes(strSend,strlen(strSend));
				m_sendBufList.pop();
				delete strSend;
			}
			else
			{
				break;
			}

		}
	}

OnError:
	if(m_bLogicServerConnected && NULL != m_pSock)
	{
		m_pSock->shutdown();
	}
	m_bStop  = true;
	m_bHasLogined = false;
	m_bLogicServerConnected = m_bRawSockConnected= false;
	delete m_pSock;
	m_pSock = NULL;
}