//recv线程需要负责网络检测，重连。
static void* recvTask(void* data)
{
	while (true)
	{
		if(g_NetworkStat == NetworkStat_NotConnect)
		{
			//发起网络连接
			if(connectToServer())
			{
				//连接成功，修改相应状态
				g_NetworkStat = NetworkStat_Connected;

				//recv线程初始化为check状态 
				g_RecvThreadStat = RecvThreadStat_Check;

				continue;
			}
			else
			{
				lfSleep(2000);
				continue;
			}
		}

		//if(g_RecvThreadStat == RecvThreadStat_Check)
		//{
		//	//通过select检测网络状态
		//	fd_set fdset;
		//	FD_ZERO(&fdset);
		//	FD_SET(cSocket.getSock(), &fdset);
		//	struct timeval timev;
		//	timev.tv_sec = 0;
		//	timev.tv_usec = 0;

		//	//非阻塞select 
		//	int ret = select(cSocket.getSock() + 1, &fdset, 0, 0, &timev);
		//	if(ret == 0)
		//	{
		//		//一切正常休息一下
		//		lfSleep(250);
		//	}
		//	else
		//	{
		//		//有recv fdset有返回，在没有发送请求包的情况下，只能是网络断掉了
		//		closeConnection();
		//		// 通知接收数据出错
		//		GlobalNetworkMsgDispacher::getMsgDispacher()->addPakage(new GlobalNetPackage(Type_Conncet_Err,NULL,NULL));
		//		continue;
		//	}
		//}
		//else if(g_RecvThreadStat == RecvThreadStat_Recv)
		{
			CCLog("recvTask : recv data .....");
			// 读取头部
			char* head = new char[sizeof(SPHead)];
			int l = cSocket.Recv(head,sizeof(SPHead),0);
			if ( l != sizeof(SPHead))
			{
				CCLog("recvTask : recv Head error , total length = %d, readed length = %d",sizeof(SPHead),l);

				// 通知接收数据出错
				if(g_RecvThreadStat == RecvThreadStat_Check)
				{
					CCLog("recvTask : recv Head error,g_RecvThreadStat == RecvThreadStat_Check");
					GlobalNetworkMsgDispacher::getMsgDispacher()->addPakage(new GlobalNetPackage(Type_Conncet_Err,NULL,NULL));
				}
				else
				{
					CCLog("recvTask : recv Head error,g_RecvThreadStat != RecvThreadStat_Check");
					GlobalNetworkMsgDispacher::getMsgDispacher()->addPakage(new GlobalNetPackage(Type_Recv_Err,NULL,NULL));
				}
				

				delete head;

				// 出问题了
				closeConnection();
				continue;
			}

			if (!isHeadValied((SPHead*)head))
			{
				CCLog("recvTask : recv Head is inValied");

				// 通知接收数据出错
				// 通知接收数据出错
				if(g_RecvThreadStat == RecvThreadStat_Check)
				{
					CCLog("recvTask : recv Head is inValied   g_RecvThreadStat == RecvThreadStat_Check");
					GlobalNetworkMsgDispacher::getMsgDispacher()->addPakage(new GlobalNetPackage(Type_Conncet_Err,NULL,NULL));
				}
				else
				{
					CCLog("recvTask : recv Head is inValied   g_RecvThreadStat != RecvThreadStat_Check");
					GlobalNetworkMsgDispacher::getMsgDispacher()->addPakage(new GlobalNetPackage(Type_Recv_Err,NULL,NULL));
				}

				delete head;

				//出问题了
				closeConnection();
				continue;
			}

			CCLog("recvTask : recv head success!");

			// 获取数据包
			int data_len = ntohl(((SPHead*)head)->data_len);
			char* body = new char[data_len];

			int l_body = cSocket.Recv(body,data_len,0);
			if ( l_body != data_len)
			{
				CCLog("recvTask : recv body error , total length = %d, readed length = %d",data_len,l_body);

				// 通知接收数据出错
				// 通知接收数据出错
				if(g_RecvThreadStat == RecvThreadStat_Check)
				{
					CCLog("recvTask : recv body error,g_RecvThreadStat == RecvThreadStat_Check");
					GlobalNetworkMsgDispacher::getMsgDispacher()->addPakage(new GlobalNetPackage(Type_Conncet_Err,NULL,NULL));
				}
				else
				{
					CCLog("recvTask : recv body error,g_RecvThreadStat != RecvThreadStat_Check");
					GlobalNetworkMsgDispacher::getMsgDispacher()->addPakage(new GlobalNetPackage(Type_Recv_Err,NULL,NULL));
				}


				delete body;
				delete head;

				//出问题了
				closeConnection();
				continue;
			}

			CCLog("recvTask : recv body success!");

			// 通知接收数据成功
			GlobalNetworkMsgDispacher::getMsgDispacher()->addPakage(new GlobalNetPackage(Type_RecvData,head,body));

			//修改标志
			g_RecvThreadStat = RecvThreadStat_Check;
		}
		/*else
		{
			CCAssert(false, "stat error");
			lfSleep(1000);
			continue;
		}*/
	}
	return 0;
	
}