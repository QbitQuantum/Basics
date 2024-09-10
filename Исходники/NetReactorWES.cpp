	CErrno NetReactorWES::iUpdate(INT32 start, INT32 end)
	{
		INT32 count = end - start;
		DWORD result = WaitForMultipleObjects(count, &m_pEvents[start], FALSE, 1);

		if (result >= WAIT_OBJECT_0 && result < (WAIT_OBJECT_0 + count))
		{
			int index = result - WAIT_OBJECT_0 + start;
			INetHandlerPtr pNetHandler = m_pConnections[index];
			WSANETWORKEVENTS events = { 0 };
			WSAEnumNetworkEvents((SOCKET)pNetHandler->GetSession()->GetSocket(), m_pEvents[index], &events);

			bool bClosed = false;
			if (events.lNetworkEvents & FD_READ)
			{
				bClosed = !pNetHandler->OnMsgRecving().IsSuccess() || bClosed;
			}
			if (events.lNetworkEvents & FD_ACCEPT)
			{
				bClosed = !pNetHandler->OnMsgRecving().IsSuccess() || bClosed;
			}
			if (events.lNetworkEvents & FD_WRITE)
			{
				bClosed = !pNetHandler->OnMsgSending().IsSuccess() || bClosed;
			}
			if (events.lNetworkEvents & FD_CLOSE)
			{
				bClosed = true;
			}

			ISession * pSession = pNetHandler->GetSession();
			if (pSession && pSession->GetObjTimeout().IsExpired() || pSession->IsClosed())
			{
				bClosed = TRUE;
			}

			if (bClosed)
			{
				gDebugStream("delete curNodeName=" << pNetHandler->GetSession()->GetCurNodeName() << ":remoteName=" << pNetHandler->GetSession()->GetRemoteName() << ":address=" << pNetHandler->GetSession()->GetAddress() << ":port=" << pNetHandler->GetSession()->GetPort());
				DelNetHandler(pNetHandler);
				pNetHandler->OnClose();
			}
		}
		else if (result == WAIT_FAILED)
		{
			gDebugStream("***********Error***********" << "Wait Failed");
		}
		else if (result >= WAIT_ABANDONED_0 && result < (WAIT_ABANDONED_0 + count))
		{
			gDebugStream("***********Error***********" << "WAIT_ABANDONED_0" << result - WAIT_ABANDONED_0);
		}
		else if (result == WAIT_TIMEOUT)
		{

		}
		return CErrno::Success();
	}