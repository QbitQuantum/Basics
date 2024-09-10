//重画函数
void CChessBorad::OnPaint()
{
	CPaintDC dc(this);

	//获取大小
	CRect rcClient;
	GetClientRect(&rcClient);

	//创建缓冲图
	CDC BufferDC;
	CBitmap BufferBmp;
	BufferDC.CreateCompatibleDC(&dc);
	BufferBmp.CreateCompatibleBitmap(&dc,rcClient.Width(),rcClient.Height());
	BufferDC.SelectObject(&BufferBmp);

	//设置 DC
	BufferDC.SetBkMode(TRANSPARENT);
	BufferDC.SetTextColor(RGB(200,0,0));
	BufferDC.SelectObject(CSkinResourceManager::GetDefaultFont());
	//绘画棋盘
	CImageHandle BoradHandle(&m_ImageBorad);
	m_ImageBorad.BitBlt(BufferDC,0,0);

	//棋子名字
	LPCTSTR pszChessName[]={TEXT("王"),TEXT("后"),TEXT("车"),TEXT("象"),TEXT("马"),TEXT("士")};

	//绘画棋子
	CImageHandle FrameHandle(&m_ImageFrame);
	CImageHandle ChessHandle(&m_ImageChess);
	int nXPosImage=0,nYPosImage=0,nXBoradPos=0,nYBoradPos=0;
	for (BYTE cbXPos=0;cbXPos<8;cbXPos++)
	{
		for (BYTE cbYPos=0;cbYPos<8;cbYPos++)
		{
			//计算位置
			nXBoradPos=GetChessXPos(cbXPos);
			nYBoradPos=GetChessYPos(cbYPos);
			tagChessItem * pChessItem=m_ChessBorad[cbXPos][cbYPos];

			//绘画棋子
			if (pChessItem!=NULL)
			{
				nXPosImage=(pChessItem->cbChess-1)*CHESS_WIDTH;
				nYPosImage=(pChessItem->cbColor-1)*CHESS_HEIGHT;
				m_ImageChess.AlphaDrawImage(&BufferDC,nXBoradPos+(SPACE_BORAD_X-CHESS_WIDTH)/2,
					nYBoradPos+(SPACE_BORAD_Y-CHESS_HEIGHT)/2,CHESS_WIDTH,CHESS_HEIGHT,
					nXPosImage,nYPosImage,RGB(255,0,255));
			}

			//绘画框架
			bool bFrame=((cbXPos==m_cbXPosStart)&&(cbYPos==m_cbYPosStart));
			if (bFrame==false) bFrame=((cbXPos==m_cbXPosSelect)&&(m_cbYPosSelect==cbYPos));
			if (bFrame==false) bFrame=((cbXPos==m_cbXPosTerminal)&&(cbYPos==m_cbYPosTerminal));
			if (bFrame==true) m_ImageFrame.AlphaDrawImage(&BufferDC,nXBoradPos,nYBoradPos,RGB(255,0,255));

			//绘画棋字
			if ((m_bShowChessName==true)&&(pChessItem!=NULL))
			{
				LPCTSTR pszTitle=pszChessName[pChessItem->cbChess-1];
				BufferDC.SetTextColor(((cbXPos+cbYPos)%2==1)?RGB(255,255,255):RGB(200,0,0));
				BufferDC.TextOut(nXBoradPos+5,nYBoradPos+5,pszTitle,lstrlen(pszTitle));
			}
		}
	}

	//绘画界面
	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),&BufferDC,0,0,SRCCOPY);

	//清理资源
	BufferBmp.DeleteObject();
	BufferDC.DeleteDC();

	return;
}