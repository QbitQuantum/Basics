void MovieLooperUI::PositionIndicator::Draw(BRect update)
{
	BRect rect = Bounds();
	
	// draw the focus indicator
	if (IsFocus())
	{
		SetHighColor(navigationColor);
		StrokeRect(rect);
	}
	else // or not
	{
		// how bout a nice bevel?
		SetHighColor(255,255,255,255);
		StrokeLine(rect.RightTop(), rect.RightBottom());
		StrokeLine(rect.LeftBottom(), rect.RightBottom());
		SetHighColor(ui_color(B_PANEL_BACKGROUND_COLOR));
		StrokeLine(rect.LeftTop(), rect.RightTop());
		StrokeLine(rect.LeftTop(), rect.LeftBottom());
	}
	
	// the non-focus-indicating part of the view
	rect.InsetBy(1.0,1.0);
	
	// everything but the knobs
	if (startCoord == 3.0 && endCoord == rect.right-2.0)
	{
		// green
		SetHighColor(clipColor);
		// don't draw where the knobs draw
		rect.left += 5.0;
		rect.right -= 5.0;
		// draw
		FillRect(rect & update);
	}
	else
	{
		BRect left(rect.left, rect.top, startCoord-3.0, rect.bottom),
				right(endCoord+3.0, rect.top, rect.right, rect.bottom),
				middle(startCoord+3.0, rect.top, endCoord-3.0, rect.bottom);
		
		SetHighColor(clipColor);
		FillRect(middle & update);
		SetHighColor(unClipColor);
		FillRect(left & update);
		FillRect(right & update);
	}
	
	// the position indicator
	if (update.left < playCoord && update.right > playCoord)
	{
		if (playCoord >= (startCoord+3.0) && playCoord <= (endCoord-3.0))
		{
			SetHighColor(0,0,0,255);
			StrokeLine(BPoint(playCoord, 1.0), BPoint(playCoord, Bounds().bottom-1.0));
		}
	}
	// and the knobs
	rect.Set(startCoord-2.0, 1.0, startCoord+2.0, Bounds().bottom-1.0);
	if (update.Intersects(rect))
		DrawKnob(startCoord);
	
	rect.Set(endCoord-2.0, 1.0, endCoord+2.0, Bounds().bottom-1.0);
	if (update.Intersects(rect))
		DrawKnob(endCoord);
}