void CMFCWorldView::OnDraw(CDC* pDC)
{
	//获取文档
	CMFCWorldDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//准备内存绘图缓冲区
	CDC MemDC;
	CBitmap MemBitmap;
	MemDC.CreateCompatibleDC(NULL);//创建绘图设备
	//绘图区域大小，可以像这样中直接使用窗口大小，也可以自己计算需要多大的区域
	MemBitmap.CreateCompatibleBitmap(pDC,870,510);CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);//创建绘图区
	MemDC.FillSolidRect(0,0,870,510,RGB(255,255,255));//初始化
	//读取文档
	char** p;
	p = pDoc->getmap(5);
	//画刷定义
	int wallc=RGB(0,0,0);//墙是黑色
	CBrush wallBrush(wallc);
	int playc=RGB(0,255,0);//玩家是绿色
	CBrush playBrush(playc);
	int exitc=RGB(255,0,0);//出口是红色
	CBrush exitBrush(exitc);
	CBrush *oldBrush;
	//缓冲区绘图
	for (int i = 0; i <= 2*MM; ++i)
	{
		for (int j = 0; j <= 2*NN; ++j)
		{
			switch (p[j][i])
			{
			case WALL:
				oldBrush = MemDC.SelectObject(&wallBrush);
				MemDC.Rectangle(Start+i*cubelong,Start+j*cubelong,Start+(i+1)*cubelong,Start+(j+1)*cubelong);
				MemDC.SelectObject(oldBrush);
				break;
			case PLAY:
				oldBrush = MemDC.SelectObject(&playBrush);
				MemDC.Rectangle(Start+i*cubelong,Start+j*cubelong,Start+(i+1)*cubelong,Start+(j+1)*cubelong);
				MemDC.SelectObject(oldBrush);
				break;
			case EXIT:
				oldBrush = MemDC.SelectObject(&exitBrush);
				MemDC.Rectangle(Start+i*cubelong,Start+j*cubelong,Start+(i+1)*cubelong,Start+(j+1)*cubelong);
				MemDC.SelectObject(oldBrush);
			}
		}
	}
	//将内存中的图拷贝到屏幕上进行显示 
	pDC->BitBlt(0,0,870,510,&MemDC,0,0,SRCCOPY); 
	//绘图完成后的清理 
	MemBitmap.DeleteObject(); 
	MemDC.DeleteDC(); 

}