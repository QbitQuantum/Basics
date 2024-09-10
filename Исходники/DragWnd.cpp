void CDragWnd::OnPaint( CDCHandle dc )
{
	CRect rc;
	GetClientRect(rc);
	dc.BitBlt(0,0,rc.Width(),rc.Height(),m_memdc,0,0,SRCCOPY);
}