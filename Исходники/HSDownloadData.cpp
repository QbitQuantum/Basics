BOOL CHSDownloadData::DownLoadData()
{
	CriticalGuard guard(&m_critical);
	long lLen;
	StockUserInfo* pStock = NULL;
	short nPeriod;
	SetTaskMask(m_nCulType);
	m_nCulType ++;
	if ( m_nCulType >= 4)
		m_nCulType = 1;
	GetNextCode(&pStock, nPeriod);
	char* pBuffer = MakeReqPacket(&pStock->m_ciStockCode,nPeriod,lLen);

	if(pBuffer == NULL)
	{
		DownLoadData();
	}
	else
	{
		HSMarketDataType market = pStock->m_ciStockCode.m_cCodeType & 0xF000;
		char cServerType = CEV_Connect_HQ;

		if(market == FUTURES_MARKET)
		{
			//cServerType = CEV_Connect_QH;  //期货
		}

		if (market == HK_MARKET)
		{
			//cServerType = CEV_Connect_GG;  //港股
		}
		if ( m_pDataSource && !IsBadReadPtr(m_pDataSource,1))
			m_pDataSource->HSDataSource_RequestAsyncData(m_nDataSourceID,pBuffer,lLen,-1,e_DataSouceSend_Normal|e_DataSourceSend_HQDataDownLoad,
			                     m_lHandle);
		TRACE2("\r\n send packet code:%s, nPeriod:%d \r\n", pStock->GetName(),nPeriod);
	}
	return TRUE;	
}