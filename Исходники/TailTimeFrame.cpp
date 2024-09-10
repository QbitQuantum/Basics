// 初始化尾包时刻帧
void OnInitInstrTailTimeFrame(m_oTailTimeFrameStruct* pTailTimeFrame,
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar)
{
	ASSERT(pTailTimeFrame != NULL);
	ASSERT(pCommInfo != NULL);
	ASSERT(pConstVar != NULL);
	EnterCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	if (pTailTimeFrame->m_pCommandStructSet != NULL)
	{
		delete pTailTimeFrame->m_pCommandStructSet;
		pTailTimeFrame->m_pCommandStructSet = NULL;
	}
	pTailTimeFrame->m_pCommandStructSet = new m_oInstrumentCommandStruct;
	// 源地址
	pTailTimeFrame->m_pCommandStructSet->m_uiSrcIP = pCommInfo->m_pServerSetupData->m_oXMLIPSetupData.m_uiSrcIP;
	// 目的地址
	pTailTimeFrame->m_pCommandStructSet->m_uiAimIP = pCommInfo->m_pServerSetupData->m_oXMLIPSetupData.m_uiAimIP;
	// 目标IP地址端口号
	pTailTimeFrame->m_pCommandStructSet->m_usAimPort = pCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usAimPort
		+ pCommInfo->m_pServerSetupData->m_oXMLParameterSetupData.m_usNetRcvPortMove;
	// 尾包时刻发送缓冲区帧数设定为仪器个数
	pTailTimeFrame->m_uiSndBufferSize = pConstVar->m_iInstrumentNum * pConstVar->m_iSndFrameSize;
	// 尾包时刻应答接收缓冲区帧数设定为仪器个数
	pTailTimeFrame->m_uiRcvBufferSize = pConstVar->m_iInstrumentNum * pConstVar->m_iRcvFrameSize;
	// 尾包时刻查询返回端口
	pTailTimeFrame->m_pCommandStructSet->m_usReturnPort = pCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usTailTimeReturnPort;
	// 尾包时刻查询接收端口偏移量
	pTailTimeFrame->m_usPortMove = pCommInfo->m_pServerSetupData->m_oXMLParameterSetupData.m_usNetRcvPortMove;
	// 重置帧内通讯信息
	// 命令，为1则设置命令应答，为2查询命令应答，为3AD采样数据重发
	pTailTimeFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendQueryCmd;
	// 重置帧内容解析变量
	ResetInstrFramePacket(pTailTimeFrame->m_pCommandStructSet);
	// 清空发送帧缓冲区
	if (pTailTimeFrame->m_cpSndFrameData != NULL)
	{
		delete[] pTailTimeFrame->m_cpSndFrameData;
		pTailTimeFrame->m_cpSndFrameData = NULL;
	}
	pTailTimeFrame->m_cpSndFrameData = new char[pConstVar->m_iSndFrameSize];
	memset(pTailTimeFrame->m_cpSndFrameData, pConstVar->m_cSndFrameBufInit, 
		pConstVar->m_iSndFrameSize);
	// 清空尾包时刻查询命令字集合
	if (pTailTimeFrame->m_pbyCommandWord != NULL)
	{
		delete[] pTailTimeFrame->m_pbyCommandWord;
		pTailTimeFrame->m_pbyCommandWord = NULL;
	}
	pTailTimeFrame->m_pbyCommandWord = new BYTE[pConstVar->m_iCommandWordMaxNum];
	memset(pTailTimeFrame->m_pbyCommandWord, pConstVar->m_cSndFrameBufInit, 
		pConstVar->m_iCommandWordMaxNum);
	// 尾包时刻查询命令字个数
	pTailTimeFrame->m_usCommandWordNum = 0;

	// 重置帧内容解析变量
	if (pTailTimeFrame->m_pCommandStructReturn != NULL)
	{
		delete pTailTimeFrame->m_pCommandStructReturn;
		pTailTimeFrame->m_pCommandStructReturn = NULL;
	}
	pTailTimeFrame->m_pCommandStructReturn = new m_oInstrumentCommandStruct;
	ResetInstrFramePacket(pTailTimeFrame->m_pCommandStructReturn);
	// 清空接收帧缓冲区
	if (pTailTimeFrame->m_cpRcvFrameData != NULL)
	{
		delete[] pTailTimeFrame->m_cpRcvFrameData;
		pTailTimeFrame->m_cpRcvFrameData = NULL;
	}
	pTailTimeFrame->m_cpRcvFrameData = new char[pConstVar->m_iRcvFrameSize];
	memset(pTailTimeFrame->m_cpRcvFrameData, pConstVar->m_cSndFrameBufInit, 
		pConstVar->m_iRcvFrameSize);
	LeaveCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
}