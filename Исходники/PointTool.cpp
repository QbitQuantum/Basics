void CPointTool::OnLButtonDown(_CVIEW * pView, UINT nFlags, CPoint& point)
{
	CMiniCADDoc* pDoc = pView->GetDocument();
	if (pDoc==NULL)return;
	CADGraphics	*pGraphics = &pDoc->m_Graphics;
	CDisplay *pDisplay = pGraphics->m_pDisplay;
	if (pDisplay == NULL) return;
	CADPoint* pPoint;
	pPoint=new CADPoint();
	ADPOINT adPoint=pDoc->m_Graphics.ClientToDoc(point);
	pPoint->pt=adPoint;
	pPoint->m_nLayer=pDoc->m_LayerGroup.indexOf(pDoc->m_curLayer);
	pDoc->m_Graphics.m_Entities.Add((CObject*)pPoint);
	pDoc->m_Graphics.DrawGraphics(pDisplay->GetDC(),pPoint);
	pView->ReBitBlt();
	CDrawTool::OnLButtonDown(pView, nFlags, point);
}