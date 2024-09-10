void CGOView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	pointList.Add(point);
	//CGODoc * pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	CDC *cdc = GetDC();

	POINT p[20];
	for(int i=0;i<pointList.GetSize();i++)
	{
		p[i] = pointList.GetAt(i);
	}
	//CBrush brush1(RGB(255,0,0));
	//cdc->SelectObject(&brush1);
	cdc->Polygon(p,pointList.GetSize());
	EdgeMarkFill();
	pointList.RemoveAll();
	CView::OnLButtonDblClk(nFlags, point);
}