int	CStockManager::GetMarketStockList(HSMarketDataType* pMarket, int nMarketCount,CArray<StockUserInfo>& ayRef)
{
	
	CSingleLock lock(&m_mutexStock);
	if (lock.Lock())
	{
		int nCount = 0;		
		for ( int i=0; i<m_ayStocks.GetCount(); i++ )
		{
			CHSDSStockInfoIntact* pStockIntact = (CHSDSStockInfoIntact*)m_ayStocks.GetAt(i);
			HSMarketDataType hsMarketCur = pStockIntact->m_stockInfo.m_ciStockCode.m_cCodeType;
			BOOL bInMarket = FALSE;

			if ( pStockIntact && !IsBadReadPtr(pStockIntact,sizeof(CHSDSStockInfoIntact)))
			{
				HSMarketDataType hsMarketCur = pStockIntact->m_stockInfo.m_ciStockCode.m_cCodeType;
				BOOL bInMarket = FALSE;
				if (pStockIntact != NULL )
				{
					for (int i = 0; i < nMarketCount; i ++)
					{
						if (hsMarketCur == pMarket[i])
						{
							bInMarket = TRUE;
							break;
						}
					}
				}
				if (bInMarket )
				{
					ayRef.Add(pStockIntact->m_stockInfo);					
				}
			}			
		}
		lock.Unlock();
	}
	return ayRef.GetCount();
}