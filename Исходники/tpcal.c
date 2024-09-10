void DoPaint(HDC hdc)
{
	const char szInstructions[] = "Please touch the center of the target.";

	POINT p;
	int i, n;
	int old_rop;
	POINT last = current_target_location;
	HPEN hOldPen;
	
	if (current_target == total_targets) {
		RECT r = {10, yext/2,  xext - 10, yext/2 + 40};
		DrawDone(hdc, r);
		return;
	}
	
	if (current_target == 0)
	{
		RECT r = {10, yext - 85, xext - 10, yext - 10};
		DrawAbout(hdc, r);
	}

	current_target_location = GetTarget(current_target);

	old_rop = SetROP2(hdc, R2_XORPEN);
	hOldPen = SelectObject(hdc, GetStockObject(WHITE_PEN));

	n = 20;
	for (i=0; i < n; i++)
	{
		p.x = last.x + ((current_target_location.x - last.x) * i / n);
		p.y = last.y + ((current_target_location.y - last.y) * i / n);
		DrawTarget(hdc, p);
		Sleep(60);
		DrawTarget(hdc, p);
	}

	// final position
	SetROP2(hdc, R2_COPYPEN);
	SelectObject(hdc, GetStockObject(BLACK_PEN));

	DrawTarget(hdc, current_target_location);
	DrawLabel(hdc, current_target_location, szInstructions);

	// put things back
	SetROP2(hdc, old_rop);
	SelectObject(hdc, hOldPen);
}