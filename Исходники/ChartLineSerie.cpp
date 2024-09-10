void CChartLineSerie::Draw(CDC* pDC)
{
	if (!m_bIsVisible)
		return;

	// If shadow or smooth is enabled, then the complete series
	// must be redrawn.
	if (m_bShadow || m_bSmooth)
	{
		DrawAll(pDC);
		return;
	}

	if (pDC->GetSafeHdc())
	{
		CPen NewPen;
		if (m_iPenStyle != PS_SOLID)
		{
			LOGBRUSH lb;
			lb.lbStyle = BS_SOLID;
			lb.lbColor = m_SerieColor;
			NewPen.CreatePen(PS_GEOMETRIC | m_iPenStyle, m_iLineWidth, &lb);
		}
		else
		{
			NewPen.CreatePen(m_iPenStyle, m_iLineWidth, m_SerieColor);
		}
		CPen* pOldPen;

		pDC->SetBkMode(TRANSPARENT);
		//To have lines limited in the drawing rectangle :
		pDC->IntersectClipRect(m_pParentCtrl->GetPlottingRect());
		pOldPen = pDC->SelectObject(&NewPen);

		//Draw all points that haven't been drawn yet
		for (m_uLastDrawnPoint;m_uLastDrawnPoint<GetPointsCount()-1;m_uLastDrawnPoint++)
		{
			SChartXYPoint Point = GetPoint(m_uLastDrawnPoint);
			CPoint ScreenPoint;
			ValueToScreen(Point.X, Point.Y, ScreenPoint);
			pDC->MoveTo(ScreenPoint.x,ScreenPoint.y);

			Point = GetPoint(m_uLastDrawnPoint+1);
			ValueToScreen(Point.X, Point.Y, ScreenPoint);
			pDC->LineTo(ScreenPoint.x,ScreenPoint.y);
		}

		pDC->SelectClipRgn(NULL);
		pDC->SelectObject(pOldPen);
		DeleteObject(NewPen);
	}
}