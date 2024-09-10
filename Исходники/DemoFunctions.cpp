void PaintClover(HWND hwnd,HRGN hRgnClip, int cxClient, int cyClient)
{
	double      fAngle, fRadius ;
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint (hwnd, &ps) ;

	SetViewportOrgEx (hdc, cxClient / 2, cyClient / 2, NULL) ;
	SelectClipRgn (hdc, hRgnClip) ;

	fRadius = _hypot (cxClient / 2.0, cyClient / 2.0) ;

	for (fAngle = 0.0 ; fAngle < TWOPI ; fAngle += TWOPI / 360)
	{
		MoveToEx (hdc, 0, 0, NULL) ;
		LineTo (hdc, (int) ( fRadius * cos (fAngle) + 0.5),
			(int) (-fRadius * sin (fAngle) + 0.5)) ;
	}
	EndPaint (hwnd, &ps) ;
}