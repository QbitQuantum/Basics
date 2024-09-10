//通知回调函数（发送队列线程调用）
void __cdecl CTCPNetworkEngine::OnQueueServiceSink(WORD wIdentifier, void * pBuffer, WORD wDataSize)
{
	switch (wIdentifier)
	{
		case QUEUE_SEND_REQUEST:		//发送请求
		{
			//效验数据
			tagSendDataRequest * pSendDataRequest = (tagSendDataRequest *)pBuffer;
			ASSERT(wDataSize >= (sizeof(tagSendDataRequest) - sizeof(pSendDataRequest->cbSendBuf)));
			ASSERT(wDataSize == (pSendDataRequest->wDataSize + sizeof(tagSendDataRequest) - sizeof(pSendDataRequest->cbSendBuf)));

			//群发数据
			if (pSendDataRequest->dwSocketID == 0)
			{
				//获取活动项
				{
					CThreadLock lcok(m_CriticalSection);
					m_TempSocketItem.RemoveAll();
					m_TempSocketItem.Copy(m_ActiveSocketItem);
				}

				//循环发送数据
				CServerSocketItem * pServerSocketItem = NULL;
				for (INT_PTR i = 0; i < m_TempSocketItem.GetCount(); i++)
				{
					pServerSocketItem = m_TempSocketItem[i];
					ASSERT(pServerSocketItem != NULL);
					CThreadLock lock(pServerSocketItem->GetSignedLock());
					if (pServerSocketItem->IsAllowBatch())//第一次不允许？？
					{
						pServerSocketItem->SendData(pSendDataRequest->cbSendBuf, pSendDataRequest->wDataSize, pSendDataRequest->wMainCmdID,
						                            pSendDataRequest->wSubCmdID, pServerSocketItem->GetRountID());
					}
				}
			}
			else
			{
				//单项发送
				CServerSocketItem * pServerSocketItem = EnumSocketItem(LOWORD(pSendDataRequest->dwSocketID));
				CThreadLock lock(pServerSocketItem->GetSignedLock());
				pServerSocketItem->SendData(pSendDataRequest->cbSendBuf, pSendDataRequest->wDataSize, pSendDataRequest->wMainCmdID,
				                            pSendDataRequest->wSubCmdID, HIWORD(pSendDataRequest->dwSocketID));
			}

			break;
		}
		case QUEUE_SAFE_CLOSE:		//安全关闭
		{
			//效验数据
			ASSERT(wDataSize == sizeof(tagSafeCloseSocket));
			tagSafeCloseSocket * pSafeCloseSocket = (tagSafeCloseSocket *)pBuffer;

			//安全关闭
			try
			{
				CServerSocketItem * pServerSocketItem = EnumSocketItem(LOWORD(pSafeCloseSocket->dwSocketID));
				CThreadLock lock(pServerSocketItem->GetSignedLock());
				pServerSocketItem->ShutDownSocket(HIWORD(pSafeCloseSocket->dwSocketID));
			}
			catch (...)
			{
			}
			break;
		}
		case QUEUE_ALLOW_BATCH:		//允许群发
		{
			//效验数据
			ASSERT(wDataSize == sizeof(tagAllowBatchSend));
			tagAllowBatchSend * pAllowBatchSend = (tagAllowBatchSend *)pBuffer;

			//设置群发
			CServerSocketItem * pServerSocketItem = EnumSocketItem(LOWORD(pAllowBatchSend->dwSocketID));
			CThreadLock lock(pServerSocketItem->GetSignedLock());
			pServerSocketItem->AllowBatchSend(HIWORD(pAllowBatchSend->dwSocketID), pAllowBatchSend->cbAllow ? true : false);

			break;
		}
		case QUEUE_DETECT_SOCKET:	//检测连接
		{
			//获取活动项
			{
				CThreadLock lcok(m_CriticalSection);
				m_TempSocketItem.RemoveAll();
				m_TempSocketItem.Copy(m_ActiveSocketItem);
			}

			//构造数据
			CMD_KN_DetectSocket DetectSocket;
			ZeroMemory(&DetectSocket, sizeof(DetectSocket));

			//变量定义
			WORD wRountID = 0;
			DWORD dwNowTickCount = GetTickCount();
			DWORD dwBreakTickCount = __max(dwNowTickCount - m_dwLastDetect, TIME_BREAK_READY);

			//设置变量
			m_dwLastDetect = GetTickCount();

			//检测连接
			for (INT_PTR i = 0; i < m_TempSocketItem.GetCount(); i++)
			{
				//变量定义
				CServerSocketItem * pServerSocketItem = m_TempSocketItem[i];
				DWORD dwRecvTickCount = pServerSocketItem->GetRecvTickCount();
				CThreadLock lock(pServerSocketItem->GetSignedLock());

				//间隔检查
				if (dwRecvTickCount >= dwNowTickCount) continue;

				//检测连接
				if (pServerSocketItem->IsReadySend() == true)
				{
					if ((dwNowTickCount - dwRecvTickCount) > dwBreakTickCount)
					{
						pServerSocketItem->CloseSocket(pServerSocketItem->GetRountID());
						continue;
					}
				}
				else
				{
					if ((dwNowTickCount - dwRecvTickCount) > TIME_BREAK_CONNECT)
					{
						pServerSocketItem->CloseSocket(pServerSocketItem->GetRountID());
						continue;
					}
				}

				//发送数据
				if (pServerSocketItem->IsReadySend() == true)
				{
					wRountID = pServerSocketItem->GetRountID();
					DetectSocket.dwSendTickCount = GetTickCount();
					pServerSocketItem->SendData(&DetectSocket, sizeof(DetectSocket), MDM_KN_COMMAND, SUB_KN_DETECT_SOCKET, wRountID);
				}
			}

			break;
		}
		default:
		{
			ASSERT(FALSE);
		}
	}

	return;
}