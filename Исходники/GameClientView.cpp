//绘画界面
void CGameClientView::DrawGameView(CDC * pDC, int nWidth, int nHeight)
{
	CString strFile,strTemp;
	CTime tmCur = CTime::GetCurrentTime();
	CString strTime = tmCur.Format("%m%d");
	strFile.Format("log\\%sDrawGameView.log",strTime);

	if (nWidth > 0 && nWidth < 1500)
	{
		if (xOffInt != nWidth)
		{
			xOffInt=nWidth;
			yOffInt=nHeight;

			AfxGetMainWnd()->SendMessage(IDM_RESET_UI, nWidth, nHeight);
		}

	}
	//绘画背景
	DrawViewImage(pDC,m_ImageBack,enMode_Spread);
	int iXPos;
	int iYPos;
	for (int i=0; i < GAME_PLAYER; i++)
	{
		iXPos=	m_PtVideo[i].x;
		iYPos=m_PtVideo[i].y;

		if ( 1 == m_uVideoInt[i])
		DrawOtherVideoPic(  pDC,  iXPos,  iYPos);
	}//End for

	//自己
	int myX,myY,myW,myH;
	myW= MYSLEF_VIDEO_W;
	myH= MYSLEF_VIDEO_H;
	myX=  10-3;//
	myY=  nHeight-myH-10-35; 
	DrawMyselfVideoPic( pDC,  myX,  myY);
	//绘画用户
	pDC->SetTextColor(RGB(255,255,0));
	for (WORD i=0;i<GAME_PLAYER;i++)
	{
		//变量定义
		const tagUserData * pUserData=GetUserInfo(i);
		if (pUserData!=NULL)
		{
			//用户名字
			pDC->SetTextAlign((i==1)?(TA_RIGHT|TA_TOP):(TA_LEFT|TA_TOP));
			DrawTextString(pDC,pUserData->szName,RGB(240,240,240),RGB(50,50,50),m_ptNameNew[i].x,m_ptName[i].y);

			if( m_tDice>0 && m_tDice<12)
			{
				ActionDice1( pDC,m_tDice);

				strTemp.Format("ActionDice1 ");
				theApp.WriteLog(strFile, strTemp);

			}
			else
			{
				if( m_tDice== 12)
				{
					ActionDice2( pDC,m_nDiceCount1,m_nDiceCount2);
					strTemp.Format("ActionDice2  m_nDiceCount1=%d,m_nDiceCount2=%d", m_nDiceCount1,m_nDiceCount2);
					theApp.WriteLog(strFile, strTemp);
		//	m_tDice++;
				}//End if
			}//End if
			//其他信息
			WORD wUserTimer=GetUserTimer(i);
			if (wUserTimer!=0) DrawUserTimer(pDC,m_ptTimer[i].x,m_ptTimer[i].y,wUserTimer);
			if (pUserData->cbUserStatus==US_READY) DrawUserReady(pDC,m_ptReady[i].x,m_ptReady[i].y);
			//DrawUserFace(pDC,pUserData->wFaceID,m_ptFace[i].x,m_ptFace[i].y,pUserData->cbUserStatus==US_OFFLINE);
			//画听标记
			if( m_bTingFlag[i] )
			{
				ShowTingPic( pDC, m_ptFace[i].x,m_ptFace[i].y);
			}//End if
		}
	}

	//用户标志
	if (m_wBankerUser!=INVALID_CHAIR)
	{
		//加载位图
		CImageHandle ImageHandle(&m_ImageUserFlag);
		int nImageWidth=m_ImageUserFlag.GetWidth()/4;
		int nImageHeight=m_ImageUserFlag.GetHeight();

		//绘画标志
		for (WORD i=0;i<GAME_PLAYER;i++)
		{
			WORD wIndex=((i+GAME_PLAYER)-m_wBankerUser)%GAME_PLAYER;
			m_ImageUserFlag.BitBlt(pDC->m_hDC,m_UserFlagPos[i].x,m_UserFlagPos[i].y,nImageWidth,nImageHeight,nImageWidth*wIndex,0);
		}
	}

	//桌面麻将
	for (WORD i=0;i<4;i++)
	{
		m_TableCard[i].DrawCardControl(pDC);
		m_DiscardCard[i].DrawCardControl(pDC);
		m_WeaveCard[i][0].DrawCardControl(pDC);
		m_WeaveCard[i][1].DrawCardControl(pDC);
		m_WeaveCard[i][2].DrawCardControl(pDC);
		m_WeaveCard[i][3].DrawCardControl(pDC);
	}

	//堆积麻将
	m_HeapCard[3].DrawCardControl(pDC);
	m_HeapCard[0].DrawCardControl(pDC);
	m_HeapCard[1].DrawCardControl(pDC);
	m_HeapCard[2].DrawCardControl(pDC);

	//用户麻将
	m_UserCard[0].DrawCardControl(pDC);
	m_UserCard[1].DrawCardControl(pDC);
	m_UserCard[2].DrawCardControl(pDC);
	m_HandCardControl.DrawCardControl(pDC);

	//出牌提示
	if (m_bOutCard==true)
	{
		CImageHandle HandleOutCard(&m_ImageOutCard);
		m_ImageOutCard.AlphaDrawImage(pDC,(nWidth-m_ImageOutCard.GetWidth())/2,nHeight-150,RGB(255,0,255));
		//显示听牌
		if ( !m_bTingFlag[2] )
		{
			m_btTingCard.ShowWindow(SW_SHOW);
		}
		else
		{
			m_btTingCard.ShowWindow(SW_HIDE);
		}
	}
	else
	{
		m_btTingCard.ShowWindow(SW_HIDE);
	}

	//等待提示
	if (m_bWaitOther==true)
	{
		CImageHandle HandleWait(&m_ImageWait);
		m_ImageWait.AlphaDrawImage(pDC,(nWidth-m_ImageWait.GetWidth())/2,nHeight-150,RGB(255,0,255));
	}

	//荒庄标志
	if (m_bHuangZhuang==true)
	{
		CImageHandle HandleHuangZhuang(&m_ImageHuangZhuang);
		m_ImageHuangZhuang.AlphaDrawImage(pDC,(nWidth-m_ImageHuangZhuang.GetWidth())/2,nHeight/2-103,RGB(255,0,255));
	}

	//用户状态
	for (WORD i=0;i<GAME_PLAYER;i++)
	{
		if ((m_wOutCardUser==i)||(m_cbUserAction[i]!=0))
		{
			//计算位置
			int nXPos=0,nYPos=0;
			switch (i)
			{
			case 0:	//北向
				{
					nXPos=nWidth/2-32;
					nYPos=m_nYBorder+95;
					break;
				}
			case 1:	//东向
				{
					nXPos=nWidth-m_nXBorder-170;
					nYPos=nHeight/2-71;
					break;
				}
			case 2:	//南向
				{
					nXPos=nWidth/2-32;
					nYPos=nHeight-m_nYBorder-220;
					break;
				}
			case 3:	//西向
				{
					nXPos=m_nXBorder+115;
					nYPos=nHeight/2-71 -45;
					break;
				}
			}

			//动作背景
			CImageHandle ImageHandle(&m_ImageActionBack);
			m_ImageActionBack.AlphaDrawImage(pDC,nXPos,nYPos,m_ImageActionBack.GetWidth()/4,m_ImageActionBack.GetHeight(),
				i*m_ImageActionBack.GetWidth()/4,0,RGB(255,0,255));

			//绘画动作
			if (m_cbUserAction[i]!=WIK_NULL)
			{
				//变量定义
				int nXImagePos=0;
				CImageHandle ImageHandle(&m_ImageUserAction);
				int nItemWidth=m_ImageUserAction.GetWidth()/7;

				//计算位置
				if (m_cbUserAction[i]&WIK_PENG) nXImagePos=nItemWidth;
				else if (m_cbUserAction[i]&WIK_FILL) nXImagePos=nItemWidth*2;
				else if (m_cbUserAction[i]&WIK_GANG) nXImagePos=nItemWidth*3;
				else if (m_cbUserAction[i]&WIK_CHI_HU) nXImagePos=nItemWidth*4;

				//绘画动作
				int nItemHeight=m_ImageUserAction.GetHeight();
				m_ImageUserAction.BitBlt(pDC->m_hDC,nXPos+13,nYPos+15,nItemWidth,nItemHeight,nXImagePos,0);
			}
			else
			{
				//如果已经听了，而且打了第一张出去
				if ( m_IntFirstTingFlag[i]==1 && m_bTingFlag[i] )
				{
					//绘画麻将
					g_CardResource.m_ImageTableBottom.DrawCardItem(pDC,0,nXPos+18,nYPos+15);
				}
				else
				{
					//绘画麻将
					g_CardResource.m_ImageTableBottom.DrawCardItem(pDC,m_cbCardData,nXPos+18,nYPos+15);
				}
			}
		}
	}

	return;
}