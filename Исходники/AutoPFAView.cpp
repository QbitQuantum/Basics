BOOL CAutoPFAView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	//CScrollView::OnEraseBkgnd(pDC);
	CAutoPFADoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	/*
    wndbkBrush.CreateSolidBrush(RGB(128,128,128));
    wndbkBrush.DeleteObject();
    */

	CBrush wndbkBrush;
    wndbkBrush.CreateSolidBrush(pDoc->m_workSpaceRef.GetbkColor());
	FillOutsideRect(pDC,&wndbkBrush);//把组件范围外的区域也刷成客户区域背景颜色，这样看起来不会闪屏
	CRect rc(CPoint(0,0),GetTotalSize());
    pDC->FillRect(rc, &wndbkBrush);
	wndbkBrush.DeleteObject();
    return TRUE;
}