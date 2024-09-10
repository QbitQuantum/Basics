void ImgMaskCreator::ScanFill(const TRect2D<int>& range, PelGray8 fillVal)
{
	TRect2D<int> window = TRect2D<int>(	range.Center().x(), 
										range.y0(),
										range.x1(),
										range.y1());
	window = m_img.Window(window);
	TImage<PelGray8>::RowIter iterBegin = m_img.RowBegin();
	TImage<PelGray8>::RowIter iterEnd	= m_img.RowEnd();
	size_t w = window.Width();
	size_t x = 0;
	for(; iterBegin != iterEnd; ++iterBegin)
	{
		PelGray8 *pDataM = iterBegin.Base();
		PelGray8 *pDataL = pDataM-1;
		PelGray8 *pDataR = pDataM+1;
		*pDataM = fillVal;
		x = 0;
		while(*pDataL != m_boundLineVal && x<w)	{ *pDataL-- = fillVal; ++x; }
		x = 0;
		while(*pDataR != m_boundLineVal && x<w)	{ *pDataR++ = fillVal; ++x; }
	}
}