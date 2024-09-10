void CUser::MarketBBSTimeCheck()
{
	CUser* pUser = NULL;	// Basic Initializations. 	
	int send_index = 0;			
	char send_buff[256]; memset(send_buff, NULL, 256);	
	float currenttime = 0.0f;
	int price = 0;

	currenttime = TimeGet();

	for (int i = 0 ; i < MAX_BBS_POST ; i++) {		
		if (m_pMain->m_sBuyID[i] != -1) {	// BUY!!!
			pUser = m_pMain->GetUserPtr(m_pMain->m_sBuyID[i]);			
			if (pUser == NULL)
			{
				MarketBBSBuyDelete(i);
				continue;
			}
			
			if (m_pMain->m_fBuyStartTime[i] + BBS_CHECK_TIME < currenttime) {
				if (pUser->m_pUserData->m_iGold >= BUY_POST_PRICE) {
					pUser->m_pUserData->m_iGold -= BUY_POST_PRICE ;
					m_pMain->m_fBuyStartTime[i] = TimeGet();

					memset(send_buff, NULL, 256); send_index = 0;	
					SetByte( send_buff, WIZ_GOLD_CHANGE, send_index );	// Now the target
					SetByte( send_buff, 0x02, send_index );
					SetDWORD( send_buff, BUY_POST_PRICE, send_index );
					SetDWORD( send_buff, pUser->m_pUserData->m_iGold, send_index );
					pUser->Send( send_buff, send_index );	
				}
				else {
					MarketBBSBuyDelete(i);
				}
			}
		}
		
		if (m_pMain->m_sSellID[i] != -1) {	// SELL!!!
			pUser = m_pMain->GetUserPtr(m_pMain->m_sSellID[i]);
			if (pUser == NULL)
			{
				MarketBBSSellDelete(i);
				continue;
			}
		
			if (m_pMain->m_fSellStartTime[i] + BBS_CHECK_TIME < currenttime) {
				if (pUser->m_pUserData->m_iGold >= SELL_POST_PRICE) {
					pUser->m_pUserData->m_iGold -= SELL_POST_PRICE ;
					m_pMain->m_fSellStartTime[i] = TimeGet();

					memset(send_buff, NULL, 256); send_index = 0;
					SetByte( send_buff, WIZ_GOLD_CHANGE, send_index );	// Now the target
					SetByte( send_buff, 0x02, send_index );
					SetDWORD( send_buff, SELL_POST_PRICE, send_index );
					SetDWORD( send_buff, pUser->m_pUserData->m_iGold, send_index );
					pUser->Send( send_buff, send_index );	
				}
				else {
					MarketBBSSellDelete(i);
				}
			}
		}
	}
}