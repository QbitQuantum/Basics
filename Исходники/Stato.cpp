void Stato::newVideoMessage(char *header,BYTE *buf)
{
	if(header && buf)
	{
		// received WM_VIDEO -> new data, save it in hdc_mem and then update the image showed

		/*
		byte 2,3: coord x
		byte 4,5: coord y
		byte 6,7: width (px)
		byte 8,9: height (px)
		byte 10,11: bytes per pixel
		*/

		int x,y,width,height,size,bytesperpixel;

		memcpy(&x,				header + 2,2);
		memcpy(&y,				header + 4,2);
		memcpy(&width,			header + 6,2);
		memcpy(&height,			header + 8,2);
		memcpy(&bytesperpixel,	header + 10,2);

		x=ntohs(x);
		y=ntohs(y);
		width=ntohs(width);
		height=ntohs(height);
		bytes_per_pixel=ntohs(bytesperpixel);

		size=width*height*bytes_per_pixel;

		HDC hdc_tmp = CreateCompatibleDC(NULL);

		HBITMAP bitmap = CreateCompatibleBitmap(hdcBuf,width,height);
		
		BITMAPINFOHEADER bmih;
		bmih.biSize = sizeof(BITMAPINFOHEADER);
		bmih.biBitCount = 8*bytes_per_pixel;
		bmih.biClrImportant = 0;
		bmih.biClrUsed = 0;
		bmih.biCompression = BI_RGB;
		bmih.biHeight = height;
		bmih.biWidth = width;
		bmih.biPlanes = 1;
		bmih.biSizeImage = size;
		bmih.biXPelsPerMeter = 0;
		bmih.biYPelsPerMeter = 0;

		BITMAPINFO bmpInfo;
		bmpInfo.bmiHeader = bmih;

		SetDIBits(	hdc_tmp,
					bitmap,
					0,
					height,
					buf,
					&bmpInfo,
					DIB_PAL_COLORS);

		SelectObject(hdc_tmp,bitmap);

		// save in the memory DC (double buffering)
		BitBlt( hdcBuf,
				x,y,
				width,height,
				hdc_tmp,
				0,0,
				SRCCOPY);

		DeleteDC(hdc_tmp);
		DeleteObject(bitmap);
	}

	delete[] header;
	delete[] buf;
}