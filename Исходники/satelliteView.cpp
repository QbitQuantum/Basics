void CSatelliteView::OnDraw(CDC* pDC)
{
	CSatelliteDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CRect rectClient;
	GetClientRect(&rectClient);
	double x,y;
	x=(rectClient.right-rectClient.left)/2;
	y=(rectClient.bottom-rectClient.top)/2;
    pDC->SelectStockObject(NULL_BRUSH);
	CPen newPen;
	CPen newPenx;
	CPen newPen_satellite;
	newPen.CreatePen(PS_SOLID,pDoc->m_widthDoc,pDoc->m_orbitColor);
	newPen_satellite.CreatePen(PS_SOLID,2,pDoc->m_satelliteColor);
	newPenx.CreatePen(PS_SOLID,pDoc->m_widthDocx,pDoc->m_orbitColor);
    CPen *poldPen;
	poldPen=pDC->SelectObject(&newPen);
	pDC->Ellipse(x-pDoc->m_radiiDoc,y-pDoc->m_radiiDoc,x+pDoc->m_radiiDoc,y+pDoc->m_radiiDoc);
	poldPen=pDC->SelectObject(&newPenx);
	pDC->Ellipse(x-pDoc->m_radiiDocx,y-pDoc->m_radiiDocx,x+pDoc->m_radiiDocx,y+pDoc->m_radiiDocx);
	poldPen=pDC->SelectObject(&newPen_satellite);
	pDC->Ellipse(x+pDoc->m_radiiDoc*cos(pDoc->m_angle)-15,y+pDoc->m_radiiDoc*sin(pDoc->m_angle)-15,x+pDoc->m_radiiDoc*cos(pDoc->m_angle)+15,y+pDoc->m_radiiDoc*sin(pDoc->m_angle)+15);
	pDC->Ellipse(x+pDoc->m_radiiDocx*cos(pDoc->m_angle)-15,y+pDoc->m_radiiDocx*sin(pDoc->m_angle)-15,x+pDoc->m_radiiDocx*cos(pDoc->m_angle)+15,y+pDoc->m_radiiDocx*sin(pDoc->m_angle)+15);
	// TODO: add draw code for native data here
}