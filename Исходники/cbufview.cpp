VOID CBufView::RenderOnDevice(HDC hDC)
{
	RECT rc = { 0 };
	if ( OnMessage(BVM_GETUPDATEAREA, 0, (LPARAM) &rc) )
		BitBlt(hDC, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, m_buffer.hDC, rc.left, rc.top, SRCCOPY);
	else
		SetDIBitsToDevice(hDC, 0, 0, m_cs.cx, m_cs.cy, 0, 0, 0, m_cs.cy, m_buffer.pvBits, &m_buffer.bmi, DIB_RGB_COLORS);
}