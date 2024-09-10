void LO_ElementHint::drawHintRect(DrawContext dc) {
	dc->rectangle(x, y, width, height);
	return;
	static const int r = 5;
	static const double degrees = M_PI / 180.0;

	dc->begin_new_sub_path();
	dc->arc(x + width - r, y + r, r, -90 * degrees, 0 * degrees);
	dc->arc(x + width - r, y + height - r, r, 0 * degrees, 90 * degrees);
	dc->arc(x + r, y + height - r, r, 90 * degrees, 180 * degrees);
	dc->arc(x + r, y + r, r, 180 * degrees, 270 * degrees);
	dc->close_path();
}