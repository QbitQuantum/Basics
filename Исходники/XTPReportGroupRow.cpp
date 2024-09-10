void CXTPReportGroupRow::Draw(CDC* pDC, CRect rcRow, CRect rcClip, int nLeftOffset,
	CXTPReportRecordMergeItems& /*mergeItems*/, int nColumnFrom, int nColumnTo)
{
	UNREFERENCED_PARAMETER(rcClip);
	UNREFERENCED_PARAMETER(nColumnFrom);
	UNREFERENCED_PARAMETER(nColumnTo);

	CRgn rgnClip;
	if (!pDC->IsPrinting())
	{
		rgnClip.CreateRectRgnIndirect(&rcClip);
		pDC->SelectClipRgn(&rgnClip, RGN_COPY);
	}

	CXTPReportPaintManager *pPaintManager = m_pControl->GetPaintManager();

	pDC->SetBkMode(TRANSPARENT);

	m_rcRow = rcRow;
	if (0 == GetControl()->GetFreezeColumnsCount())
	{
		m_rcRow.left  -= nLeftOffset;
		m_rcRow.right -= nLeftOffset;
	}

	XTP_REPORTRECORDITEM_DRAWARGS drawArgs;
	drawArgs.pDC        = pDC;
	drawArgs.nTextAlign = DT_LEFT;
	drawArgs.pControl   = m_pControl;
	drawArgs.pColumn    = NULL;
	drawArgs.pRow       = this;
	drawArgs.pItem      = NULL;
	drawArgs.rcItem     = m_rcRow;

	XTP_REPORTRECORDITEM_METRICS* pDrawMetrics = new XTP_REPORTRECORDITEM_METRICS;
	pDrawMetrics->strText = GetCaption();

	pPaintManager->FillGroupRowMetrics(this, pDrawMetrics, pDC->IsPrinting());

	ASSERT(m_pControl);
	if (m_pControl)
		m_pControl->GetItemMetrics(&drawArgs, pDrawMetrics);

	pPaintManager->DrawGroupRow(pDC, this, m_rcRow, pDrawMetrics);

	pDrawMetrics->InternalRelease();

	if (!pDC->IsPrinting())
	{
		pDC->SelectClipRgn(NULL, RGN_COPY);
		rgnClip.DeleteObject();
	}
}