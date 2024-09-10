// Create a bitmap for off-screen drawing...
bool CTinyCadView::CreateBitmap(CDC &dc, int width, int height)
{
	// Is there already a suitable bitmap?
	if (m_bitmap_width >= width && m_bitmap_height >= height)
	{
		return true;
	}

	// Is this beyond the maximum size we are willing to allocate?
	if (width * height > m_max_bitmap_size)
	{
		return false;
	}

	int bpp = dc.GetDeviceCaps(BITSPIXEL);
	if (bpp <= 16)
	{
		bpp = 16;
	}
	else
	{
		bpp = 24;
	}

	// Now try and create the bitmap...
	struct
	{
		BITMAPINFO bi;
		RGBQUAD bipal[3];
	} q;
	q.bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	q.bi.bmiHeader.biWidth = width;
	q.bi.bmiHeader.biHeight = height;
	q.bi.bmiHeader.biPlanes = 1;
	q.bi.bmiHeader.biBitCount = (WORD) bpp;
	q.bi.bmiHeader.biCompression = bpp == 16 ? BI_BITFIELDS : BI_RGB;
	q.bi.bmiHeader.biSizeImage = 0;
	q.bi.bmiHeader.biXPelsPerMeter = 0;
	q.bi.bmiHeader.biYPelsPerMeter = 0;
	q.bi.bmiHeader.biClrUsed = bpp == 16 ? 3 : 0;
	q.bi.bmiHeader.biClrImportant = 0;
	q.bi.bmiColors[0].rgbRed = 0;
	q.bi.bmiColors[0].rgbGreen = 0;
	q.bi.bmiColors[0].rgbBlue = 0;
	q.bi.bmiColors[0].rgbReserved = 0;

	// Set up the 5-6-5 bit masks
	if (bpp == 16)
	{
		((DWORD*) (q.bi.bmiColors))[0] = (WORD) (0x1F << 11); //make sure that RGQQUAD array is after the q.bi struct
		((DWORD*) (q.bi.bmiColors))[1] = (WORD) (0x3F << 5); //otherwise you will get an access violation
		((DWORD*) (q.bi.bmiColors))[2] = (WORD) (0x1F << 0);
	}

	void *bits;
	HBITMAP hb = CreateDIBSection(dc.m_hDC, &q.bi, DIB_RGB_COLORS, &bits, NULL, 0);

	if (!hb)
	{
		// Probably not enough memory...
		return false;
	}

	// Do we need to destroy the old bitmap?
	if (m_bitmap.m_hObject)
	{
		m_bitmap.DeleteObject();
	}

	m_bitmap.Attach(hb);
	m_bitmap_width = width;
	m_bitmap_height = height;

	return true;
}