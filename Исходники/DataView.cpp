void CDataView::setZoomWindow(double newScale, int hPos, int vPos)
{
	m_scale = fixZoomScale(newScale);
	setScrollInfo(hPos*m_scale, vPos*m_scale);
}