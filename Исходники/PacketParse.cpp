uint8 CPacketParse::WebSocketDisposeDataIn(_WebSocketInfo* pWebSocketInfo, ACE_Message_Block* pCurrMessage, IMessageBlockManager* pMessageBlockManager)
{
	//处理数据包
	char* pData   = pCurrMessage->rd_ptr();     //得到这个数据块的首字节
	uint32 u4Data = pCurrMessage->length();     //得到这个数据块的长度
	uint32 u4PacketLen = 0;
	uint8 u1Ret        = (uint8)PACKET_GET_ERROR;  

	//将收到的数据粘入缓冲等待做切包处理
	if(pWebSocketInfo->m_u4DataLength + u4Data > MAX_ENCRYPTLENGTH)
	{
		OUR_DEBUG((LM_ERROR, "[CPacketParse::WebSocketDisposeHandIn]pWebSocketInfo is full.\n"));
		return (uint8)PACKET_GET_ERROR;
	}

	memcpy_safe(pData, u4Data, (char* )&pWebSocketInfo->m_szData[pWebSocketInfo->m_u4DataLength], u4Data);
	pWebSocketInfo->m_u4DataLength += u4Data;

	//解析规则约定为
	//<命令字>,<数据包长度><数据包体>

	//首先解密数据包,最大解密数据包是5K
	//如果再大，则扩展这个大小
	if(pWebSocketInfo->m_u4DecryptDataLen + pWebSocketInfo->m_u4DataLength > MAX_DECRYPTLENGTH)
	{
		OUR_DEBUG((LM_ERROR, "[CPacketParse::WebSocketDisposeHandIn]m_u4DecryptDataLen is full.\n"));
		return (uint8)PACKET_GET_ERROR;
	}

	char* pDecryptData = (char* )&pWebSocketInfo->m_szDecryptData[pWebSocketInfo->m_u4DecryptDataLen];
	uint32 u4DecryptLen = MAX_DECRYPTLENGTH;
	uint32 u4OriPacketLen = pWebSocketInfo->m_u4DataLength;
	u1Ret = Decrypt(pWebSocketInfo->m_szData, u4OriPacketLen, pDecryptData, u4DecryptLen);
	if(u1Ret != (uint8)PACKET_GET_ENOUGTH)
	{
		return u1Ret;
	}

	pWebSocketInfo->m_u4DecryptDataLen += u4DecryptLen;

	//如果接受字节少于9个，则认为包头不完整
	if(u4Data < 9)
	{
		return (uint8)PACKET_GET_NO_ENOUGTH;
	}

	//已经解析出完整数据包，判断是否有后续数据包的部分数据
	if(pWebSocketInfo->m_u4DataLength > u4OriPacketLen)
	{
		//有后续的数据包，在这里需要处理一下
		pWebSocketInfo->m_u4DataLength -= u4OriPacketLen;

		memcpy_safe((char* )&pWebSocketInfo->m_szData[u4OriPacketLen], pWebSocketInfo->m_u4DataLength, (char* )&pWebSocketInfo->m_szData, pWebSocketInfo->m_u4DataLength);
	}
	else
	{
		pWebSocketInfo->m_u4DataLength = 0;
	}
	
	//接收到了完整的数据包，开始处理数据
	//获得当前包ID和包长
	uint32 u4CurrDecryptDataLen = pWebSocketInfo->m_u4DecryptDataLen;
	u1Ret = ReadDataPacketInfo(pWebSocketInfo->m_szDecryptData, u4CurrDecryptDataLen, m_u2PacketCommandID, u4PacketLen);
	if(u1Ret == PACKET_GET_ENOUGTH)
	{
		//申请一个包头，记录当前包的所有长度
		m_pmbHead = pMessageBlockManager->Create(sizeof(uint32));
		if(NULL == m_pmbHead)
		{
			return (uint8)PACKET_GET_ERROR;
		}

		//去掉包头，只留数据体在包体内
		char* pInfo = (char* )ACE_OS::strstr(pWebSocketInfo->m_szDecryptData, "{");
		if(NULL == pInfo)
		{
			//如果找不到大括号，说明数据包异常，断开这个链接
			return (uint8)PACKET_GET_ERROR;
		}

		uint32 u4NetPacketLen = u4CurrDecryptDataLen - (uint32)(pInfo - pWebSocketInfo->m_szDecryptData);
		memcpy_safe((char*)&u4NetPacketLen, (uint32)sizeof(uint32), (char* )m_pmbHead->wr_ptr(), (uint32)sizeof(uint32));
		m_pmbHead->wr_ptr(sizeof(uint32));

		//获得包体
		m_pmbBody = pMessageBlockManager->Create(u4NetPacketLen);
		if(NULL == m_pmbBody)
		{
			return PACKET_GET_ERROR;
		}

		memcpy_safe((char*)pInfo, u4NetPacketLen, (char* )m_pmbBody->wr_ptr(), u4NetPacketLen);
		m_pmbBody->wr_ptr(u4NetPacketLen);

		//处理完的数据从块中移除
		pCurrMessage->reset();

		//如果有剩余数据，则再让系统判定一下
		if(pWebSocketInfo->m_u4DataLength > 0)
		{
			pCurrMessage->size((size_t)pWebSocketInfo->m_u4DataLength);
			memcpy_safe(pWebSocketInfo->m_szData, pWebSocketInfo->m_u4DataLength, (char* )pCurrMessage->wr_ptr(), pWebSocketInfo->m_u4DataLength);
			pCurrMessage->wr_ptr(pWebSocketInfo->m_u4DataLength);
			pWebSocketInfo->m_u4DataLength = 0;
		}

		//如果解析包还有内容，则再放回去
		pWebSocketInfo->m_u4DecryptDataLen -= u4CurrDecryptDataLen;
		if(pWebSocketInfo->m_u4DecryptDataLen > 0)
		{
			memcpy_safe((char* )&pWebSocketInfo->m_szDecryptData[u4CurrDecryptDataLen],
				pWebSocketInfo->m_u4DecryptDataLen,
				pWebSocketInfo->m_szDecryptData,
				pWebSocketInfo->m_u4DecryptDataLen);
		}

		return (uint8)PACKET_GET_ENOUGTH;
	}
	else
	{
		return u1Ret;
	}

}