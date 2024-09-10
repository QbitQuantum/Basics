void ConsoleView::OnDraw()
{
	Graphics * g = ui::Engine::Ref().g;
	//g->fillrect(Position.X, Position.Y, Size.X, Size.Y, 0, 61, 76, 180);
	g->fillrect(Position.X, Position.Y, Size.X, Size.Y, 0, 0, 0, 180);
	g->draw_line(Position.X, Position.Y+Size.Y, Position.X+Size.X, Position.Y+Size.Y, 255, 255, 255, 200);
}