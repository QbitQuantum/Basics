	bool CServerSocket::ActiveStart()
	{
		HANDLE hIOCPHandle;
		sockaddr_in addr;
		m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE,0,0,0);
		if(m_hIOCP!=0)
		{
			m_IOCPSOCKET.socket = WSASocket(PF_INET,SOCK_STREAM,IPPROTO_IP,NULL,0,WSA_FLAG_OVERLAPPED);
			if(m_IOCPSOCKET.socket != INVALID_SOCKET)
			{
				memset(&addr,0,sizeof(sockaddr_in));
				addr.sin_family = PF_INET;
				if(strcmp(m_IOCPSOCKET.ip,"0.0.0.0")==0)
				{
					addr.sin_addr.S_un.S_addr = INADDR_ANY;

				}
				else
				{
					addr.sin_addr.S_un.S_addr = inet_addr(m_IOCPSOCKET.ip);
				}
				WSAHtons(m_IOCPSOCKET.socket,m_IOCPSOCKET.port,&addr.sin_port);
				//°ó¶¨Socket
				if(bind(m_IOCPSOCKET.socket,(sockaddr*)&addr,sizeof(sockaddr_in))==0)
				{
					m_AcceptThread = new CAcceptThread(this);
					m_AcceptThread->Resume();
					for (int i = 0 ;i<= m_iWorkThreadCount ;i++)
					{
						m_WorkThread[i] = new CWorkThread(this,false);
					}
					return true;

				}
				else
				{
					this->OnError(NULL,GetLastError());
					closesocket(m_IOCPSOCKET.socket);
					m_IOCPSOCKET.socket = INVALID_SOCKET;
				}
			}//endif
			else
			{
				OnError(NULL,WSAGetLastError());			
				hIOCPHandle = m_hIOCP;
				m_hIOCP = 0 ;
				CloseHandle(m_hIOCP);
			}
		}
		else
			OnError(NULL,GetLastError());
			return false;
	}