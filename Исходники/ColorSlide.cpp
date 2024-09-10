void CColorSlide::DynamicStat(ENUM_SLIDERSTATE aState)
{
	if (m_nWidth <= 0)
	{
		return;
	}
	CDC* pDC =GetWindowDC();	
	if (pDC == NULL)
	{
		return;
	}
	pDC->SetBkColor(TRANSPARENT);
	CRect lrcClientRect;
	GetClientRect(lrcClientRect);
	m_nWidth = lrcClientRect.Width();
	lrcClientRect.bottom;
	m_nHeight = lrcClientRect.Height();

	CMemDC TempDC(pDC, CRect(lrcClientRect.left, lrcClientRect.top,lrcClientRect.right, lrcClientRect.bottom));
	PaintBK(lrcClientRect,TempDC.GetSafeHdc());
	if( m_SlideType != PERCENT_SLIDE ) 
	DrawSlider(aState,lrcClientRect,TempDC.GetSafeHdc());
	BitBlt(pDC->GetSafeHdc(),0,0,m_nWidth,m_nHeight,TempDC.GetSafeHdc(),0,0,SRCCOPY);
	ReleaseDC(pDC);
}