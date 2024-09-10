void CTalk::OnDraw(CDC &dc)
{
	//边框
	int nWidth = 6;
	CRect Rect(CPoint(300, 200), CSize(nWidth * TILE_WIDTH, 2 * TILE_HEIGHT));
	int i, j;
	for(i = 0; i < Rect.Width() / TILE_WIDTH; i++)
	{
		for(j = 0; j < Rect.Height() / TILE_HEIGHT; j++)
		{
			Tile.Draw(dc, Rect.left + i * TILE_WIDTH, Rect.top + j * TILE_HEIGHT, TILE_FLOOR);
		}
	}	
	COLORREF crBorderColor = BORDER_COLOR;
	int nBorderWidth = 5;
	CBrush Brush(crBorderColor);	
	for(i = 0; i < nBorderWidth; i++)
	{
		Rect.InflateRect(1, 1);
		dc.FrameRect(&Rect, &Brush);
	}

	//设置显示字体	
	int nFontSize = 12;

	//显示说话内容
	CFont Font;	
	Font.CreatePointFont(nFontSize * 10, "Roman");
	dc.SelectObject(&Font);
	dc.SetTextColor(RGB(255, 180, 0));
	dc.SetBkMode(TRANSPARENT);
	Tile.Draw(dc, Rect.left + TILE_WIDTH / 4, Rect.top + TILE_HEIGHT / 4, Talk[m_idTalk].idTile[nTileIndex]);
	dc.TextOut(Rect.left + TILE_WIDTH + TILE_WIDTH / 2 , Rect.top + TILE_HEIGHT / 2, Talk[m_idTalk].szName, strlen(Talk[m_idTalk].szName));
	dc.TextOut(Rect.left + TILE_WIDTH + TILE_WIDTH / 2 + nFontSize * 4, Rect.top + TILE_HEIGHT / 2, Talk[m_idTalk].szSentence1, strlen(Talk[m_idTalk].szSentence1));
	dc.TextOut(Rect.left + TILE_WIDTH / 2, Rect.top + TILE_HEIGHT / 2 + nFontSize + 8, Talk[m_idTalk].szSentence2, strlen(Talk[m_idTalk].szSentence2));

	//显示闪烁space
	CFont SpaceFont;
	SpaceFont.CreatePointFont(90, "Roman");
	dc.SelectObject(&SpaceFont);
	static bool bChange = true;
	COLORREF Color = (bChange = !bChange) ? RGB(102, 102, 102) : RGB(155, 155, 155);
	dc.SetTextColor(Color);
	dc.SetBkMode(TRANSPARENT);
	dc.TextOut(Rect.right - TILE_WIDTH, Rect.bottom - 20, "space", 5);

	/*
	UINT nLineNo;
	for(nLineNo = 0; nLineNo < strlen(Talk[m_idTalk].szSentence) / nMaxWord; nLineNo++)
	{
		dc.TextOut(Rect.left + TILE_WIDTH + TILE_WIDTH / 2 , Rect.top + TILE_HEIGHT / 2 + nLineNo * nFontSize, Talk[m_idTalk].szSentence + nMaxWord * i, nMaxWord);
	}
	dc.TextOut(Rect.left + TILE_WIDTH + TILE_WIDTH / 2 , Rect.top + TILE_HEIGHT / 2, Talk[m_idTalk].szSentence, strlen(Talk[m_idTalk].szSentence) % nMaxWord);
	dc.TextOut(Rect.right - TILE_WIDTH , Rect.top + TILE_HEIGHT / 2 + (strlen(Talk[m_idTalk].szSentence) / nMaxWord + 1) * nFontSize, Talk[m_idTalk].szSentence, strlen(Talk[m_idTalk].szSentence) % nMaxWord);
	*/
}