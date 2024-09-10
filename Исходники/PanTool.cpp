void CPanTool::OnMouseMove(_CVIEW* pView, UINT nFlags, CPoint& point)
{
	::SetCursor(AfxGetApp()->LoadCursor(IDC_PAN));
	CDC* pDC = NULL;
	pDC = pView->GetDC();
	if (pDC == NULL) return;
	CMiniCADDoc* pDoc = pView->GetDocument();
	if (pDoc==NULL)return;
	CADGraphics	*pGraphics = &pDoc->m_Graphics;
	CDisplay *pDisplay = pGraphics->m_pDisplay;
	if (pDisplay == NULL) return;
	if (!c_bDown)
	{
		DeleteDC(pDC->m_hDC);
		return;
	}
	::SetCursor(AfxGetApp()->LoadCursor(IDC_PANDOWN));

	double ddx,ddy;
	int dx,dy;
	dx=point.x-c_PtOld.x;
	dy=point.y-c_PtOld.y;
	ddx=dx/pDoc->m_Graphics.m_ZoomRate;
	ddy=dy/pDoc->m_Graphics.m_ZoomRate;

	int cx = point.x - c_PtDown.x;
	int cy = point.y - c_PtDown.y;

	CBrush brush;
	brush.CreateSolidBrush(pDoc->m_Graphics.m_BKColor);
	CRect rect;
	CRect rect2;
	pView->GetClientRect(rect);
	if(pView->m_curWorkSpace==MODELSPACE)
	{
		if (cx>0)
			rect2.SetRect(0,0,cx,rect.Height());
		else
			rect2.SetRect(rect.Width()+cx,0,rect.Width(),rect.Height());
		pDC->FillRect(&rect2, &brush);
		if (cy>0)
			rect2.SetRect(0,0,rect.Width(),cy-1);
		else
			rect2.SetRect(0,rect.Height()+cy,rect.Width(),rect.Height());
		pDC->FillRect(&rect2, &brush);
		pDC->BitBlt(cx,cy,rect.Width(),rect.Height(),pDisplay->GetDC(),0,0,SRCCOPY);
	}
	else
	{
		CRect moveRect=pView->m_ModelRect;
		CDC* pPaperDC=pDisplay->GetPaperDC();
		int xOffset=0;
		int yOffset=0;
		if (cx>0)
		{
			if(cx>pView->m_ModelRect.Width())cx=pView->m_ModelRect.Width();
			rect2.SetRect(pView->m_ModelRect.left,pView->m_ModelRect.top,pView->m_ModelRect.left+cx,pView->m_ModelRect.top+pView->m_ModelRect.Height());
			moveRect.left+=cx;
		}
		else
		{
			if(cx<-pView->m_ModelRect.Width())cx=-pView->m_ModelRect.Width();
			rect2.SetRect(pView->m_ModelRect.left+pView->m_ModelRect.Width()+cx,pView->m_ModelRect.top,pView->m_ModelRect.left+pView->m_ModelRect.Width(),pView->m_ModelRect.top+pView->m_ModelRect.Height());
			moveRect.right+=cx;
			xOffset-=cx;
			
		}
		pPaperDC->FillRect(&rect2, &brush);
		if (cy>0)
		{
			if(cy>pView->m_ModelRect.Height())cy=pView->m_ModelRect.Height();
			rect2.SetRect(pView->m_ModelRect.left,pView->m_ModelRect.top,pView->m_ModelRect.left+pView->m_ModelRect.Width(),pView->m_ModelRect.top+cy);
			moveRect.top+=cy;
		}
		else
		{
			if(cy<-pView->m_ModelRect.Height())cy=-pView->m_ModelRect.Height();
			rect2.SetRect(pView->m_ModelRect.left,pView->m_ModelRect.top+pView->m_ModelRect.Height()+cy,pView->m_ModelRect.left+pView->m_ModelRect.Width(),pView->m_ModelRect.top+pView->m_ModelRect.Height());
			moveRect.bottom+=cy;
			yOffset-=cy;						
		}
		pPaperDC->FillRect(&rect2, &brush);

		pPaperDC->BitBlt(moveRect.left,moveRect.top,moveRect.Width(),moveRect.Height(),pDisplay->GetDC(),xOffset,yOffset,SRCCOPY);
		pView->Invalidate(false);
	}
	brush.DeleteObject();
	DeleteDC(pDC->m_hDC);
	CDrawTool::OnMouseMove(pView, nFlags, point);
}