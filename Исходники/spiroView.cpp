void CSpiroView::OnRemovePiece(CBasePiece** ppPiece) 
{
	ENSURE(ppPiece != NULL && *ppPiece != NULL);
	CRgn	rgnPiece;

	CDC*	pDC = GetDC();
	ENSURE(pDC != NULL);
	OnPrepareDC(pDC);

	(*ppPiece)->GetDevPieceRgn(pDC, &rgnPiece, m_nZoomNumer, m_nZoomDenom, true);

	InvalidateRgn(&rgnPiece);
	delete *ppPiece;
	*ppPiece = NULL;
	ReleaseDC(pDC);
	GetDocument()->TransferCurrentFigure();  // make the current figure permanent
	m_bDrawingDone = false;
}