UINT CRefresher::GetRefreshSetting(RefreshParam& rp)
{
	UINT	uRet	= 0;
	CProfile	prof;
	if((uRet = prof.LoadProfile(SYS_CONFIG_POS)) != 0)
		return uRet;
	if((uRet = prof.GetProfileStringW(REFRESH_SETTING,SERVER_IP,rp.strIp) != 0))
		return uRet;
	if((uRet = prof.GetProfileIntW(REFRESH_SETTING,SERVER_PORT,rp.iPort) != 0))
		return uRet;
	if((uRet = prof.GetProfileStringW(REFRESH_SETTING,SEND_MSG,rp.strMsg) != 0))
		return uRet;
	return uRet;
}