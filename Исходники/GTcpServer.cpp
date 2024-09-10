void GTcpSvrServiceThread(PGTHREAD pThread)
{
	DWORD dwResult;
	PGHND_DATA pClient;
	INT nResult;
	INT nLong;
	INT nLongBytes = sizeof(INT);
	DWORD dwTickCount;

	GLog_Write("GTcpSvrServiceThread：伺服线程开始");
	for(;;)
	{
		#if(_RUN_INFO)
		pThread->dwState = GTHREAD_STATE_SLEEP;
		#endif

		if(!dwGTcpSvrListenerCount)
		{
			Sleep(1000);
			dwResult = WSA_WAIT_TIMEOUT;
		}else
			dwResult = WSAWaitForMultipleEvents(dwGTcpSvrListenerCount, hGTcpSvrListenerEvents, FALSE, 1000, FALSE);
		if(pThread->bIsShutdown)
			break;

		#if(_RUN_INFO)
		pThread->dwState = GTHREAD_STATE_WORKING1;
		pThread->dwRunCount++;
		#endif

		if(WSA_WAIT_TIMEOUT != dwResult)
		{	
			dwResult -= WSA_WAIT_EVENT_0;
			WSAResetEvent(hGTcpSvrListenerEvents[dwResult]);
			if((dwGTcpSvrClientCount + dwGTcpSvrPendingAcceptCount >= dwGSockMaxNumberConnection) || (!GTcpSvr_PostAccept(pGTcpSvrListeners[dwResult], dwGSockNumberPostAccept)))
			{
				SOCKADDR_IN Addr;
				int nLen;
				nLen = sizeof(SOCKADDR_IN);
				closesocket(WSAAccept(pGTcpSvrListeners[dwResult]->Socket, (SOCKADDR*)&Addr, &nLen, NULL, 0));
				if(dwGTcpSvrClientCount >= dwGSockMaxNumberConnection)
					GLog_Write("GTcpSvrServiceThread：超出连接限制");
				else
					GLog_Write("GTcpSvrServiceThread：投递接受“GTcpSvr_PostAccept”失败");

				#if(_OUTIODATA_INFO)
				std::stringstream ss;
				ss << "[GTcpSvrServiceThread]" << "[SvrClientCount:"<<dwGTcpSvrClientCount <<"|SvrPendingAcceptCount:" <<dwGTcpSvrPendingAcceptCount<< "]";
				GLog_Write(const_cast<char*>(ss.str().c_str()));
				#endif
			}
			continue;
		}

		if(dwGSockAcceptBytes)
		{
			#if(_USE_INTERLOCKED_IN_LIST)
			GTcpSvr_LockPendingAcceptList();
			#else
			EnterCriticalSection(&GTcpSvrPendingAcceptCS);
			#endif

			#if(_RUN_INFO)
			pThread->dwState = GTHREAD_STATE_WORKING2;
			#endif

			pClient = pGTcpSvrPendingAcceptHead;
			pGTcpSvrOvertimeCount = 0;
			while(pClient)
			{
				nResult = getsockopt(pClient->Socket, SOL_SOCKET, SO_CONNECT_TIME, (char *)&nLong, (PINT)&nLongBytes);
				if((SOCKET_ERROR != nResult) && (0xFFFFFFFF != nLong) && (dwGSockTimeAcceptOvertime < (DWORD)nLong))
				{
					pGTcpSvrOvertimeClient[pGTcpSvrOvertimeCount] = pClient;
					pGTcpSvrOvertimeCount++;
				}
				pClient = pClient->pNext;
			}

			#if(_USE_INTERLOCKED_IN_LIST)
			GTcpSvr_UnlockPendingAcceptList();
			#else
			LeaveCriticalSection(&GTcpSvrPendingAcceptCS);
			#endif

			#if(_RUN_INFO)
			pThread->dwState = GTHREAD_STATE_WORKING3;
			#endif

			while(pGTcpSvrOvertimeCount)	//overtime send GIO_CLOSE
			{
				pGTcpSvrOvertimeCount--;
				pGTcpSvrOvertimeClient[pGTcpSvrOvertimeCount]->dwTickCountAcitve = dwTickCount;
				GTcpSvr_DoCloseClient(PGHND_DATA(pGTcpSvrOvertimeClient[pGTcpSvrOvertimeCount]->pOwner), pGTcpSvrOvertimeClient[pGTcpSvrOvertimeCount], GIO_CLOSE);
			}
		}//if(dwGSockAcceptBytes)

		if(dwGSockTimeIdleOvertime)
		{
			#if(_USE_INTERLOCKED_IN_LIST)
			GTcpSvr_LockClientList();
			#else
			EnterCriticalSection(&GTcpSvrClientCS);
			#endif

			#if(_RUN_INFO)
			pThread->dwState = GTHREAD_STATE_WORKING4;
			#endif

			pClient = pGTcpSvrClientHead;
			pGTcpSvrOvertimeCount = 0;
			dwTickCount = GetTickCount();
			while(pClient)
			{//QueryPerformanceCounter
				if(dwTickCount >= pClient->dwTickCountAcitve)
					nLong = dwTickCount - pClient->dwTickCountAcitve;
				else
					nLong = 0xFFFFFFFF - pClient->dwTickCountAcitve + dwTickCount;
				if((DWORD)nLong > dwGSockTimeIdleOvertime)
				{
					pGTcpSvrOvertimeClient[pGTcpSvrOvertimeCount] = pClient;
					pGTcpSvrOvertimeCount++;
				}
				pClient = pClient->pNext;
			}

			#if(_USE_INTERLOCKED_IN_LIST)
			GTcpSvr_UnlockClientList();
			#else
			LeaveCriticalSection(&GTcpSvrClientCS);
			#endif
			
			#if(_RUN_INFO)
			pThread->dwState = GTHREAD_STATE_WORKING5;
			#endif

			while(pGTcpSvrOvertimeCount)
			{
				pGTcpSvrOvertimeCount--;
				pGTcpSvrOvertimeClient[pGTcpSvrOvertimeCount]->dwTickCountAcitve = dwTickCount;
				GTcpSvr_DoCloseClient(pGTcpSvrOvertimeClient[pGTcpSvrOvertimeCount], pGTcpSvrOvertimeClient[pGTcpSvrOvertimeCount], GIO_IDLE_OVERTIME);
			}
		}//if(dwGSockTimeIdleOvertime)
	}//for(;;)
}