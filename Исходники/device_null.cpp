bool DeviceNull::init_color_frame()
{
	BITMAPINFO	f_bmi		= {0};
	void *		f_buffer	= nullptr;

	// create a device independent bitmap of the correct format
	f_bmi.bmiHeader.biCompression    = BI_RGB;
	f_bmi.bmiHeader.biBitCount       = m_private->m_resolution.m_bits_per_pixel;
    f_bmi.bmiHeader.biSize           = sizeof(BITMAPINFOHEADER);
    f_bmi.bmiHeader.biWidth          = m_private->m_resolution.m_width;
    f_bmi.bmiHeader.biHeight         = m_private->m_resolution.m_height;
    f_bmi.bmiHeader.biPlanes         = 1;
    f_bmi.bmiHeader.biSizeImage      = GetBitmapSize(&f_bmi.bmiHeader);
    f_bmi.bmiHeader.biClrImportant   = 0;

	auto f_dib = CreateDIBSection(nullptr, &f_bmi, DIB_RGB_COLORS, &f_buffer, nullptr, 0);

	if (!f_dib)
		return false;
	
	// attach the DIB to a device context
	auto f_hdc = GetDC(nullptr);
	auto f_paintdc = CreateCompatibleDC(f_hdc);
	SetMapMode(f_paintdc, GetMapMode(f_hdc));
	SelectObject(f_paintdc, f_dib);

	// text properties
	SetBkColor  (f_paintdc, RGB (0,0,0));
	SetTextColor(f_paintdc, RGB(255,255,255));
	SetTextAlign(f_paintdc, TA_CENTER);

	// write the text to the DIB
	const wchar_t *f_msg = L"No Kinect available.";
	TextOut(f_paintdc, 160, 110, f_msg, wcslen(f_msg));

	// save the buffer
	memcpy(m_private->m_color_data.data(), f_buffer, m_private->m_color_data.size());

	// cleanup
	DeleteDC(f_paintdc);

	return true;
}