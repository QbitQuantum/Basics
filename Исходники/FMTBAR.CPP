int CFormatBar::GetDefaultHeight(void)
{
	CRect rectSize;
	rectSize.SetRectEmpty();
#ifdef WIN32
	CalcInsideRect(rectSize, TRUE);       // will be negative size
#else
	CalcInsideRect(rectSize);       // will be negative size
#endif
	return m_sizeButton.cy - rectSize.Height();
}