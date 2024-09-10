 void CVisualSynanView::Recalculate(CDC& clDC, CPrintInfo* pInfo)
{
	if( GetDocument()->NoSentences() )
		return;

	//selecting choosen font
	CFont* pOldFont = NULL;
	
	//creating memory DC
	CRect clientRect;
	GetClientRect(&clientRect);
	OnPrepareDC(&clDC,pInfo);
	clDC.DPtoLP(&clientRect);

	if( m_bExistUsefulFont)
	{
		pOldFont = clDC.SelectObject(&m_FontForWords);
	}

	//calculating sentences coordinates 
	GetDocument()->CalculateCoordinates(&clDC,clientRect.right, m_bShowGroups);

	if( pOldFont )
		clDC.SelectObject(pOldFont);

}