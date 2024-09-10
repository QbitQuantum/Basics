void CMFC_DemoView::OnDraw(CDC* pDC)
{
	CMFC_DemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CClientDC hdc(this);
	SetMapMode(hdc, MM_ANISOTROPIC);       //设置映像模式
	HPEN hP = (HPEN)GetStockObject(BLACK_PEN);	//黑色画笔
	HBRUSH hB = (HBRUSH)GetStockObject(DKGRAY_BRUSH); //画刷
	SelectObject(hdc, hB);   //选择画刷
	SelectObject(hdc, hP);       //选择画笔
	RoundRect(hdc, 50, 120, 100, 200, 15, 15); //绘制圆角矩形
	hB = (HBRUSH)GetStockObject(LTGRAY_BRUSH);  //采用亮灰色画刷
	SelectObject(hdc, hB);  	   //选择画刷
	Ellipse(hdc, 150, 50, 200, 150); 	   //绘制椭圆
	hB = (HBRUSH)GetStockObject(HOLLOW_BRUSH); //虚画刷
	SelectObject(hdc, hB);  	  //选择画刷
	Pie(hdc, 250, 50, 300, 100, 250, 50, 300, 50);  	//绘制饼形

	hP = CreatePen(PS_DASHDOT, 1, RGB(0, 0, 255));
	hB = CreateHatchBrush(HS_HORIZONTAL, RGB(0, 255, 0));
	SelectObject(hdc, hP);
	SelectObject(hdc, hB);
	RoundRect(hdc, 35, 220, 115, 270, 15, 15);
	Ellipse(hdc, 125, 170, 225, 220);
	Pie(hdc, 250, 120, 300, 170, 300, 120, 300, 170);

}