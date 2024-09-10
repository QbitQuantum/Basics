void DropHighlight::draw(const Common::Rect &) {
	Graphics::Surface *screen = ((PegasusEngine *)g_engine)->_gfx->getWorkArea();

	// Since this is only used in two different ways, I'm only
	// going to implement it in those two ways. Deal with it.

	Common::Rect rect = _bounds;
	rect.grow(-_thickness);
	screen->frameRect(rect, _highlightColor);
	rect.grow(1);
	screen->frameRect(rect, _highlightColor);

	if (_cornerDiameter == 8 && _thickness == 4) {
		rect.grow(1);
		screen->frameRect(rect, _highlightColor);
		screen->hLine(rect.left + 1, rect.top - 1, rect.right - 2, _highlightColor);
		screen->hLine(rect.left + 1, rect.bottom, rect.right - 2, _highlightColor);
		screen->vLine(rect.left - 1, rect.top + 1, rect.bottom - 2, _highlightColor);
		screen->vLine(rect.right, rect.top + 1, rect.bottom - 2, _highlightColor);
	}
}