CTradeStockBaseDlg::~CTradeStockBaseDlg()
{
	UnRequestHQ();
	UnregisterHotKey(HOTKEY_ENTRUST_ID, 0, VK_F3);
	if (m_bQuickTrade)
	   UnregisterLinkageMsg(PUBLIC_MESSAGE_QUICKTRADE);
	UnregisterLinkageMsg(PUBLIC_MESSAGE_TRADE);
	UnregisterLinkageMsg(TRADE_MESSAGE_STOCKCODE);
	if (m_pTradeMarketList)
	{
		m_pTradeMarketList->Release();
	}
	if (m_pSHSJType)
	{
		m_pSHSJType->Release();
	}
	if (m_pSZSJType)
	{
		m_pSZSJType->Release();
	}
	if (m_StockEntrustType)
	{
		m_StockEntrustType->Release();
	}
}