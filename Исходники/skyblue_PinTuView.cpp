void CSkyblue_PinTuView::OnDraw(CDC* pDC)
{
	//a.获取文档数据控制权
	CSkyblue_PinTuDoc* pDoc = (CSkyblue_PinTuDoc*)GetDocument();

	//b.使用内存设备环境memDC
	//  与内存环境关联的内存位图memBmp
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap memBmp;
	memBmp.CreateCompatibleBitmap(pDC,
		pDoc->m_bmpWidth,pDoc->m_bmpHeight);
	memDC.SelectObject(&memBmp);

	//c. 将图像绘制到内存位图memBmp中

	//1.绘制游戏所有当前散乱的方块
	DrawGameBlocks(&memDC);
	//2.绘制空白方块
	DrawBlankBlock(&memDC);
	//3.绘制边界间隔线条
	DrawLines(&memDC);

	//d.整幅图从内存memBmp拷贝到屏幕
	pDC->BitBlt(0,0,pDoc->m_bmpWidth,pDoc->m_bmpHeight,
				&memDC,0,0,SRCCOPY);
}