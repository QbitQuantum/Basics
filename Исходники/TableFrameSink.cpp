//游戏结束
bool __cdecl CTableFrameSink::OnEventGameEnd(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason)
{
	switch (cbReason)
	{
	case GER_NORMAL:		//常规结束
		{
			//定义变量
			CMD_S_GameEnd GameEnd;
			ZeroMemory(&GameEnd,sizeof(GameEnd));
			GameEnd.cbTotalEnd = 1;

			//扑克数据
			BYTE cbEndCardData[GAME_PLAYER][MAX_CENTERCOUNT];
			ZeroMemory(cbEndCardData,sizeof(cbEndCardData));

			try{
				//获取扑克
				for (WORD i=0;i<m_wPlayerCount;i++)
				{
					//用户过滤
					if (m_cbPlayStatus[i]==FALSE) continue;

					//最大牌型
					BYTE cbEndCardKind = m_GameLogic.FiveFromSeven(m_cbHandCardData[i],MAX_COUNT,m_cbCenterCardData,MAX_CENTERCOUNT,cbEndCardData[i],MAX_CENTERCOUNT);
					ASSERT(cbEndCardKind!=FALSE);			
					CopyMemory(GameEnd.cbLastCenterCardData[i],cbEndCardData[i],sizeof(BYTE)*CountArray(cbEndCardData));
				}
			}catch(...)
			{
				TraceMessage("用户过滤v最大牌型");
				ASSERT(FALSE);
			}

			//总下注备份
			LONG lTotalScore[GAME_PLAYER];
			ZeroMemory(lTotalScore,sizeof(lTotalScore));
			CopyMemory(lTotalScore,m_lTotalScore,sizeof(m_lTotalScore));

			//胜利列表
			UserWinList WinnerList[GAME_PLAYER];
			ZeroMemory(WinnerList,sizeof(WinnerList));

			//临时数据
			BYTE bTempData[GAME_PLAYER][MAX_CENTERCOUNT];
			CopyMemory(bTempData,cbEndCardData,GAME_PLAYER*MAX_CENTERCOUNT);

			WORD wWinCount=0;
			try{
				//用户得分顺序
				for (WORD i=0;i<m_wPlayerCount;i++)
				{
					//查找最大用户
					if(!m_GameLogic.SelectMaxUser(bTempData,WinnerList[i],lTotalScore))
					{
						wWinCount=i;
						break;
					}

					//删除胜利数据
					for (WORD j=0;j<WinnerList[i].bSameCount;j++)
					{
						WORD wRemoveId=WinnerList[i].wWinerList[j];
						ASSERT(bTempData[wRemoveId][0]!=0);
						ZeroMemory(bTempData[wRemoveId],sizeof(BYTE)*MAX_CENTERCOUNT);
					}
				}
			}catch(...)
			{
				TraceMessage("用户得分顺序");
				ASSERT(FALSE);
			}

			//强退用户
			for (WORD i=0;i<m_wPlayerCount;i++)
			{
				if(m_cbPlayStatus[i]==FALSE && lTotalScore[i]>0l)
				{					
					WinnerList[wWinCount].wWinerList[WinnerList[wWinCount].bSameCount++] = i;
				}
			}

			//得分变量
			LONG lUserScore[GAME_PLAYER];
			ZeroMemory(lUserScore,sizeof(lUserScore));
			//CopyMemory(lTotalScore,m_lTotalScore,sizeof(m_lTotalScore));

			try
			{
				//得分情况
				for (int i=0;i<m_wPlayerCount-1;i++)
				{
					//胜利人数
					int iWinCount = (int)WinnerList[i].bSameCount;
					if(0 == iWinCount)break;

					//胜利用户得分情况
					for(int j=0;j<iWinCount;j++)
					{
						if(0 == lTotalScore[WinnerList[i].wWinerList[j]])continue;

						if(j>0 && lTotalScore[WinnerList[i].wWinerList[j]] - 
							lTotalScore[WinnerList[i].wWinerList[j-1]] == 0)continue;

						//失败用户失分情况
						for(int k=i+1;k<m_wPlayerCount;k++)
						{
							//失败人数
							if(0 == WinnerList[k].bSameCount)break;

							for(int l=0;l<WinnerList[k].bSameCount;l++)
							{
								//用户已赔空
								if(0 == lTotalScore[WinnerList[k].wWinerList[l]])continue;

								WORD wLostId=WinnerList[k].wWinerList[l];
								WORD wWinId=WinnerList[i].wWinerList[j];
								LONG lMinScore = 0;

								//上家得分数目
								LONG lLastScore = ((j>0)?lTotalScore[WinnerList[i].wWinerList[j-1]]:0);
								if(j>0)ASSERT(lLastScore>0L);							
								lMinScore = min(lTotalScore[wWinId]-lLastScore,lTotalScore[wLostId]);

								for(int m=j;m<iWinCount;m++)
								{
									//得分数目
									lUserScore[WinnerList[i].wWinerList[m]]+=lMinScore/(iWinCount-j);
								}

								//赔偿数目
								lUserScore[wLostId]-=lMinScore;
								lTotalScore[wLostId]-=lMinScore;
							}
						}
					}
				}
			}catch(...)
			{
				TraceMessage("得分数目/赔偿数目");
				ASSERT(FALSE);
			}

			//扣税变量
			WORD wRevenue=m_pGameServiceOption->wRevenue;

			//统计用户分数(税收)
			for(WORD i=0;i<m_wPlayerCount;i++)
			{
				GameEnd.lGameScore[i]=lUserScore[i];
				ASSERT(lUserScore[i]+m_lTotalScore[i]>=0L);
				if(GameEnd.lGameScore[i]>0L)
				{
					GameEnd.lGameTax[i]=GameEnd.lGameScore[i]*wRevenue/100L;
					GameEnd.lGameScore[i]-=GameEnd.lGameTax[i];
				}
			}

			////统计用户分数
			//for(WORD i=0;i<m_wPlayerCount;i++)
			//{
			//	GameEnd.lGameScore[i]=lUserScore[i];
			//	GameEnd.lGameScore[i]-=GameEnd.lGameTax[i];
			//}

			CopyMemory(GameEnd.cbCardData,m_cbHandCardData,sizeof(m_cbHandCardData));

			//发送信息
			m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
			m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));

			//积分变量
			for (WORD i=0;i<GAME_PLAYER;i++)
			{
				if (m_cbPlayStatus[i]==TRUE)
				{
					enScoreKind nScoreKind;
					if(GameEnd.lGameScore[i]==0L)nScoreKind=enScoreKind_Draw;
					else nScoreKind=(GameEnd.lGameScore[i]>0L)?enScoreKind_Win:enScoreKind_Lost;

					//写入积分
					m_pITableFrame->WriteUserScore(i,GameEnd.lGameScore[i],GameEnd.lGameTax[i],nScoreKind);
				}
			}

			//结束游戏
			m_pITableFrame->ConcludeGame();

			return true;
		}
	case GER_NO_PLAYER:		//没有玩家
		{
			//定义变量
			CMD_S_GameEnd GameEnd;
			ZeroMemory(&GameEnd,sizeof(GameEnd));
			GameEnd.cbTotalEnd = 0;

			//效验结果
			WORD wUserCount=0;
			for (WORD i=0;i<GAME_PLAYER;i++)
			{
				if(m_cbPlayStatus[i]!=FALSE)wUserCount++;
			}
			if(wUserCount!=1)
			{
				ASSERT(FALSE);
				TraceMessage("没有玩家//效验结果出错");
			}

			//统计分数
			LONG lScore = 0,lRevenue = 0;
			enScoreKind nScoreKind ;
			WORD wWinner = INVALID_CHAIR;
			for (WORD i = 0;i<GAME_PLAYER;i++)
			{
				if(m_cbPlayStatus[i]==FALSE)
				{
					if(m_lTotalScore[i] > 0L)GameEnd.lGameScore[i]-=m_lTotalScore[i];
					continue;
				}

				wWinner = i;

				////处理税收
				//for (WORD t=0;t<m_wPlayerCount;t++)
				//{
				//	//赢家不用收税
				//	if(wWinner==t)continue;
				//	if(m_lTotalScore[t]>0L)
				//	{
				//		GameEnd.lGameScore[t]=-m_lTotalScore[t];
				//		m_lTotalScore[t]-=m_bUserTax[t];
				//		GameEnd.lGameTax[t] = m_bUserTax[t];
				//	}
				//}

				//总下注数目
				LONG lAllScore = 0L;
				for (WORD j = 0;j<GAME_PLAYER;j++)
				{
					if(wWinner==j)continue;
					lAllScore += m_lTotalScore[j];
				}
				ASSERT(lAllScore>=0);
				GameEnd.lGameScore[i] = lAllScore;

				//统计税收
				if(GameEnd.lGameScore[i]>0L)
				{
					//扣税变量
					WORD wRevenue=m_pGameServiceOption->wRevenue;
					GameEnd.lGameTax[i]=GameEnd.lGameScore[i]*wRevenue/100L;
					GameEnd.lGameScore[i]-=GameEnd.lGameTax[i];
				}

				//构造扑克
				CopyMemory(GameEnd.cbCardData,m_cbHandCardData,sizeof(m_cbHandCardData));

				lScore=GameEnd.lGameScore[i];
				lRevenue= GameEnd.lGameTax[i];
				nScoreKind=(GameEnd.lGameScore[i]>0L)?enScoreKind_Win:enScoreKind_Lost;
			}

			//发送消息
			m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
			m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));

			//写入积分
			if(wWinner<GAME_PLAYER)
			{
				m_pITableFrame->WriteUserScore(wWinner,lScore,lRevenue,nScoreKind);
			}
			else TraceMessage("//写入积分ffff");

			//结束游戏
			m_pITableFrame->ConcludeGame();

			return true;
		}
	case GER_USER_LEFT:
		{
			//效验参数
			ASSERT(pIServerUserItem!=NULL);
			ASSERT(wChairID<m_wPlayerCount);

			//强退处理
			OnUserGiveUp(wChairID);
			return true;
		}
	}
	return false;
}