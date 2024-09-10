//重画函数
void CGameScoreWnd::OnPaint()
{
	CPaintDC dc(this);

	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//创建缓冲
	CDC BufferDC;
	CBitmap ImageBuffer;
	BufferDC.CreateCompatibleDC(&dc);
	ImageBuffer.CreateCompatibleBitmap(&dc,rcClient.Width(),rcClient.Height());
	BufferDC.SelectObject(&ImageBuffer);

	//绘画背景
	CImageHandle BackImageHandle(&m_ImageBack);
	m_ImageBack.BitBlt(BufferDC,0,0);

	//设置 DC
	BufferDC.SetBkMode(TRANSPARENT);
	BufferDC.SetTextColor(RGB(230,230,230));
	BufferDC.SelectObject(CSkinAttribute::m_DefaultFont);

	//绘画麻将
	g_CardResource.m_ImageUserBottom.DrawCardItem(&BufferDC,m_GameScoreInfo.cbChiHuCard,85,23);

	//用户成绩
	CRect rcDraw;
	TCHAR szBuffer[64];
	for (int i=0;i<GAME_PLAYER;i++)
	{
		//用户名字
		rcDraw.left=25;
		rcDraw.right=125;
		rcDraw.top=125+i*25;
		rcDraw.bottom=rcDraw.top+12;
		BufferDC.DrawText(m_GameScoreInfo.szUserName[i],lstrlen(m_GameScoreInfo.szUserName[i]),&rcDraw,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);

		//用户积分
		rcDraw.left=130;
		rcDraw.right=170;
		rcDraw.top=125+i*25;
		rcDraw.bottom=rcDraw.top+12;
		_snprintf(szBuffer,sizeof(szBuffer),TEXT("%ld"),m_GameScoreInfo.lScore[i]);
		BufferDC.DrawText(szBuffer,lstrlen(szBuffer),&rcDraw,DT_CENTER|DT_VCENTER|DT_SINGLELINE);

		//用户状态
		if (m_GameScoreInfo.wCardType[i]!=0) BufferDC.TextOut(180,125+i*25,TEXT("胡牌"),4);
		else if (m_GameScoreInfo.wProvideUser==i) BufferDC.TextOut(180,125+i*25,TEXT("放炮"),4);

		//其他信息
		if (m_GameScoreInfo.wBankerUser==i) BufferDC.TextOut(228,125+i*25,TEXT("是"),2);
	}

	//绘画界面
	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),&BufferDC,0,0,SRCCOPY);

	//清理资源
	BufferDC.DeleteDC();
	ImageBuffer.DeleteObject();

	return;
}