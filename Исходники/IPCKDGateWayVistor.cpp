BOOL IPCKDGateWayVistor::SendKcxpMsg( char *pCmd )
{
	EnterCriticalSection(&m_caSendMsgLock);
	g_pLog->WriteRunLog(KCXP_MODE, LOG_DEBUG, pCmd);

	int iRetCode = KCBP_MSG_OK;
	char szTemp[512] = {0};

	if (NULL == m_pKcxpConn)
	{
		g_pLog->WriteRunLog(KCXP_MODE, LOG_DEBUG, "获取KCXP连接失败!");
		LeaveCriticalSection(&m_caSendMsgLock);
		return FALSE;
	}	

	// 发送消息
	try
	{
		// 解析命令
		g_pParseKcbpLog->ParseCmd(pCmd);

		// 向KCXP发送命令
		BOOL bRet = g_pParseKcbpLog->ExecSingleCmd();

		// 清空日志解析，便于下一次操作
		g_pParseKcbpLog->Clean();

		if (FALSE != bRet)
		{
			// 获取执行结果
			int nRow = 0;				

			if ((iRetCode = m_pKcxpConn->RsOpen()) == KCBP_MSG_OK)
			{
				// 获取结果集行数，注意行数是包括标题的，因此行数要减1
				m_pKcxpConn->RsGetRowNum(&nRow);

				if (nRow>1)
				{
					m_nRowNum = nRow - 1;					
				}
				else
				{
					g_pLog->WriteRunLogEx(__FILE__,__LINE__,"结果集返回行数异常!");
					m_nRowNum = 0;
					LeaveCriticalSection(&m_caSendMsgLock);
					return FALSE;
				}

				if ((iRetCode = m_pKcxpConn->RsFetchRow()) == KCBP_MSG_OK)
				{
					if ((iRetCode = m_pKcxpConn->RsGetCol(1, szTemp)) == KCBP_MSG_OK)
					{
						if ((iRetCode = m_pKcxpConn->RsGetCol(2, szTemp)) == KCBP_MSG_OK)
						{
							if(strcmp(szTemp,"0") != 0)
							{
								iRetCode = m_pKcxpConn->RsGetCol(3, szTemp);

								g_pLog->WriteRunLogEx(__FILE__,__LINE__, "获取结果集列信息失败,ERRCODE = %ld", iRetCode);
								LeaveCriticalSection(&m_caSendMsgLock);
								return FALSE;
							}
						}
					}
					else
					{
						g_pLog->WriteRunLogEx(__FILE__,__LINE__, "获取结果集列信息失败,ERRCODE = %ld", iRetCode);
						LeaveCriticalSection(&m_caSendMsgLock);
						return FALSE;
					}
				}				
			}
			else
			{	
				g_pLog->WriteRunLogEx(__FILE__,__LINE__,"打开结果集失败,ERRCODE = %ld", iRetCode);
				LeaveCriticalSection(&m_caSendMsgLock);
				return FALSE;
			}
		}
		else
		{
			LeaveCriticalSection(&m_caSendMsgLock);
			return FALSE;
		}
	}
	catch(...)
	{
		g_pLog->WriteRunLog(KCXP_MODE, LOG_DEBUG, "LBM调用异常！");
		LeaveCriticalSection(&m_caSendMsgLock);
		return FALSE;
	}	

	LeaveCriticalSection(&m_caSendMsgLock);
	return TRUE;
}