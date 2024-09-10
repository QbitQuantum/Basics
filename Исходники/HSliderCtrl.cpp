void HSliderCtrl::OnPaint()
{
	CPaintDC dc(this);
	//获取位置
	CRect rect;
	GetClientRect(&rect);
	//建双缓冲
	CImage		imgBuffer;
	CDC			dcBuffer;
	imgBuffer.Create(rect.Width(), rect.Height(), 24);
	dcBuffer.Attach(imgBuffer.GetDC());

	if (!m_imgBk.IsNull())
	{
		m_imgBk.TransparentBlt(dcBuffer.GetSafeHdc(),0,0,rect.Width(),rect.Height(),
			0,0,m_imgBk.GetWidth(),m_imgBk.GetHeight()/5,RGB(255,0,255));
		CRect thuRect;
		GetThumbRect(&thuRect);
		m_imgBk.TransparentBlt(dcBuffer.GetSafeHdc(),thuRect.left,thuRect.top,thuRect.Width(),thuRect.Height(),
			0,0+m_imgBk.GetHeight()/5*(m_byThuState+2),11,m_imgBk.GetHeight()/5,RGB(255,0,255));
		m_imgBk.TransparentBlt(dcBuffer.GetSafeHdc(),0,0,thuRect.left,rect.Height(),
			0,0+m_imgBk.GetHeight()/5,thuRect.left,m_imgBk.GetHeight()/5,RGB(255,0,255));
	}

	//清除缓冲
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &dcBuffer, 0, 0, SRCCOPY);
	dcBuffer.Detach();
	imgBuffer.ReleaseDC();
}