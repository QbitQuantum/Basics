BOOL CDrawMandelbrotDlg::Draw()
{
	CRect rect;
	GetWindowRect(&rect);
	int width = rect.Width();
	int height = rect.Height();

	m_top  = m_bottom + (m_right - m_left) * height / width;

	CClientDC dc(this);
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc, width, height);
	memDC.SelectObject(&bmp);

	BITMAPINFO bmpInfo; 
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);  
	bmpInfo.bmiHeader.biWidth = width; 
	bmpInfo.bmiHeader.biHeight = -height;
	bmpInfo.bmiHeader.biPlanes = 1;  
	bmpInfo.bmiHeader.biBitCount = 24;  
	bmpInfo.bmiHeader.biCompression = BI_RGB;  
	bmpInfo.bmiHeader.biSizeImage = 0;  
	bmpInfo.bmiHeader.biXPelsPerMeter = 3000;  
	bmpInfo.bmiHeader.biYPelsPerMeter = 3000;  
	bmpInfo.bmiHeader.biClrUsed = 0;  
	bmpInfo.bmiHeader.biClrImportant = 0;  

	long bytesPerLine = (bmpInfo.bmiHeader.biWidth * 3 + 3) / 4 * 4;
	long bufferSize = bytesPerLine * height;

	BYTE *buffer = new BYTE[bufferSize];
	memset(buffer, 0, bufferSize);

	int maxLoop = 1500;

	double w = m_right - m_left;
	double h = m_top - m_bottom;

	int iTmp = -1;
	int index = -1;
	#pragma omp parallel for
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			ComplexNum z;
			ComplexNum c;
			double dTmp;

			int loopCount = 0;
			c.real = w * (i + 1) / width + m_left;
			c.imag = h * (j + 1) / height + m_bottom;
			
			do
			{
				dTmp = z.real * z.real - z.imag * z.imag + c.real;
				z.imag = 2 * z.real * z.imag + c.imag;
				z.real = dTmp;
				++loopCount;
			} while((z.real * z.real + z.imag * z.imag) < 4 && loopCount < maxLoop);

			if (loopCount != maxLoop)
			{
				int iTmp = loopCount  % 255;
				index = j * bytesPerLine + i * 3;
				buffer[index] = iTmp;
				buffer[index + 1] = iTmp * 5;
				buffer[index + 2] = iTmp * 10;
			}
		}
	}

	SetDIBits(dc.m_hDC, bmp, 0, height, buffer, &bmpInfo, DIB_RGB_COLORS);
	delete []buffer;

	dc.BitBlt(0, 0, bmpInfo.bmiHeader.biWidth, height, &memDC, 0, 0, SRCCOPY);

	return true;
}