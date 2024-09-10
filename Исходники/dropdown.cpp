void DropDown::Draw(const Point& screenPos)
{
	if(!drawn)
	{
		if(optionIndex!=-1)
			TextPosition(options[optionIndex].first);
		drawn = true;
	}
	Graphics * g = ui::Engine::Ref().g;
	Point Position = screenPos;

	ui::Colour textColour = Appearance.TextInactive;
	ui::Colour borderColour = Appearance.BorderInactive;
	ui::Colour backgroundColour = Appearance.BackgroundInactive;

	if (isMouseInside)
	{
		textColour = Appearance.TextHover;
		borderColour = Appearance.BorderHover;
		backgroundColour = Appearance.BackgroundHover;
	}
	else
	{
		textColour = Appearance.TextInactive;
		borderColour = Appearance.BorderInactive;
		backgroundColour = Appearance.BackgroundInactive;
	}

	g->fillrect(Position.X-1, Position.Y-1, Size.X+2, Size.Y+2, backgroundColour.Red, backgroundColour.Green, backgroundColour.Blue, backgroundColour.Alpha);
	g->drawrect(Position.X, Position.Y, Size.X, Size.Y, borderColour.Red, borderColour.Green, borderColour.Blue, borderColour.Alpha);
	if(optionIndex!=-1)
		g->drawtext(Position.X+textPosition.X, Position.Y+textPosition.Y, options[optionIndex].first, textColour.Red, textColour.Green, textColour.Blue, textColour.Alpha);
}