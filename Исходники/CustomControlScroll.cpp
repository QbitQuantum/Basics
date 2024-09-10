void CCustomControlScroll::Draw(CWindowGc& gc)
	{
	TInt x, y;
	//上图标
	x = iDisplayPoint.iX;
	y = iDisplayPoint.iY;
	if (iBitmapDirection[0])
		gc.BitBlt(TPoint(x, y), iBitmapDirection[0]);
	//下图标
	y += iDisplaySize.iHeight-iBitmapHeight;
	if (iBitmapDirection[1])
		gc.BitBlt(TPoint(x, y), iBitmapDirection[1]);
	//滚动条
	y = iDisplayPoint.iY+iScrollerPosY;
	if (iBitmapScroller)
		gc.BitBlt(TPoint(x, y), iBitmapScroller);
	}