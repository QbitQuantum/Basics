//绘画函数
void CShortMessage::OnPaint()
{
	CPaintDC dc(this); 

	//绘画标题
	DrawCaption(&dc);

	CRect ClientRect;
	GetClientRect(&ClientRect);
	int nXExcursion=GetXExcursionPos();
	int nYExcursion=GetYExcursionPos();

	/////////////////////////////////////////////////////////////////////////////
	CRect rcClient1;
	GetWindowRect(&rcClient1);
	int nWidth1=rcClient1.Width();
	int nHeight1=rcClient1.Height();
	//调整判断
	if ((nWidth1!=0)&&(nHeight1!=0))
	{
		//框架位置
		CRect rcFrame;
		rcFrame.SetRect(0,0,nWidth1,nHeight1);

		//窗口区域
		CRgn RegionWindow;
		RegionWindow.CreateRoundRectRgn(rcFrame.left,rcFrame.top,rcFrame.right+1,rcFrame.bottom+1,5,5);

		//设置区域
		SetWindowRgn(RegionWindow,TRUE);
	}
	///////////////////////////////////////////////////////////////////////////

	//绘画背景
	COLORREF Color = RGB(170,213,244);
	dc.FillSolidRect(nXExcursion,nYExcursion,ClientRect.Width()-2*nXExcursion,4,Color);
	dc.FillSolidRect(nXExcursion,ClientRect.Height()-8,ClientRect.Width()-2*nXExcursion,7,Color);
	dc.FillSolidRect(nXExcursion,nYExcursion+4,12,ClientRect.Height()-nYExcursion-9,Color);
	dc.FillSolidRect(ClientRect.Width()-nXExcursion-12,nYExcursion+4,12,ClientRect.Height()-nYExcursion-9,Color);
	CRect mRect(nXExcursion,190,ClientRect.Width()-2*nXExcursion,ClientRect.Height());
	CBrush Brush(Color); 
	dc.FillRect(mRect,&Brush);

	//创建笔画
	CPen BorderPen(PS_SOLID,1,RGB(20,20,20));
	CPen * pOldPen=dc.SelectObject(&BorderPen);
	dc.SelectObject(m_SkinAttribute.m_brBackGround);

	//绘画内框
	CRect rcDrawRect(nXExcursion,nYExcursion,ClientRect.Width()-2*nXExcursion,200);
	rcDrawRect.DeflateRect(6,4,6,4);
	dc.RoundRect(&rcDrawRect,CPoint(8,8));

	//清理资源
	dc.SelectObject(pOldPen);
	BorderPen.DeleteObject();

	//创建笔画
	CPen BorderPen1(PS_SOLID,1,m_SkinAttribute.m_crInsideBorder);
	pOldPen=dc.SelectObject(&BorderPen1);

	//绘画内框
	rcDrawRect.DeflateRect(1,1,1,1);
	dc.RoundRect(&rcDrawRect,CPoint(8,8));
	CRect rcDrawRect1(nXExcursion+9,203,ClientRect.Width()-2*nXExcursion-8,ClientRect.Height()-37);
	dc.RoundRect(&rcDrawRect1,CPoint(4,4));

	//清理资源
	dc.SelectObject(pOldPen);
	BorderPen1.DeleteObject();

	return;
}