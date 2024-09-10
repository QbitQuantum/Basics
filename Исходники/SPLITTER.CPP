void Splitter::drawSplitter() 
{
	PAINTSTRUCT ps;
	RECT rc, rcToDraw1, rcToDraw2, TLrc, BRrc;

	HDC hdc = ::BeginPaint(_hSelf, &ps);
	getClientRect(rc);

	if ((_spiltterSize >= 4) && (_dwFlags & SV_RESIZEWTHPERCNT))
	{
		adjustZoneToDraw(TLrc, TOP_LEFT);
		adjustZoneToDraw(BRrc, BOTTOM_RIGHT);
		paintArrow(hdc, TLrc, isVertical()?ARROW_LEFT:ARROW_UP);
	}

	if (isVertical())
	{
		rcToDraw2.top = (_dwFlags & SV_RESIZEWTHPERCNT)?_clickZone2TL.bottom:0;
		rcToDraw2.bottom = rcToDraw2.top + 2;

		rcToDraw1.top = rcToDraw2.top + 1;
		rcToDraw1.bottom = rcToDraw1.top + 2;
	}
	else
	{
		rcToDraw2.top = 1;
		rcToDraw2.bottom = 3;

		rcToDraw1.top = 2;
		rcToDraw1.bottom = 4;
	}

	int bottom = 0;
	if (_dwFlags & SV_RESIZEWTHPERCNT)
		bottom = (isVertical() ? rc.bottom - _clickZone2BR.bottom : rc.bottom);
	else
		bottom = rc.bottom;

	while (rcToDraw1.bottom <= bottom)
	{
		if (isVertical())
		{
			rcToDraw2.left = 1;
			rcToDraw2.right = 3;

			rcToDraw1.left = 2;
			rcToDraw1.right = 4;
		}
		else
		{
			rcToDraw2.left = _clickZone2TL.right;
			rcToDraw2.right = rcToDraw2.left + 2;

			rcToDraw1.left = rcToDraw2.left;
			rcToDraw1.right = rcToDraw1.left + 2;
		}

		while (rcToDraw1.right <= (isVertical() ? rc.right : rc.right - _clickZone2BR.right))
		{
			::FillRect(hdc, &rcToDraw1, (HBRUSH)(RGB(0xFF, 0xFF, 0xFF)));
			::FillRect(hdc, &rcToDraw2, (HBRUSH)(COLOR_3DSHADOW+1));

			rcToDraw2.left += 4;
			rcToDraw2.right += 4;
			rcToDraw1.left += 4;
			rcToDraw1.right += 4;
		}
		rcToDraw2.top += 4;
		rcToDraw2.bottom += 4;
		rcToDraw1.top += 4;
		rcToDraw1.bottom += 4;
	}

	if ((_spiltterSize >= 4) && (_dwFlags & SV_RESIZEWTHPERCNT))
		paintArrow(hdc, BRrc, isVertical()?ARROW_RIGHT:ARROW_DOWN);

	::EndPaint(_hSelf, &ps);
}