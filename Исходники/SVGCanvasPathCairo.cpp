wxSVGRect wxSVGCanvasPathCairo::GetResultBBox(const wxCSSStyleDeclaration& style, const wxSVGMatrix& matrix) {
	if (&matrix) {
		cairo_matrix_t m;
		cairo_matrix_init(&m, matrix.GetA(), matrix.GetB(), matrix.GetC(), matrix.GetD(), matrix.GetE(), matrix.GetF());
		cairo_set_matrix(m_cr, &m);
	}
	ApplyStrokeStyle(m_cr, style);
	double x1, y1, x2, y2;
	if (style.GetStrokeWidth() > 0)
		cairo_stroke_extents(m_cr, &x1, &y1, &x2, &y2);
	else
		cairo_fill_extents(m_cr, &x1, &y1, &x2, &y2);
	if (&matrix) {
		cairo_matrix_t mat;
		cairo_matrix_init(&mat, 1, 0, 0, 1, 0, 0);
		cairo_set_matrix(m_cr, &mat);
	}
	return wxSVGRect(x1, y1, x2 - x1, y2 - y1);
}