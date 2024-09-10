BOOL GradientRectangle(HDC hDC, int x0, int y0, int x1, int y1, COLORREF c0, COLORREF c1, int angle)
{
	TRIVERTEX vert[4] = { 
		{ x0, y0,  R16(c0), G16(c0), B16(c0), 0 },				//  0:c0         3:(c0+c1)/2
		{ x1, y1,  R16(c1), G16(c1), B16(c1), 0 },				//
		{ x0, y1,  R16(c0, c1), G16(c0, c1), B16(c0, c1), 0 },	//
		{ x1, y0,  R16(c0, c1), G16(c0, c1), B16(c0, c1), 0 }	//  2:(c0+c1)/2  1: c1
	};

	ULONG Index[] = { 0, 1, 2, 0, 1, 3};

	switch ( angle % 180 )
	{
	case   0: 
		return GradientFill(hDC, vert, 2, Index, 1, GRADIENT_FILL_RECT_H);

	case  45: 
		return GradientFill(hDC, vert, 4, Index, 2, GRADIENT_FILL_TRIANGLE);

	case  90: 
		return GradientFill(hDC, vert, 2, Index, 1, GRADIENT_FILL_RECT_V);

	case 135: 
		vert[0].x = x1;
		vert[3].x = x0;
		vert[1].x = x0;
		vert[2].x = x1;
		return GradientFill(hDC, vert, 4, Index, 2, GRADIENT_FILL_TRIANGLE);
	}

	return FALSE;
}