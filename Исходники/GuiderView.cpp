CGuiderView::CGuiderView()
{
	// TODO: 在此处添加构造代码
	CBitmap bmp;
	//bmp.LoadBitmapW(IDB_BITMAP2); ///加载位图
	bmp.LoadBitmapW (131);
	m_brushBackground.CreatePatternBrush(&bmp); ///创建位图画刷
	////////////////////////////////////////////////////////////////////////////
	m_pMemDC=new CDC();
	m_pMemBitmap=new CBitmap();

}