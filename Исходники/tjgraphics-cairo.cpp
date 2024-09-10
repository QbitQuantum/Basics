void Graphics::DrawRectangle(Pen* pen, const RectF& rc) {
	cairo_t* cg = reinterpret_cast<cairo_t*>(_private);
	cairo_save(cg);
	PenPrivate* pp = reinterpret_cast<PenPrivate*>(pen->_private);
	cairo_pattern_t* cp = pp->pattern;
	cairo_set_source(cg, cp);
	cairo_set_line_width(cg, pp->width);
	cairo_translate(cg, rc.GetLeft(), rc.GetTop());
	cairo_rectangle(cg, 0, 0, rc.GetWidth(), rc.GetHeight());
	cairo_stroke(cg);
	cairo_restore(cg);
}