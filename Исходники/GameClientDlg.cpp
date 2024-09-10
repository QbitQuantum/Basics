//游戏场景
bool CGameClientDlg::OnGameSceneMessage(BYTE cbGameStation, bool bLookonOther, const void * pBuffer, WORD wDataSize)
{
	if(IsLookonMode())m_GameClientView.m_bLookOnUser=true;
	switch (cbGameStation)
	{
	case GS_FREE:		//空闲状态
		{
			//效验数据
			if (wDataSize!=sizeof(CMD_S_StatusFree)) return false;
			CMD_S_StatusFree * pStatusFree=(CMD_S_StatusFree *)pBuffer;

			//设置控件
			if (IsLookonMode()==false)
			{
				SetGameTimer(GetMeChairID(),IDI_START_GAME,TIME_USER_START_GAME);
				m_GameClientView.m_btStart.ShowWindow(SW_SHOW);
				m_GameClientView.m_btStart.SetFocus();
			}

			return true;
		}
	case GS_TK_CALL:	// 叫庄状态
		{
			//效验数据
			if (wDataSize!=sizeof(CMD_S_StatusCall)) return false;
			CMD_S_StatusCall * pStatusCall=(CMD_S_StatusCall *)pBuffer;

			//用户信息
			for (WORD i=0;i<GAME_PLAYER;i++)
			{
				//视图位置
				m_wViewChairID[i]=SwitchViewChairID(i);

				//获取用户
				const tagUserData * pUserData=GetUserData(i);
				if (pUserData==NULL) continue;

				//游戏信息
				m_cbPlayStatus[i]=TRUE;

				//用户名字
				lstrcpyn(m_szAccounts[i],pUserData->szName,CountArray(m_szAccounts[i]));
			}
			
			//始叫用户
			if(!IsLookonMode() && pStatusCall->wCallBanker==GetMeChairID())
			{
				//控件显示
				//ActiveGameFrame();
				m_GameClientView.m_btBanker.ShowWindow(SW_SHOW);
				m_GameClientView.m_btIdler.ShowWindow(SW_SHOW);
			}

			//等待标志
			WORD wViewID=m_wViewChairID[pStatusCall->wCallBanker];
			m_GameClientView.SetWaitCall((BYTE)wViewID);

			//实际定时器
			if(pStatusCall->wCallBanker==GetMeChairID())
			{
				SetGameTimer(pStatusCall->wCallBanker,IDI_CALL_BANKER,TIME_USER_CALL_BANKER);
			}
			else SetGameTimer(pStatusCall->wCallBanker,IDI_NULLITY,TIME_USER_CALL_BANKER);

			return true;
		}
	case GS_TK_SCORE:	//下注状态
		{
			//效验数据
			if (wDataSize!=sizeof(CMD_S_StatusScore)) return false;
			CMD_S_StatusScore * pStatusScore=(CMD_S_StatusScore *)pBuffer;

			//设置变量
			m_lTurnMaxScore=pStatusScore->lTurnMaxScore;
			m_wBankerUser=pStatusScore->wBankerUser;			
			CopyMemory(m_lTableScore,pStatusScore->lTableScore,sizeof(m_lTableScore));
			for (WORD i=0;i<GAME_PLAYER;i++)
			{
				//视图位置
				m_wViewChairID[i]=SwitchViewChairID(i);

				//桌面筹码
				if(m_lTableScore[i]>0L)m_GameClientView.SetUserTableScore(m_wViewChairID[i],m_lTableScore[i]);
				
				//获取用户
				const tagUserData * pUserData=GetUserData(i);
				if (pUserData==NULL) continue;
				
				//游戏信息
				m_cbPlayStatus[i]=TRUE;
				
				//用户名字
				lstrcpyn(m_szAccounts[i],pUserData->szName,CountArray(m_szAccounts[i]));
			}

			//设置筹码
			if (!IsLookonMode() && pStatusScore->lTurnMaxScore>0L && m_lTableScore[GetMeChairID()]==0L)
			{
				LONGLONG lUserMaxScore[GAME_PLAYER];
				ZeroMemory(lUserMaxScore,sizeof(lUserMaxScore));
				LONGLONG lTemp=m_lTurnMaxScore;
				for (WORD i=0;i<GAME_PLAYER;i++)
				{
					if(i>0)lTemp/=2;
					lUserMaxScore[i]=__max(lTemp,1L);
				}

				//更新控件
				UpdateScoreControl(lUserMaxScore,SW_SHOW);

				//实际定时器
				SetTimer(IDI_TIME_USER_ADD_SCORE,(TIME_USER_ADD_SCORE)*1000,NULL);
			}

			//庄家标志
			WORD wID=m_wViewChairID[m_wBankerUser];
			m_GameClientView.SetBankerUser(wID);

			//等待标志
			m_GameClientView.SetWaitInvest(true);


			//辅助显示中心时钟
			SetGameTimer(GetMeChairID(),IDI_NULLITY,TIME_USER_ADD_SCORE);

			return true;
		}
	case GS_TK_PLAYING:	//游戏状态
		{
			//效验数据
			if (wDataSize!=sizeof(CMD_S_StatusPlay)) return false;
			CMD_S_StatusPlay * pStatusPlay=(CMD_S_StatusPlay *)pBuffer;

			//设置变量
			m_lTurnMaxScore=pStatusPlay->lTurnMaxScore;
			m_wBankerUser=pStatusPlay->wBankerUser;
			CopyMemory(m_lTableScore,pStatusPlay->lTableScore,sizeof(m_lTableScore));
			CopyMemory(m_bUserOxCard,pStatusPlay->bOxCard,sizeof(m_bUserOxCard));
			for (WORD i=0;i<GAME_PLAYER;i++)
			{
				//视图位置
				m_wViewChairID[i]=SwitchViewChairID(i);

				//桌面筹码
				if(m_lTableScore[i]>0L)m_GameClientView.SetUserTableScore(m_wViewChairID[i],m_lTableScore[i]);
				
				//获取用户
				const tagUserData * pUserData=GetUserData(i);
				if (pUserData==NULL) continue;
				
				//游戏信息
				m_cbPlayStatus[i]=TRUE;
				
				//扑克数据
				CopyMemory(m_cbHandCardData[i],pStatusPlay->cbHandCardData[i],MAX_COUNT);

				//用户名字
				lstrcpyn(m_szAccounts[i],pUserData->szName,CountArray(m_szAccounts[i]));
			}

			//庄家标志
			WORD wID=m_wViewChairID[m_wBankerUser];
			m_GameClientView.SetBankerUser(wID);

			//左上信息
			//m_GameClientView.SetScoreInfo(m_lTurnMaxScore,0);

			//设置界面
			LONGLONG lTableScore=0L;
			for (WORD i=0;i<GAME_PLAYER;i++)
			{
				//设置位置
				WORD wViewChairID=m_wViewChairID[i];

				//设置扑克
				if (m_cbPlayStatus[i]==TRUE) 
				{
					m_GameClientView.m_CardControl[wViewChairID].SetCardData(pStatusPlay->cbHandCardData[i],MAX_COUNT);
				}
			}

			WORD wMeChiarID=GetMeChairID();
			WORD wViewChairID=m_wViewChairID[wMeChiarID];
			if(!IsLookonMode())m_GameClientView.m_CardControl[wViewChairID].SetPositively(true);
			if(IsAllowLookon() || !IsLookonMode())
			{				
				m_GameClientView.m_CardControl[wViewChairID].SetDisplayFlag(true);
			}

			//摊牌标志
			for (WORD i=0;i<GAME_PLAYER;i++)
			{
				if(m_bUserOxCard[i]!=0xff)
				{
					m_GameClientView.ShowOpenCard(m_wViewChairID[i]);
				}
			}

			//控件处理
			if(!IsLookonMode())
			{
				//显示控件
				if(m_bUserOxCard[wMeChiarID]==0xff)
				{
					OnSendCardFinish(0,0);
				}
				else 
				{
					m_GameClientView.m_CardControl[wViewChairID].SetPositively(false);
					if(m_bUserOxCard[wMeChiarID]==TRUE)//牛牌分类
					{
						//设置变量
						BYTE bTemp[MAX_COUNT];
						CopyMemory(bTemp,m_cbHandCardData[wMeChiarID],sizeof(bTemp));

						//获取牛牌
						m_GameLogic.GetOxCard(bTemp,MAX_COUNT);

						BYTE bCardValue=m_GameLogic.GetCardType(bTemp,MAX_COUNT);
						ASSERT(bCardValue>0);

						if(bCardValue<OX_THREE_SAME)
						{
							//设置控件
							m_GameClientView.m_CardControl[wViewChairID].SetCardData(bTemp,3);
							m_GameClientView.m_CardControlOx[wViewChairID].SetCardData(&bTemp[3],2);	
						}

						//显示点数
						m_GameClientView.SetUserOxValue(wViewChairID,bCardValue);
					}
					else 
					{
						//无牛
						m_GameClientView.SetUserOxValue(wViewChairID,0);
					}					
				}
			}
			return true;
		}
	}

	return false;
}