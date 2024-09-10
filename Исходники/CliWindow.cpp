void
CliWindow::Invalidate (const Rect& region)
{
	Rect bounds = _canvas.GetDrawBounds();
	if (bounds.Intersects(region)) {
		bounds = bounds.Intersect(region);
		Redraw(bounds);
		if (_parent) {
			bounds.Move(Bounds().TopLeft()+_parent->ClientOffset());
			_parent->Invalidate(bounds);
		}
	}
}