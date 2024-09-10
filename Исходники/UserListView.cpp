//获取字符
LPCTSTR CUserListView::GetDisplayText(IUserItem * pIUserItem, WORD wColumnPos)
{
	//效验参数
	ASSERT(pIUserItem!=NULL);
	if (wColumnPos>=m_wColumnCount) return NULL;

	//变量定义
	static TCHAR szBuffer[512];
	tagUserData * pUserData=pIUserItem->GetUserData();

	//生成显示
	switch (m_wDataDescribe[wColumnPos])
	{
	case DTP_USER_ID:			//用户 ID
		{
			_snprintf_s(szBuffer,sizeof(szBuffer),TEXT("%ld"),pIUserItem->GetUserData()->dwUserID);
			return szBuffer;
		}
	case DTP_GAME_ID:			//游戏 ID
		{
			_snprintf_s(szBuffer,sizeof(szBuffer),TEXT("%ld"),pIUserItem->GetUserData()->dwGameID);
			return szBuffer;
		}
	case DTP_INSURE_SCORE:		//存储金币
		{
			_snprintf_s(szBuffer,sizeof(szBuffer),TEXT("%ld"),pIUserItem->GetUserData()->lInsureScore);
			return szBuffer;
		}
	case DTP_GAME_GOLD:			//游戏金币
		{
			_snprintf_s(szBuffer,sizeof(szBuffer),TEXT("%ld"),pIUserItem->GetUserData()->lGameGold);
			return szBuffer;
		}
	case DTP_LOVE_LINESS:		//用户魅力
		{
			_snprintf_s(szBuffer,sizeof(szBuffer),TEXT("%ld"),pIUserItem->GetUserData()->lLoveliness);
			return szBuffer;
		}
	case DTP_USER_ACCOUNTS:		//用户名字
		{
			return pIUserItem->GetUserData()->szName;
		}
	case DTP_UNDER_WRITE:		//个性签名
		{
			return pIUserItem->GetUserData()->szUnderWrite;
		}
	case DTP_USER_TABLE:		//游戏桌号
		{
			WORD wTableID=pUserData->wTableID;
			if (wTableID!=INVALID_TABLE) _snprintf_s(szBuffer,sizeof(szBuffer),TEXT("%3d"),wTableID+1);
			else szBuffer[0]=0;
			return szBuffer;
		}
	case DTP_USER_SCORE:		//用户积分
		{
			_snprintf_s(szBuffer,sizeof(szBuffer),TEXT("%ld"),pUserData->lScore);
			return szBuffer;
		}
	case DTP_USER_EXPERIENCE:	//用户经验
		{
			_snprintf_s(szBuffer,sizeof(szBuffer),TEXT("%ld"),pUserData->lExperience);
			return szBuffer;
		}
	case DTP_USER_WIN:			//胜局盘数
		{
			_snprintf_s(szBuffer,sizeof(szBuffer),TEXT("%ld"),pUserData->lWinCount);
			return szBuffer;
		}
	case DTP_USER_LOST:			//输局盘数
		{
			_snprintf_s(szBuffer,sizeof(szBuffer),TEXT("%ld"),pUserData->lLostCount);
			return szBuffer;
		}
	case DTP_USER_DRAW:			//和局盘数
		{
			_snprintf_s(szBuffer,sizeof(szBuffer),TEXT("%ld"),pUserData->lDrawCount);
			return szBuffer;
		}
	case DTP_USER_FLEE:			//逃局盘数
		{
			_snprintf_s(szBuffer,sizeof(szBuffer),TEXT("%ld"),pUserData->lFleeCount);
			return szBuffer;
		}
	case DTP_USER_PLAY_COUNT:	//总局盘数
		{
			_snprintf_s(szBuffer,sizeof(szBuffer),TEXT("%ld"),pIUserItem->GetUserPlayCount());
			return szBuffer;
		}
	case DTP_WIN_RATE:			//用户胜率
		{
			if (pUserData->lWinCount>0)
			{
				LONG lAllCount=pIUserItem->GetUserPlayCount();
				double dWinRate=(double)(pUserData->lWinCount*100)/(double)lAllCount;
				if (dWinRate>=0.01) _snprintf_s(szBuffer,sizeof(szBuffer),TEXT("%5.2f%%"),dWinRate);
				else szBuffer[0]=0;
			}
			else szBuffer[0]=0;
			return szBuffer;
		}
	case DTP_LOST_RATE:			//用户输率
		{
			if (pUserData->lLostCount>0)
			{
				LONG lAllCount=pIUserItem->GetUserPlayCount();
				double dLostRate=(double)(pUserData->lLostCount*100)/(double)lAllCount;
				if (dLostRate>=0.01) _snprintf_s(szBuffer,sizeof(szBuffer),TEXT("%5.2f%%"),dLostRate);
				else szBuffer[0]=0;
			}
			else szBuffer[0]=0;
			return szBuffer;
		}
	case DTP_DRAW_RATE:			//用户和率
		{
			if (pUserData->lDrawCount>0)
			{
				LONG lAllCount=pIUserItem->GetUserPlayCount();
				double dDrawRate=(double)(pUserData->lDrawCount*100)/(double)lAllCount;
				if (dDrawRate>=0.01) _snprintf_s(szBuffer,sizeof(szBuffer),TEXT("%5.2f%%"),dDrawRate);
				else szBuffer[0]=0;
			}
			else szBuffer[0]=0;
			return szBuffer;
		}
	case DTP_FLEE_RATE:			//用户逃率
		{
			if (pUserData->lFleeCount>0)
			{
				LONG lAllCount=pIUserItem->GetUserPlayCount();
				double dFleeRate=(double)(pUserData->lFleeCount*100)/(double)lAllCount;
				if (dFleeRate>=0.01) _snprintf_s(szBuffer,sizeof(szBuffer),TEXT("%5.2f%%"),dFleeRate);
				else szBuffer[0]=0;
			}
			else szBuffer[0]=0;
			return szBuffer;
		}
	case DTP_GAME_LEVEL:		//游戏等级
		{
			szBuffer[0]=0;
			if (m_GameRankManager.GetInterface()!=NULL)
			{
				LPCTSTR pszGameRank=m_GameRankManager->GetLevelDescribe(pIUserItem->GetUserData()->lScore);
				lstrcpyn(szBuffer,pszGameRank,sizeof(szBuffer));
			}
			return szBuffer;
		}
	}

	//默认显示
	szBuffer[0]=0;

	return szBuffer;
}