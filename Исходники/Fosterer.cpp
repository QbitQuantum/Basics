void GDITest(void)
{
	ENUMLOGFONTEXW enumlog;
	EXTLOGFONTW extlog;
	
	memset(& enumlog, 0, sizeof(enumlog));
	memset(& extlog, 0, sizeof(extlog));

	int j = sizeof(enumlog);
	int k = sizeof(extlog);
	
	for (int i=0; i<sizeof(FIXARRAY)/sizeof(long); i++)
	{
		char t[20];

		long v = FIXARRAY[i];

		if ( v >= 0)
			t[0] = '+';
		else
		{
			t[0] = '-';
			v = - v;
		}

		sprintf(t+1, "%d + %d/16\n", v/16, v%16);
		OutputDebugString(t);
	}

	HDC hDC = GetDC(NULL);
	
	HBITMAP bmp1 = CreateBitmap(100, 100, 1, 1, NULL);
	HBITMAP bmp2 = CreateBitmap(100, 100, 1, 4, NULL);
	HBITMAP bmp3 = CreateBitmap(100, 100, 1, 8, NULL);
	HBITMAP bmp4 = CreateBitmap(100, 100, 3, 8, NULL);
	HBITMAP bmp5 = CreateBitmap(100, 100, 1, 24, NULL);

	void * dibbits;

	HBITMAP bmp6 = CreateDIBSection(hDC, (BITMAPINFO *) & dib, 
					    DIB_RGB_COLORS, & dibbits, NULL, 0);

	BeginPath(hDC);
	MoveToEx(hDC, 100, 100, NULL);
	LineTo(hDC, 150, 150);
	PolyBezierTo(hDC, & Points[0], 3);
	CloseFigure(hDC);
	Ellipse(hDC, -100, -100, 100, 100);
	EndPath(hDC);
	POINT points[20];
	BYTE  types[20];

	int n = GetPath(hDC, NULL, NULL, 0);
	n = GetPath(hDC, points, types, min(n, 20));

	SetBitmapDimensionEx(bmp1, 10000, 10000, NULL);
}