bool CDrawableWidget::GrabScreen(CImage & imgGrabTo)
{
	
	GetClientRect(&m_rect); 
	
	StretchBlt(imgGrabTo.GetDC(), 0, 0, imgGrabTo.GetWidth(), imgGrabTo.GetHeight(), 
		SafeGrabDC()->GetSafeHdc(), 0, 0, m_rect.right, m_rect.bottom, SRCCOPY);

	imgGrabTo.ReleaseDC();
	SafeReleaseDC();
	return true;

	//GetClientRect(&m_rect); 
	//HBITMAP hBmpResult = CreateCompatibleBitmap(GetDC()->GetSafeHdc(),
	//	m_rect.right,m_rect.bottom);


	//return hBmpResult;
}