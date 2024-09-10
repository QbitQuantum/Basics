void RenderOffscreen(HDC hDestDC)
{
	HDC hdc				= hDestDC; // CreateCompatibleDC(hWndMain);
	int err=GetLastError();
	HBITMAP hOldBitmap	= SelectObject(hdc, hbmpOffscreen);
	RECT rect;
	HPEN hPen;
	double dx, dy, px, py,  AngRad, dDeltaAng;
	int pos, p1;
	long CenterX, CenterY;

	hPen = SelectObject(hdc, CreatePen(PS_SOLID, 3, 0L));

	GetClientRect(hWndMain, &rect);

	/* Draw the table */
	CenterX = (rect.right - rect.left)/2;
	CenterY = (rect.bottom - rect.top)/2;
	Ellipse(hdc, CenterX - 100, CenterY - 100, CenterX + 100, CenterY + 100);

	/* Draw the chopsticks */
	dDeltaAng = 360 / PHILOSOPHERS;
	for (pos = 0; pos < PHILOSOPHERS; pos++)	//FIXIT
	{
		/* Draw the chopsticks */
		AngRad = (pos * dDeltaAng)/57.29577951;
		dx = CenterX + (sin(AngRad)*60);
		dy = CenterY - (cos(AngRad)*60);
		MoveToEx(hdc, (int)dx, (int)dy, NULL);
		dx = CenterX + (sin(AngRad)*85);
		dy = CenterY - (cos(AngRad)*85);
		LineTo(hdc, (int)dx, (int)dy);

		//Draw the plate
		AngRad = ((pos * dDeltaAng+dDeltaAng / 2))/57.29577951;
		dx = CenterX + (sin(AngRad) * 72);
		dy = CenterY - (cos(AngRad) * 72);
		Ellipse(hdc, (int)dx-12, (int)dy-12, (int)dx+12, (int)dy+12);
	}

	/* delete the black pen */
	DeleteObject(SelectObject(hdc, hPen));

	/* Draw the philosophers */
	for(pos = 0; pos < PHILOSOPHERS; pos++)
	{
		/* select a pen for each philosopher */
		switch (gDinerState[pos])
		{
		case RESTING:
			hPen = SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(0, 255, 0)));
			break;

		case WAITING:
		case EATING:
			hPen = SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(255, 0, 0)));
			break;

		default:
			hPen = SelectObject(hdc, CreatePen(PS_SOLID, 3, 0L));
		}

		AngRad = ((pos * dDeltaAng) + dDeltaAng / 2)/57.29577951;
		px = CenterX + (sin(AngRad)*150);
		py = CenterY - (cos(AngRad)*150);

		/* Draw the Philosopher */
		Ellipse(hdc, (int)px-25, (int)py-25, (int)px+25, (int)py+25);

		//Draw the left arm
		if (gChopstickState[pos] == pos)
		{
			MoveToEx(hdc, (int)px, (int)py, NULL);
			AngRad = (pos * dDeltaAng)/57.29577951;
			dx = CenterX + (sin(AngRad)*85);
			dy = CenterY - (cos(AngRad)*85);
			LineTo(hdc, (int)dx, (int)dy);
		}

		//Draw the right arm
		p1 = pos + 1;
		if (p1 == PHILOSOPHERS)
			p1 = 0;
		if (gChopstickState[p1] == pos)
		{
			MoveToEx(hdc, (int)px, (int)py, NULL);
			AngRad = (p1 * dDeltaAng)/57.29577951;
			dx = CenterX + (sin(AngRad)*85);
			dy = CenterY - (cos(AngRad)*85);
			LineTo(hdc, (int)dx, (int)dy);
		}

		/* Delete the pen */
		DeleteObject(SelectObject(hdc, hPen));			
	}	//for pos

	BitBlt( hDestDC,
				rect.left,
				rect.top,
				rect.right - rect.left,
				rect.bottom-rect.top,
				hdc,
				rect.left,
				rect.top,
				SRCCOPY
			);
	GetLastError();

	SelectObject(hdc, hOldBitmap);

//	DeleteDC(hWndMain, hdc);
}