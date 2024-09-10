int CDrawQuoteTabCtrl::OpenAllMarketMenu(CPoint point )
{
	CDrawQuoteTab* pTab = m_ayItem[m_nCurItem];
	CString strCurItemName = pTab->m_strName;
	CArray<StockType> ayAllMarket;
	m_pDataSource->HSDataSourceEx_GetSystemMarketInfo(0, 0, ayAllMarket);

	short nPreMarket = 0;
	CMenu menu;
	menu.CreatePopupMenu();
	for (int i=0; i<ayAllMarket.GetCount(); i++)
	{
		if ((nPreMarket&0xFF00) != (ayAllMarket.GetAt(i).m_nStockType&0xFF00))
		{
			menu.AppendMenu(MF_SEPARATOR|MF_MENUBARBREAK);
		}
		menu.AppendMenu(MF_BYCOMMAND,CDRAWTAB_ID_MENU_MARKET_BEGIN+i,ayAllMarket.GetAt(i).m_stTypeName.m_szName);
		if (!strCurItemName.IsEmpty() && strCurItemName==ayAllMarket.GetAt(i).m_stTypeName.m_szName)
		{
			menu.CheckMenuItem(CDRAWTAB_ID_MENU_MARKET_BEGIN+i,MF_BYCOMMAND|MF_CHECKED);
		}

		CString strTemp;
		strTemp.Format("%s-%d",ayAllMarket.GetAt(i).m_stTypeName.m_szName,ayAllMarket.GetAt(i).m_nStockType);
		m_mapTempMenuIndex.SetAt(CDRAWTAB_ID_MENU_MARKET_BEGIN+i,strTemp);

		nPreMarket = (ayAllMarket.GetAt(i).m_nStockType&0xFF00);
	}

	CWnd* pWnd = m_pDrawTabNotify->TabGetCWnd();
	int nMenuID = menu.TrackPopupMenu(TPM_VERPOSANIMATION | TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD,point.x,point.y,pWnd);
	menu.DestroyMenu();
	return nMenuID;
}