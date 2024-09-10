void
WebSafeSelector::Draw(BRect updateRect)
{
	ColorSelector::Draw(updateRect);

	if (fIsHidden) {
		SetHighColor(ViewColor());
		FillRect(updateRect);
		return;
	}

	if (updateRect.Intersects(INDICATOR_RECT)) {
		rgb_color black = (rgb_color){ 0, 0, 0 };
		rgb_color light;
		rgb_color medium;
		rgb_color dark;

		if (fMouseOver) {
			light  = (rgb_color){ 0, 255, 0, 255 };
			medium = (rgb_color){ 255, 0, 0, 255 };
			dark   = (rgb_color){ 0, 0, 255, 255 };
		} else {
			light  = tint_color(black, B_LIGHTEN_MAX_TINT);
			medium = tint_color(black, B_LIGHTEN_2_TINT);
			dark   = tint_color(black, B_LIGHTEN_1_TINT);
		}

		BRect bounds = INDICATOR_RECT;

		BPoint pointList[4];
		pointList[0] = bounds.LeftTop() + BPoint(0, 3);
		pointList[1] = bounds.LeftTop() + BPoint(0, 9);
		pointList[2] = bounds.LeftTop() + BPoint(5, 12);
		pointList[3] = bounds.LeftTop() + BPoint(5, 6);

		BPolygon* rhombus1 = new BPolygon(pointList, 4);
		SetHighColor(dark);
		FillPolygon(rhombus1);
		SetHighColor(black);
		StrokePolygon(rhombus1);
		delete rhombus1;

		pointList[0] = bounds.LeftTop() + BPoint(5, 6);
		pointList[1] = bounds.LeftTop() + BPoint(5, 12);
		pointList[2] = bounds.LeftTop() + BPoint(10, 9);
		pointList[3] = bounds.LeftTop() + BPoint(10, 3);

		BPolygon* rhombus2 = new BPolygon(pointList, 4);
		SetHighColor(light);
		FillPolygon(rhombus2);
		SetHighColor(black);
		StrokePolygon(rhombus2);
		delete rhombus2;

		pointList[0] = bounds.LeftTop() + BPoint(0, 3);
		pointList[1] = bounds.LeftTop() + BPoint(5, 6);
		pointList[2] = bounds.LeftTop() + BPoint(10, 3);
		pointList[3] = bounds.LeftTop() + BPoint(5, 0);

		BPolygon* rhombus3 = new BPolygon(pointList, 4);
		SetHighColor(medium);
		FillPolygon(rhombus3);
		SetHighColor(black);
		StrokePolygon(rhombus3);
		delete rhombus3;
	}
}