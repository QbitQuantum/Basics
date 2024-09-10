void
TTimeWindow::_AlignWindow()
{
	BPoint pt = TimeSettings().LeftTop();
	MoveTo(pt);

	BRect frame = Frame();
	BRect screen = BScreen().Frame();
	if (!frame.Intersects(screen.InsetByCopy(50.0, 50.0))) {
		BRect bounds(Bounds());
		BPoint leftTop((screen.Width() - bounds.Width()) / 2.0,
			(screen.Height() - bounds.Height()) / 2.0);

		MoveTo(leftTop);
	}
}