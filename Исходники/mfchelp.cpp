void ConvertBmp32WithAlphaToBmp32WithoutAlpha (CBitmap& bmp, COLORREF clrBk)
{
	int w, h;

	BITMAP bm;
	bmp.GetBitmap (&bm);

	h = bm.bmHeight;
	w = bm.bmWidth;

	DWORD* pdwBmp32plusA = new  DWORD [w*h];
	bmp.GetBitmapBits (w*h*4, pdwBmp32plusA);

	DWORD* pdwBmp32 = new DWORD [w*h];

	for (int i = 0; i < h; i++)
	{
		for (int k = 0; k < w; k++)
		{
			BmpColor clr = MixColor (pdwBmp32plusA [i*w+k], clrBk);
			pdwBmp32 [(h-1)*w - i*w + k] = clr.clr;
		}
	}

	bmp.DeleteObject ();

	HDC dc = GetDC (NULL);
	bmp.CreateCompatibleBitmap (CDC::FromHandle (dc), w, h);

	BITMAPINFO bi;
	ZeroMemory (&bi, sizeof (bi));
	bi.bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = w;
	bi.bmiHeader.biHeight = h;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biCompression = BI_RGB;
	
	bi.bmiHeader.biBitCount = 32;
	SetDIBits (dc, bmp, 0, h, pdwBmp32, &bi, DIB_RGB_COLORS);

	delete [] pdwBmp32plusA;
	delete [] pdwBmp32;
}