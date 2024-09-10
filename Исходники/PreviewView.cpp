void PreviewView::DoDraw()
{
	Window::DoDraw();
	Graphics * g = ui::Engine::Ref().g;
	for (size_t i = 0; i < commentTextComponents.size(); i++)
	{
		int linePos = commentTextComponents[i]->Position.Y+commentsPanel->ViewportPosition.Y+commentTextComponents[i]->Size.Y+4;
		if (linePos > 0 && linePos < Size.Y-commentBoxHeight)
		g->draw_line(
				Position.X+1+XRES/2,
				Position.Y+linePos,
				Position.X+Size.X-2,
				Position.Y+linePos,
				255, 255, 255, 100);
	}
	if (c->GetDoOpen())
	{
		g->fillrect(Position.X+(Size.X/2)-101, Position.Y+(Size.Y/2)-26, 202, 52, 0, 0, 0, 210);
		g->drawrect(Position.X+(Size.X/2)-100, Position.Y+(Size.Y/2)-25, 200, 50, 255, 255, 255, 180);
		g->drawtext(Position.X+(Size.X/2)-(Graphics::textwidth("Loading save...")/2), Position.Y+(Size.Y/2)-5, "Loading save...", style::Colour::InformationTitle.Red, style::Colour::InformationTitle.Green, style::Colour::InformationTitle.Blue, 255);
	}
	g->drawrect(Position.X, Position.Y, Size.X, Size.Y, 255, 255, 255, 255);

}