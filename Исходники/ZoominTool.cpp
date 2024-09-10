void CZoominTool::OnMouseMove(_CVIEW* pView, UINT nFlags, CPoint& point)
{
	::SetCursor(AfxGetApp()->LoadCursor(IDC_ZOOMIN));
	CDC* pDC = NULL;
	pDC = pView->GetDC();
	if (pDC == NULL) return;
	if (!c_bDown)
	{
		DeleteDC(pDC->m_hDC);
		return;
	}

	CRect oldRect(c_PtDown,c_PtOld);
	CRect newRect(c_PtDown,point);
	//CRect TrackRect;
	//	TrackRect.SetRect(m_StartPoint,point);
	CPen Pen;
	if (!Pen.CreatePen(PS_SOLID, 1, RGB(0,0,0)))
	return;
	CPen *pOldPen = pDC->SelectObject(&Pen);
	//int oldDrawMode = m_pDC->SetROP2(R2_XORPEN);
	int oldDrawMode = pDC->SetROP2(R2_NOT);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->Rectangle(oldRect);
	pDC->Rectangle(newRect);
	pDC->SetROP2(oldDrawMode);
	pDC->SelectObject(pOldPen);
	Pen.DeleteObject();
	DeleteDC(pDC->m_hDC);
	CDrawTool::OnMouseMove(pView, nFlags, point);
}