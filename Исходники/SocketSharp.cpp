//接收完成函数
bool CServerSocketItem::OnRecvCompleted(COverLappedRecv * pOverLappedRecv, DWORD dwThancferred)
{
	//效验数据
	ASSERT(m_bRecvIng==true);

	//设置变量
	m_bRecvIng=false;
	m_dwRecvTickCount=GetTickCount();

	//判断关闭
	if (m_hSocket==INVALID_SOCKET)
	{
		CloseSocket(m_wRountID);
		return true;
	}

	//接收数据
	int iRetCode=recv(m_hSocket,(char *)m_cbRecvBuf+m_wRecvSize,sizeof(m_cbRecvBuf)-m_wRecvSize,0);
	if (iRetCode<=0)
	{
		CloseSocket(m_wRountID);
		return true;
	}

	//接收完成
	m_wRecvSize+=iRetCode;
	BYTE cbBuffer[SOCKET_BUFFER];
	CMD_Head * pHead=(CMD_Head *)m_cbRecvBuf;

	//处理数据
	try
	{
		while (m_wRecvSize>=sizeof(CMD_Head))
		{
			//效验数据
			WORD wPacketSize=pHead->CmdInfo.wPacketSize;
			if (wPacketSize>SOCKET_BUFFER) throw TEXT("数据包超长");
			if (wPacketSize<sizeof(CMD_Head)) throw TEXT("数据包非法");
			if (pHead->CmdInfo.cbVersion!=SOCKET_VER) throw TEXT("数据包版本错误");
			if (m_wRecvSize<wPacketSize) break;

			//提取数据
			CopyMemory(cbBuffer,m_cbRecvBuf,wPacketSize);
			WORD wRealySize=CrevasseBuffer(cbBuffer,wPacketSize);
			ASSERT(wRealySize>=sizeof(CMD_Head));
			m_dwRecvPacketCount++;

			//解释数据
			WORD wDataSize=wRealySize-sizeof(CMD_Head);
			void * pDataBuffer=cbBuffer+sizeof(CMD_Head);
			CMD_Command Command=((CMD_Head *)cbBuffer)->CommandInfo;

			//内核命令
			if (Command.wMainCmdID==MDM_KN_COMMAND)
			{
				switch (Command.wSubCmdID)
				{
				case SUB_KN_DETECT_SOCKET:	//网络检测
					{
						break;
					}
				default: throw TEXT("非法命令码");
				}
			}
			else 
			{
				//消息处理
				m_pIServerSocketItemSink->OnSocketReadEvent(Command,pDataBuffer,wDataSize,this);			
			}

			//删除缓存数据
			m_wRecvSize-=wPacketSize;
			MoveMemory(m_cbRecvBuf,m_cbRecvBuf+wPacketSize,m_wRecvSize);
		}
	}
	catch (...)
	{ 
		CloseSocket(m_wRountID);
		return false;
	}

	return RecvData();
}