void CIOCPServer::HandleIO(DWORD dwKey, CIOCPBuffer *pBuffer, DWORD dwTrans, int nError)
{
	CIOCPContext *pContext = (CIOCPContext *)dwKey;

#ifdef _DEBUG
	//	::OutputDebugString("	HandleIO... \n");
#endif // _DEBUG
	
	// 1）首先减少套节字上的未决I/O计数
	if(pContext != NULL)
	{
		::EnterCriticalSection(&pContext->Lock);
		
		if(pBuffer->nOperation == OP_READ)
			pContext->nOutstandingRecv --;
		else if(pBuffer->nOperation == OP_WRITE)
			pContext->nOutstandingSend --;
		
		::LeaveCriticalSection(&pContext->Lock);
		
		// 2）检查套节字是否已经被我们关闭
		if(pContext->bClosing) 
		{
#ifdef _DEBUG
			::OutputDebugString(" pContext->bClosing 检查到套节字已经被我们关闭 \n");
#endif // _DEBUG
			if(pContext->nOutstandingRecv == 0 && pContext->nOutstandingSend == 0)
			{		
				ReleaseContext(pContext);
			}
			// 释放已关闭套节字的未决I/O
			ReleaseBuffer(pBuffer);	
			return;
		}
	}
	else
	{
		RemovePendingAccept(pBuffer);
#ifdef _DEBUG
			::OutputDebugString("RemovePendingAccept	检查到套节字连接超时未完成被我们关闭 \n");
#endif // _DEBUG
		
	}

	// 3）检查套节字上发生的错误，如果有的话，通知用户，然后关闭套节字
	if(nError != NO_ERROR)
	{
		if(pBuffer->nOperation != OP_ACCEPT)
		{
			OnConnectionError(pContext, pBuffer, nError);
			CloseAConnection(pContext);
			if(pContext->nOutstandingRecv == 0 && pContext->nOutstandingSend == 0)
			{		
				ReleaseContext(pContext);
			}
#ifdef _DEBUG
			::OutputDebugString("nError	非OP_ACCEPT检查到客户套节字上发生错误 \n");
#endif // _DEBUG
		}
		else // 在监听套节字上发生错误，也就是监听套节字处理的客户出错了
		{
			// 客户端出错，释放I/O缓冲区
			if(pBuffer->sClient != INVALID_SOCKET)
			{
				::closesocket(pBuffer->sClient);
				pBuffer->sClient = INVALID_SOCKET;
			}
#ifdef _DEBUG
			::OutputDebugString("nError	Listen SOCKET检查到监听套节字上发生错误 \n");
#endif // _DEBUG
		}

		ReleaseBuffer(pBuffer);
		return;
	}


	// 开始处理
	if(pBuffer->nOperation == OP_ACCEPT)
	{
		if(dwTrans == 0)
		{
#ifdef _DEBUG
			::OutputDebugString("OP_ACCEPT	监听套节字上客户端关闭 \n");
#endif // _DEBUG
			
			if(pBuffer->sClient != INVALID_SOCKET)
			{
				::closesocket(pBuffer->sClient);
				pBuffer->sClient = INVALID_SOCKET;
			}
		}
		else
		{
			// 为新接受的连接申请客户上下文对象
			CIOCPContext *pClient = AllocateContext(pBuffer->sClient);
			if(pClient != NULL)
			{
				if(AddAConnection(pClient))
				{	
					// 取得客户地址
					int nLocalLen, nRmoteLen;
					LPSOCKADDR pLocalAddr, pRemoteAddr;
					m_lpfnGetAcceptExSockaddrs(
						pBuffer->buff,
						pBuffer->nLen - ((sizeof(sockaddr_in) + 16) * 2),
						sizeof(sockaddr_in) + 16,
						sizeof(sockaddr_in) + 16,
						(SOCKADDR **)&pLocalAddr,
						&nLocalLen,
						(SOCKADDR **)&pRemoteAddr,
						&nRmoteLen);
					memcpy(&pClient->addrLocal, pLocalAddr, nLocalLen);
					memcpy(&pClient->addrRemote, pRemoteAddr, nRmoteLen);
					
					// 关联新连接到完成端口对象
					::CreateIoCompletionPort((HANDLE)pClient->s, m_hCompletion, (DWORD)pClient, 0);
					
					// 通知用户
					pBuffer->nLen = dwTrans;
					OnConnectionEstablished(pClient, pBuffer);
					
					// 向新连接投递几个Read请求，这些空间在套节字关闭或出错时释放
					for(int i=0; i<m_nInitialReads ; i++)
					{
						CIOCPBuffer *p = AllocateBuffer(BUFFER_SIZE);
						if(p != NULL)
						{
							if(!PostRecv(pClient, p))
							{
								CloseAConnection(pClient);
								break;
							}
						}
					}
				}
				else	// 连接数量已满，关闭连接
				{
					CloseAConnection(pClient);
					ReleaseContext(pClient);
				}
			}
			else
			{
				// 资源不足，关闭与客户的连接即可
				::closesocket(pBuffer->sClient);
				pBuffer->sClient = INVALID_SOCKET;
			}
		}
		
		// Accept请求完成，释放I/O缓冲区
		ReleaseBuffer(pBuffer);	

		// 通知监听线程继续再投递一个Accept请求
		::InterlockedIncrement(&m_nRepostCount);
		::SetEvent(m_hRepostEvent);
	}
	else if(pBuffer->nOperation == OP_READ)
	{
		if(dwTrans == 0)	// 对方关闭套节字
		{
			// 先通知用户
			pBuffer->nLen = 0;
			OnConnectionClosing(pContext, pBuffer);	
			// 再关闭连接
			CloseAConnection(pContext);
			// 释放客户上下文和缓冲区对象
			if(pContext->nOutstandingRecv == 0 && pContext->nOutstandingSend == 0)
			{		
				ReleaseContext(pContext);
			}
			ReleaseBuffer(pBuffer);	
		}
		else
		{
			pBuffer->nLen = dwTrans;
			// 按照I/O投递的顺序读取接收到的数据
			CIOCPBuffer *p = GetNextReadBuffer(pContext, pBuffer);
			while(p != NULL)
			{
				// 通知用户
				OnReadCompleted(pContext, p);
				// 增加要读的序列号的值
				::InterlockedIncrement((LONG*)&pContext->nCurrentReadSequence);
				// 释放这个已完成的I/O
				ReleaseBuffer(p);
				p = GetNextReadBuffer(pContext, NULL);
			}

//			printf("空闲buffer数:%d \n",m_nFreeBufferCount);
			if (pContext->nOutstandingRecv <= 0)
			{
				for(int i=0; i<m_nInitialReads ; i++)
				{
            	    // 继续投递几个新的重叠接收请求,这样能达到最快速度
					// 因为此时pBuffer已经释放或被保存到缓冲区,所以分配一个新的
					pBuffer = AllocateBuffer(BUFFER_SIZE);
					if(pBuffer != NULL)
					{
						if(!PostRecv(pContext, pBuffer))
						{
							CloseAConnection(pContext);
							break;
						}
					}
				}
			}

		}
	}
	else if(pBuffer->nOperation == OP_WRITE)
	{

		if(dwTrans == 0)	// 对方关闭套节字
		{
			// 先通知用户
			pBuffer->nLen = 0;
			OnConnectionClosing(pContext, pBuffer);	

			// 再关闭连接
			CloseAConnection(pContext);

			// 释放客户上下文和缓冲区对象
			if(pContext->nOutstandingRecv == 0 && pContext->nOutstandingSend == 0)
			{		
				ReleaseContext(pContext);
			}
			ReleaseBuffer(pBuffer);	
		}
		else
		{
			// 写操作完成，通知用户
			pBuffer->nLen = dwTrans;
			OnWriteCompleted(pContext, pBuffer);
			// 释放SendText函数申请的缓冲区
			ReleaseBuffer(pBuffer);
		}
	}
}