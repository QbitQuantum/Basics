// return rectange of handle in device coords
CRect CDrawObject::GetHandleRect(int nHandleID)
{
  //  FTLTRACE(TEXT("CDrawObject(0x%p)::GetHandleRect,m_position=[%d,%d]x[%d,%d], nHandle=%d\n"), this,
		//m_position.left, m_position.top, m_position.right, m_position.bottom,
		//nHandleID);

	CRect rect;
	// get the center of the handle in device coords
	CPoint point = GetHandle(nHandleID);
	// convert to client/device coords
	//m_pDrawCanvas->DocToClient(&point);
	// return CRect of handle in device coords
	rect.SetRect(point.x - TRACK_MARGIN, point.y - TRACK_MARGIN, point.x + TRACK_MARGIN, point.y + TRACK_MARGIN);
	//m_pDrawCanvas->ClientToDoc(&rect);
	return rect;
}