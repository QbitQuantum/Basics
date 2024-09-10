void DoMouseMove(HWND hWnd,LONG lParam)
{
    HDC hdc;

    if (mouseDown)
    {
	hdc = GetDC(hWnd);
	/*
	 * Erase the old shape.
	 */
	SaveROP = SetROP2(hdc,R2_NOTXORPEN);
	DrawShape(hdc, thisShape[CurrentPoint].Points.left,
		  thisShape[CurrentPoint].Points.top, oldx, oldy,
		  thisShape[CurrentPoint].theShape,
		  thisShape[CurrentPoint].PenWidth,
		  thisShape[CurrentPoint].PenColor, 1);
	/*
	 * At this point, the slope must be positive because
	 * the coordinates could not have been switched.
	 * The next step is to draw the new shape.
	 */

	oldx = LOWORD(lParam);
	oldy = HIWORD(lParam);
	DrawShape(hdc, thisShape[CurrentPoint].Points.left,
		  thisShape[CurrentPoint].Points.top, oldx, oldy,
		  thisShape[CurrentPoint].theShape,
		  thisShape[CurrentPoint].PenWidth,
		  thisShape[CurrentPoint].PenColor, 1);
	SetROP2(hdc,SaveROP);
	ReleaseDC(hWnd,hdc);
    }

}