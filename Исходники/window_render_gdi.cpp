void window_render_gdi::render_end()
{
	BITMAPINFO bmi;
	ZeroMemory(&bmi,sizeof(bmi));
	BITMAPINFOHEADER& h = bmi.bmiHeader;
	h.biSize = sizeof(BITMAPINFOHEADER);
	h.biWidth = m_image->m_width;
	h.biHeight = -m_image->m_height;
	h.biPlanes = 1;
	h.biBitCount = 24;
	h.biCompression = BI_RGB;
	h.biSizeImage = m_image->m_width * m_image->m_height;

	//flip();
	HDC dc = GetDC((HWND)m_window->m_hWnd);
	m_image->rgb2bgr();
	int err = SetDIBitsToDevice(dc,0,0,m_image->m_width,m_image->m_height,
		0,0,0,m_image->m_height,
		m_image->get_buffer() ,
		&bmi,
		DIB_RGB_COLORS);
	if (err <= 0)
	{
		//GDI_ERROR
		printf("error! SetDIBitsToDevice %d %d\n",err,GetLastError());
	}
	ReleaseDC((HWND)m_window->m_hWnd,dc);
	window_render::render_end();
}