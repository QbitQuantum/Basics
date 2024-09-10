void MyGraph::DrawSeriesLineStacked(CDC& dc) const
{
	VALIDATE;
	ASSERT_VALID(&dc);
	_ASSERTE(m_bStackedGraph);

	int nSeriesCount = (int)m_olMyGraphSeries.GetCount();

	CArray<int> stackAccumulator;
	stackAccumulator.SetSize(nSeriesCount);

	CArray<CPoint> polygon;
	// Special case: if we only have single series, make polygon
	// a bar instead of one pixel line.
	polygon.SetSize(nSeriesCount==1 ? 4 : nSeriesCount * 2);

	// How much space does each series get?
	int nSeriesSpace(0);
	if (m_saLegendLabels.GetSize()) {
		nSeriesSpace = (m_nXAxisWidth - m_rcLegend.Width() - (GAP_PIXELS * 2)) /
			nSeriesCount;
	}
	else {
		nSeriesSpace = m_nXAxisWidth / nSeriesCount;
	}

	int nMaxDataValue(GetMaxDataValue());
	nMaxDataValue = max(nMaxDataValue, 1);
	double dYScaling = double(m_nYAxisHeight) / nMaxDataValue;

	// Iterate the groups.
	for (int nGroup = 0; nGroup < GetMaxSeriesSize(); nGroup++) {

		// Build objects.
		COLORREF crGroup(m_dwaColors.GetAt(nGroup));
		CBrush br(crGroup);
		CBrush* pBrushOld = dc.SelectObject(&br);
		ASSERT_VALID(pBrushOld);
		// For polygon outline, use average of this and previous color, and darken it.
		COLORREF crPrevGroup(nGroup > 0 ? m_dwaColors.GetAt(nGroup-1) : crGroup);
		COLORREF crOutline = RGB(
			(GetRValue(crGroup)+GetRValue(crPrevGroup))/3,
			(GetGValue(crGroup)+GetGValue(crPrevGroup))/3,
			(GetBValue(crGroup)+GetBValue(crPrevGroup))/3);
		CPen penLine(PS_SOLID, 1, crOutline);
		CPen* pPenOld = dc.SelectObject(&penLine);
		ASSERT_VALID(pPenOld);

		// Construct bottom part of polygon from current stack accumulator
		for (int nPolyBottom = 0; nPolyBottom < nSeriesCount; ++nPolyBottom) {
			CPoint ptLoc;
			ptLoc.x = m_ptOrigin.x + (((nPolyBottom + 1) * nSeriesSpace) - (nSeriesSpace / 2));
			double dLineHeight((stackAccumulator[nPolyBottom]) * dYScaling);
			ptLoc.y = (int) ((double) m_ptOrigin.y - dLineHeight);

			if (nSeriesCount > 1) {
				polygon[nSeriesCount-nPolyBottom-1] = ptLoc;
			} else {
				// special case: when there's one series, make polygon a bar
				polygon[0] = CPoint(ptLoc.x-GAP_PIXELS/2, ptLoc.y);
				polygon[1] = CPoint(ptLoc.x+GAP_PIXELS/2, ptLoc.y);
			}
		}

		// Iterate the series, construct upper part of polygon and upadte stack accumulator
		POSITION pos(m_olMyGraphSeries.GetHeadPosition());
		for (int nSeries = 0; nSeries < nSeriesCount; ++nSeries) {

			MyGraphSeries* pSeries = m_olMyGraphSeries.GetNext(pos);
			ASSERT_VALID(pSeries);

			CPoint ptLoc;
			ptLoc.x = m_ptOrigin.x + (((nSeries + 1) * nSeriesSpace) -
				(nSeriesSpace / 2));
			double dLineHeight((pSeries->GetData(nGroup) + stackAccumulator[nSeries]) * dYScaling);
			ptLoc.y = (int) ((double) m_ptOrigin.y - dLineHeight);
			if (nSeriesCount > 1) {
				polygon[nSeriesCount+nSeries] = ptLoc;
			} else {
				// special case: when there's one series, make polygon a bar
				polygon[2] = CPoint(ptLoc.x+GAP_PIXELS/2, ptLoc.y);
				polygon[3] = CPoint(ptLoc.x-GAP_PIXELS/2, ptLoc.y);
			}

			stackAccumulator[nSeries] += pSeries->GetData(nGroup);
		}

		// Draw polygon
		VERIFY(dc.Polygon(polygon.GetData(), (int)polygon.GetSize()));

		VERIFY(dc.SelectObject(pPenOld));
		penLine.DeleteObject();
		VERIFY(dc.SelectObject(pBrushOld));
		br.DeleteObject();
	}
}