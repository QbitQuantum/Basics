//调整控件
void CGameFrame::RectifyControl(int nWidth, int nHeight)
{
	//状态判断
	if (m_DlgGamePlaza.m_bInitDialog==false) return;
	if ((nWidth==0)||(nHeight==0)) return;

	//变量定义
	const int nSplitterWidth=__max(6,m_Splitter.GetButtonSize().cx);

	//获取位置
	CRect rcSplitter;
	m_Splitter.GetWindowRect(&rcSplitter);
	ScreenToClient(&rcSplitter);

	//调整拆分条
	if(!m_bHideGameList)
	{
		int nLessPos=nWidth/4,nMaxPos=nWidth/2;
		if (m_bRectify==false)
		{
			m_bRectify=true;
			rcSplitter.left=nLessPos;
			rcSplitter.right=rcSplitter.left+nSplitterWidth;
		}

		//设置拆分范围
		m_Splitter.SetSplitterRange(nLessPos,nMaxPos);
		if ((nWidth!=0)&&(nHeight!=0))
		{
			if (rcSplitter.left<nLessPos) 
			{
				rcSplitter.left=nLessPos;
				rcSplitter.right=rcSplitter.left+nSplitterWidth;
			}
			if (rcSplitter.right>nMaxPos)
			{
				rcSplitter.right=nMaxPos;
				rcSplitter.left=rcSplitter.right-nSplitterWidth;
			}
		}
	}
	else
	{
		//拆分位置
		rcSplitter.left=0;
		rcSplitter.right=rcSplitter.left+nSplitterWidth;
	}

	//位置调整
	rcSplitter.top=m_ImageInfoFrame.nTBorder-FRAME_EXALTATION;
	rcSplitter.bottom=nHeight-m_ImageInfoFrame.nBBorder;

	//分条控件
	HDWP hDwp=BeginDeferWindowPos(32);
	UINT uUserTitleHeight=m_UserInfoView.GetTitleHeight();
	const UINT uFlags=SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOCOPYBITS;
	DeferWindowPos(hDwp,m_Splitter,NULL,rcSplitter.left,rcSplitter.top,rcSplitter.Width(),rcSplitter.Height(),uFlags);

	//列表控件
	if(!m_bHideGameList)
	{
		DeferWindowPos(hDwp,m_ServerItemView,NULL,m_ImageInfoFrame.nLBorder+m_ImageInfoServer.nLBorder,m_ImageInfoFrame.nTBorder+m_ImageInfoServer.nTBorder+uUserTitleHeight-FRAME_EXALTATION,
			rcSplitter.right-m_ImageInfoServer.nLBorder-m_ImageInfoServer.nRBorder-m_ImageInfoFrame.nLBorder,nHeight-m_ImageInfoServer.nTBorder-m_ImageInfoServer.nBBorder-m_ImageInfoFrame.nTBorder-uUserTitleHeight-m_ImageInfoFrame.nBBorder+FRAME_EXALTATION,uFlags);
		DeferWindowPos(hDwp,m_UserCompanionList,NULL,m_ImageInfoFrame.nLBorder+m_ImageInfoServer.nLBorder,m_ImageInfoFrame.nTBorder+m_ImageInfoServer.nTBorder+uUserTitleHeight-FRAME_EXALTATION,
			rcSplitter.right-m_ImageInfoServer.nLBorder-m_ImageInfoServer.nRBorder-m_ImageInfoFrame.nLBorder,nHeight-m_ImageInfoServer.nTBorder-m_ImageInfoServer.nBBorder-m_ImageInfoFrame.nTBorder-uUserTitleHeight-m_ImageInfoFrame.nBBorder+FRAME_EXALTATION,uFlags);
	}

	//信息控件
	DeferWindowPos(hDwp,m_UserInfoView,NULL,m_ImageInfoFrame.nLBorder,m_ImageInfoFrame.nTBorder-FRAME_EXALTATION,rcSplitter.right-m_ImageInfoFrame.nLBorder,uUserTitleHeight,uFlags);

	//获取位置
	CRect rcItemRect;
	m_btGamePlaza.GetWindowRect(&rcItemRect);

	//移动控件
	INT nYPos = m_ImageInfoFrame.nTBorder-FRAME_EXALTATION;
	DeferWindowPos(hDwp,m_btGamePlaza,NULL,rcSplitter.right+5,nYPos,0,0,uFlags|SWP_NOSIZE);
	for (int i=0;i<CountArray(m_btViewItem);i++) DeferWindowPos(hDwp,m_btViewItem[i],NULL,rcSplitter.right+rcItemRect.Width()+rcItemRect.Width()*i+5,nYPos,0,0,uFlags|SWP_NOSIZE);

	//页面控件
	HWND hWndActive=m_pActiveViewItem->GetWindowHandle();
	DeferWindowPos(hDwp,hWndActive,NULL,rcSplitter.right,nYPos+rcItemRect.Height(),nWidth-m_ImageInfoFrame.nRBorder-rcSplitter.right,
		nHeight-(nYPos+rcItemRect.Height())-m_ImageInfoFrame.nBBorder,uFlags);

	//其他控件
	DeferWindowPos(hDwp,m_btMin,NULL,nWidth-102,3,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btMax,NULL,nWidth-72,3,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btClose,NULL,nWidth-42,3,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btExChangeSkin,NULL,nWidth-132,3,0,0,uFlags|SWP_NOSIZE);

	//列表按钮
	m_btListControl1.GetWindowRect(&rcItemRect);
	INT nY = m_ImageInfoFrame.nTBorder-FRAME_EXALTATION+uUserTitleHeight+5;
	DeferWindowPos(hDwp,m_btListControl1,NULL,m_ImageInfoFrame.nLBorder+5,nY,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btListControl2,NULL,m_ImageInfoFrame.nLBorder+5,nY+rcItemRect.Height()+1,0,0,uFlags|SWP_NOSIZE);

	//按钮位置
	CRect rcButton;
	m_btButton1.GetWindowRect(&rcButton);

	//间隔计算
	int nEndPos=105;
	int nBeginPos=560;
	int nWindth=nWidth-nBeginPos-rcButton.Width()*5-nEndPos;
	int nButtonSpace=__min((nWidth-nBeginPos-rcButton.Width()*5-nEndPos)/4,30);

	//广告控件
	// modify by 一剑
	//DeferWindowPos(hDwp,m_BrowerAD,NULL,300,8,250,52,uFlags);

	//导航按钮
	DeferWindowPos(hDwp,m_btButton1,NULL,nWidth-rcButton.Width()*5-nButtonSpace*4-nEndPos,6,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btButton2,NULL,nWidth-rcButton.Width()*4-nButtonSpace*3-nEndPos,6,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btButton3,NULL,nWidth-rcButton.Width()*3-nButtonSpace*2-nEndPos,6,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btButton4,NULL,nWidth-rcButton.Width()*2-nButtonSpace*1-nEndPos,6,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btButton5,NULL,nWidth-rcButton.Width()*1-nButtonSpace*0-nEndPos,6,0,0,uFlags|SWP_NOSIZE);

	//获取位置
	CRect rcButtonRect;
	m_btSelfOption.GetWindowRect(&rcButtonRect);

	//移动控件
	nYPos = m_ImageInfoFrame.nTBorder-FRAME_EXALTATION-4;
	CButton * pButton[]={/*&m_btQuitGame,*/&m_btSelfOption,&m_btGlobalOption,&m_btSwitchUser};
	for (int i=0;i<CountArray(pButton);i++) DeferWindowPos(hDwp,pButton[i]->m_hWnd,NULL,nWidth-(rcButtonRect.Width()+6)*(i+1)-8,nYPos,0,0,uFlags|SWP_NOSIZE);

	//结束调整
	LockWindowUpdate();
	EndDeferWindowPos(hDwp);
	UnlockWindowUpdate();

	//更换皮肤
	int i=0;
	for (;i<CountArray(m_btViewItem);i++)
	{
		if(m_pActiveViewItem==m_pRoomViewItem[i])break;
	}
	CSkinButton * pTempButton[]={&m_btViewItem[0],&m_btViewItem[1],&m_btViewItem[2],&m_btGamePlaza};
	ASSERT((CountArray(m_btViewItem)+1)==CountArray(pTempButton));
	for (WORD j=0;j<CountArray(pTempButton);j++)
	{
		if(i==j)
		{
			pTempButton[j]->SetTextColor(RGB(0,0,0),RGB(133,215,255),true);
			pTempButton[j]->SetButtonImage(GetPlatformRes().uBtFrameItemActive,GetResInstanceHandle(),false);
		}
		else
		{
			pTempButton[j]->SetTextColor(RGB(245,245,245),RGB(20,20,20),true);
			pTempButton[j]->SetButtonImage(GetPlatformRes().uBtFrameItemNormal,GetResInstanceHandle(),false);
		}
	}

	return;
}