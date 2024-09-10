BOOL CFigure::Draw(static HDC hdc, static float Scale)
{
	BOOL tmp = true;
	wchar_t buffer[64];

	HPEN hp = CreatePen(borderStyle, 0, borderColor);
	HBRUSH hbr = CreateHatchBrush(backgroundStyle, backgroundColor);

	SelectObject(hdc, hp);

	if (backgroundStyle == -1) {
		SetDCBrushColor(hdc, backgroundColor);
		SelectObject(hdc, GetStockObject(DC_BRUSH));
	}
	else
		SelectObject(hdc, hbr);

	if (strcmp(type, "line") == 0) {
		tmp = MoveToEx(hdc, start.GetX() * Scale, start.GetY() * Scale, NULL);
		if (!tmp)
			return tmp;
		tmp = LineTo(hdc, end.GetX() * Scale, end.GetY() * Scale);
	}
	else if (strcmp(type, "rectangle") == 0) {
		tmp = Rectangle(hdc, start.GetX() * Scale, start.GetY() * Scale, end.GetX() * Scale, end.GetY() * Scale);
	}
	else if (strcmp(type, "rectangle_rounded") == 0) {
		tmp = RoundRect(hdc, start.GetX() * Scale, start.GetY()* Scale, end.GetX() * Scale, end.GetY() * Scale, 10, 10);

	}
	else if (strcmp(type, "ellipse") == 0) {
		tmp = Ellipse(hdc, start.GetX() * Scale, start.GetY()* Scale, end.GetX() * Scale, end.GetY() * Scale);
	}

	DeleteObject(hp);
	DeleteObject(hbr);

	return tmp;
}