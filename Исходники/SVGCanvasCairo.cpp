void wxSVGCanvasCairo::SetMatrix(cairo_t* cr, const wxSVGMatrix& matrix) {
	cairo_matrix_t mat;
	cairo_matrix_init(&mat, matrix.GetA(), matrix.GetB(), matrix.GetC(),
			matrix.GetD(), matrix.GetE(), matrix.GetF());
	cairo_set_matrix(cr, &mat);
}