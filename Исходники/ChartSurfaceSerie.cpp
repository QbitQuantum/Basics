void CChartSurfaceSerie::DrawAll(CDC* pDC)
{
	int iFirst=0, iLast=0;
	GetVisiblePoints(iFirst,iLast);

	if (iFirst>0)
		iFirst--;
	if (iLast<(int)GetPointsCount())
		iLast++;
	int iCount = iLast - iFirst;
	CPoint* pPoints = new CPoint[iCount+2];

	CBrush NewBrush;
	if (m_FillStyle == fsSolid)
		NewBrush.CreateSolidBrush(m_ObjectColor);
	else
	{
		int nIndex = 0;
		switch (m_FillStyle)
		{
		case fsHatchDownDiag:
			nIndex = HS_FDIAGONAL;
			break;
		case fsHatchUpDiag:
			nIndex = HS_BDIAGONAL;
			break;
		case fsHatchCross:
			nIndex = HS_CROSS;
			break;
		case fsHatchDiagCross:
			nIndex = HS_DIAGCROSS;
			break;
		case fsHatchHorizontal:
			nIndex = HS_HORIZONTAL;
			break;
		case fsHatchVertical:
			nIndex = HS_VERTICAL;
			break;
		}
		NewBrush.CreateHatchBrush(nIndex,m_ObjectColor);
	}

	CBrush* pOldBrush = pDC->SelectObject(&NewBrush);

	for (int i=iFirst; i<iLast; i++)
	{
		ValueToScreen(m_vPoints[i].X,m_vPoints[i].Y,pPoints[i-iFirst+1]);
	}

	if (m_bHorizontal)
	{
		pPoints[0].x = pPoints[1].x;
		pPoints[iCount+1].x = pPoints[iCount].x;

		double Position = m_pHorizontalAxis->GetPosition()/100.00;
		int AxisPos = m_ObjectRect.top + (int)(Position * (m_ObjectRect.bottom-m_ObjectRect.top));

		pPoints[0].y = AxisPos;
		pPoints[iCount+1].y = AxisPos;
	}
	else
	{
		pPoints[0].y = pPoints[1].y;
		pPoints[iCount+1].y = pPoints[iCount].y;

		double Position = m_pVerticalAxis->GetPosition()/100.00;
		int AxisPos = m_ObjectRect.left + (int)(Position * (m_ObjectRect.right-m_ObjectRect.left));

		pPoints[0].x = AxisPos;
		pPoints[iCount+1].x = AxisPos;
	}

	pDC->SetBkMode(TRANSPARENT);
	//To have lines limited in the drawing rectangle :
	CRect TempClipRect(m_ObjectRect);
	TempClipRect.DeflateRect(1,1);
	pDC->SetBkMode(TRANSPARENT);
	pDC->IntersectClipRect(TempClipRect);

	pDC->Polygon(pPoints,iCount+2);
	pDC->SelectClipRgn(NULL);
	pDC->SelectObject(pOldBrush);
	DeleteObject(NewBrush);

	delete[] pPoints;
}