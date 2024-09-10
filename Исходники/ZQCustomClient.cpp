void CZQCustomClient::ReadySendNextData(pBlock data, int buflen)
{
	int iSendlen = 0;
	int iRemainLen = 0;
	EnterCriticalSection(&m_SendCS);
	m_IsSending = false;
	pClientSendData node = NULL;
	while (m_beginpSendData)
	{
		node = m_beginpSendData;
		iRemainLen = MAX_BUFFER_LEN - iSendlen;
		int iDatalen = node->buflen - node->iStartPosition;
		if (iDatalen > iRemainLen)
		{
			memmove_s(&data->MsgBuf[iSendlen], iRemainLen, &node->Buf[node->iStartPosition], node->buflen);
			iSendlen = MAX_BUFFER_LEN;
			node->iStartPosition += iRemainLen;
			break;
		}
		else
		{
			memmove_s(&data->MsgBuf[iSendlen], iDatalen, &node->Buf[iSendlen], node->buflen);
			iSendlen += iDatalen;
			m_beginpSendData = node->Next;
			if (m_beginpSendData == NULL)
				m_endSendData = NULL;
			free(node->Buf);
			delete (node);

		}

	}


	if (iSendlen > 0)
	{
		m_IsSending = true;
		//这里需要记录一下总的发送数量。
		int ErrorCode = 0;
		DWORD  Transfer = 0;
		DWORD   flags = 0;
		data->OperatorType = ioWrite;
		data->buf.len = iSendlen;
		data->buf.buf = data->MsgBuf;
		memset(&data->overloapped, 0, sizeof(data->overloapped));
		if ((m_socket == INVALID_SOCKET) || (WSASend(m_socket, &data->buf, 1, &Transfer, flags, &data->overloapped, NULL) == SOCKET_ERROR))
		{
			ErrorCode = WSAGetLastError();
			if (ErrorCode != ERROR_IO_PENDING)
			{
				//发送出错了
				m_IsSending = false;
				Close();
			}
		}
		m_IsSending = false;

	}
	LeaveCriticalSection(&m_SendCS);
	
}