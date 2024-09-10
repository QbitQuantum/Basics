void PatsApiDealer::ReadIniConfig()
{ // 登录需要的参数
	m_useSimEngine = 0;
	memset(m_szTraderAccount,   0, sizeof(m_szTraderAccount));
	m_useSimEngine = GetPrivateProfileIntA("PATSAPIDEALER","SIMENGINE_DEALER",0,".\\AIB.ini");
	GetPrivateProfileStringA("PATSAPIDEALER", "TRADER_ACCOUNT", "", m_szTraderAccount, 21, ".\\AIB.ini");
	TRACE_LOG("PatsApiDealer ReadIniConfig UseSimEngine:%d, TraderAccount:%s.",m_useSimEngine,m_szTraderAccount);
}