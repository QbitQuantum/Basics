//读取配置
void CAndroidUserItemSink::ReadConfigInformation(TCHAR szFileName[], TCHAR szRoomName[], bool bReadFresh)
{
	//设置文件名
	TCHAR szPath[MAX_PATH] = TEXT("");
	TCHAR szConfigFileName[MAX_PATH] = TEXT("");
	TCHAR OutBuf[255] = TEXT("");
	GetCurrentDirectory(sizeof(szPath), szPath);
	_snprintf(szConfigFileName, sizeof(szConfigFileName), _T("%s\\%s"), szPath, szFileName);

	//每盘刷新
	if (bReadFresh)
	{
		//每盘刷新
		BYTE cbRefreshCfg = GetPrivateProfileInt(szRoomName, TEXT("Refresh"), 0, szConfigFileName);
		m_bRefreshCfg = cbRefreshCfg?true:false;
	}

	//筹码限制
	ZeroMemory(OutBuf, sizeof(OutBuf));
	GetPrivateProfileString(szRoomName, TEXT("RobotMaxJetton"), _T("5000000"), OutBuf, 255, szConfigFileName);
	_snscanf(OutBuf, strlen(OutBuf), _T("%I64d"), &m_lRobotJettonLimit[1]);

	ZeroMemory(OutBuf, sizeof(OutBuf));
	GetPrivateProfileString(szRoomName, TEXT("RobotMinJetton"), _T("100"), OutBuf, 255, szConfigFileName);
	_snscanf(OutBuf, strlen(OutBuf), _T("%I64d"), &m_lRobotJettonLimit[0]);

	if (m_lRobotJettonLimit[1] > 5000000)					m_lRobotJettonLimit[1] = 5000000;
	if (m_lRobotJettonLimit[0] < 1000)						m_lRobotJettonLimit[0] = 100;
	if (m_lRobotJettonLimit[1] < m_lRobotJettonLimit[0])	m_lRobotJettonLimit[1] = m_lRobotJettonLimit[0];

	//次数限制
	m_nRobotBetTimeLimit[0] = GetPrivateProfileInt(szRoomName, _T("RobotMinBetTime"), 4, szConfigFileName);;
	m_nRobotBetTimeLimit[1] = GetPrivateProfileInt(szRoomName, _T("RobotMaxBetTime"), 8, szConfigFileName);;

	if (m_nRobotBetTimeLimit[0] < 0)							m_nRobotBetTimeLimit[0] = 0;
	if (m_nRobotBetTimeLimit[1] < m_nRobotBetTimeLimit[0])		m_nRobotBetTimeLimit[1] = m_nRobotBetTimeLimit[0];

	//是否坐庄
	m_bRobotBanker = (GetPrivateProfileInt(szRoomName, _T("RobotBanker"), 0, szConfigFileName) == 1);

	//坐庄次数
	m_nRobotBankerCount = GetPrivateProfileInt(szRoomName, _T("RobotBankerCount"), 3, szConfigFileName);

	//空盘重申
	m_nRobotWaitBanker = GetPrivateProfileInt(szRoomName, _T("RobotWaitBanker"), 3, szConfigFileName);

	//最多个数
	m_nRobotApplyBanker = GetPrivateProfileInt(szRoomName, _T("RobotApplyBanker"), 3, szConfigFileName);

	//降低限制
	m_bReduceJettonLimit = (GetPrivateProfileInt(szRoomName, TEXT("RobotReduceLimit"), 0, szConfigFileName)!=0);

	//MyDebug(_T("机器人 读取配置 [%I64d %I64d %d %d] %d [%d %d %d] 下注 %d 下降 %d"), m_lRobotJettonLimit[0], m_lRobotJettonLimit[1],
	//	m_nRobotBetTimeLimit, m_nRobotBetTimeLimit, m_bRobotBanker, m_nRobotBankerCount, m_nRobotWaitBanker, m_nRobotApplyBanker, m_bReduceJettonLimit);
}