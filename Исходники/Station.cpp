//重画函数
void CStation::OnPaint() 
{
	CPaintDC dc(this); 

	//建立缓冲
	CDC BufferDC;
	CRect ClientRect;
	CFont LittleFont, * pOldFont=NULL;
	CBitmap BufferBmp, * pOldBmp=NULL;
	GetClientRect(&ClientRect);
	BufferBmp.CreateCompatibleBitmap(&dc,ClientRect.Width(),ClientRect.Height());
	BufferDC.CreateCompatibleDC(&dc);
	pOldBmp=BufferDC.SelectObject(&BufferBmp);
	LittleFont.CreateFont(-12,0,0,0,400,NULL,NULL,NULL,134,3,2,1,2,TEXT("宋体"));
	pOldFont=BufferDC.SelectObject(&LittleFont);

	//绘画背景
	DrawBmp(&BufferDC,0,0,IDB_ST_BACK,TY_TILE,&ClientRect);
	DrawBmp(&BufferDC,230,0,IDB_USERINFO,TY_TRAN,&ClientRect);
	DrawBmp(&BufferDC,620,0,IDB_USERINFO,TY_TRAN,&ClientRect);
	DrawBmp(&BufferDC,0,5,IDB_ST_LOGO,TY_HCENTER|TY_VCENTER,&ClientRect);
	DrawBmp(&BufferDC,-70,0,IDB_ST_BALL_CTL,TY_VCENTER|TY_RIGHT,&ClientRect);
	DrawBmp(&BufferDC,(int)m_iXBallPos-156,30-(int)m_iYBallPos,IDB_ST_BALL_POINT,TY_TRAN|TY_RIGHT,&ClientRect);
	//绘画用户
	TCHAR szBuffer[20];
	BufferDC.SetBkMode(TRANSPARENT);
	BufferDC.SetTextColor(RGB(0,0,0));
	BufferDC.SetTextAlign(TA_LEFT|TA_TOP);
	BufferDC.TextOut(ClientRect.Width()/2-220,15,TEXT("目标球"));
	BufferDC.TextOut(ClientRect.Width()/2-220,36,TEXT("  得分"));
	const tagUserData *pUserData = g_DrawInfo.pPlayView->GetUserInfo(0);
	if(pUserData)
	{
		BufferDC.TextOut(ClientRect.Width()/2-260,STATION_WND_HIGHT-27,pUserData->szName);
		g_DrawInfo.pPlayView->DrawUserFace(&BufferDC,
								//pUserData->wFaceID,
								pUserData,
								ClientRect.Width()/2-260,
								8,
								pUserData->cbUserStatus==US_OFFLINE);
		if (m_iTargetBall[0]!=255) 
			DrawBmp(&BufferDC,ClientRect.Width()/2-165,8,IDB_BALL_A,TY_TRAN,&ClientRect,m_iTargetBall[0]*((int)(BALL_RADII_A)*2+1),0,(int)(BALL_RADII_A)*2,BALL_BACK_COLOR);
		BufferDC.SetTextAlign(TA_LEFT|TA_TOP);
		sprintf(szBuffer,TEXT("%d 分"),m_iPoint[0]);
		BufferDC.SetTextColor(RGB(0,0,0));
		BufferDC.TextOut(ClientRect.Width()/2-170,36,szBuffer);
		WORD wUserTimer = g_DrawInfo.pPlayView->GetUserTimer(0);
		if(wUserTimer) 
		{
			g_DrawInfo.pPlayView->DrawUserTimer(&BufferDC,
								ClientRect.Width()/2-138,
								10,
								wUserTimer);
		}
		if(pUserData->cbUserStatus==US_READY&&!m_IsTrain) 
		{
			g_DrawInfo.pPlayView->DrawUserReady(&BufferDC,
								ClientRect.Width()/2-145,
								13);
		}
	}
	BufferDC.SetTextAlign(TA_LEFT|TA_TOP);
	BufferDC.TextOut(ClientRect.Width()/2+180,15,TEXT("目标球"));
	BufferDC.TextOut(ClientRect.Width()/2+180,36,TEXT("  得分"));
	pUserData = g_DrawInfo.pPlayView->GetUserInfo(1);
	if(pUserData)
	{
		BufferDC.TextOut(ClientRect.Width()/2+130,STATION_WND_HIGHT-27,pUserData->szName);
		g_DrawInfo.pPlayView->DrawUserFace(&BufferDC,
								//pUserData->wFaceID,
								pUserData,
								ClientRect.Width()/2+130,
								8,
								pUserData->cbUserStatus==US_OFFLINE);
		if (m_iTargetBall[1]!=255) 
			DrawBmp(&BufferDC,ClientRect.Width()/2+220,8,IDB_BALL_A,TY_TRAN,&ClientRect,m_iTargetBall[1]*((int)(BALL_RADII_A)*2+1),0,(int)(BALL_RADII_A)*2,BALL_BACK_COLOR);
		BufferDC.SetTextAlign(TA_LEFT|TA_TOP);
		sprintf(szBuffer,TEXT("%d 分"),m_iPoint[1]);
		BufferDC.SetTextColor(RGB(0,0,0));
		BufferDC.TextOut(ClientRect.Width()/2+228,36,szBuffer);
		WORD wUserTimer = g_DrawInfo.pPlayView->GetUserTimer(1);
		if(wUserTimer) 
		{
			g_DrawInfo.pPlayView->DrawUserTimer(&BufferDC,
								ClientRect.Width()/2+250,
								10,
								wUserTimer);
		}
		if(pUserData->cbUserStatus==US_READY&&!m_IsTrain) 
		{
			g_DrawInfo.pPlayView->DrawUserReady(&BufferDC,
								ClientRect.Width()/2+258,
								13);
		}
	}
	//画力量
	BufferDC.MoveTo(ClientRect.Width()-131,56);
	BufferDC.LineTo(ClientRect.Width()-131+(int)m_iXAnglePos,(int)m_iYAnglePos+56);
	BufferDC.SetTextColor(RGB(255,0,255));
	CString strAngle;
	strAngle.Format("%d 度",(int)((acos(m_iXAnglePos/41)*180)/3.14));
	BufferDC.TextOut(ClientRect.Width()-111,10,strAngle);
	BufferDC.FillSolidRect(ClientRect.Width()-182,58,97,5,RGB(0,0,0));
	BufferDC.FillSolidRect(ClientRect.Width()-182,58,(int)(g_DrawInfo.m_iPowerPos*100),5,RGB(255,100,25));
	BufferDC.FillSolidRect(ClientRect.Width()-182,58,iPos,5,RGB(255,0,255));
	//画主界面
	dc.BitBlt(0,0,ClientRect.Width(),ClientRect.Height(),&BufferDC,0,0,SRCCOPY);
	//清理
	BufferDC.SelectObject(pOldBmp);
	BufferDC.SelectObject(pOldFont);
	return;
}