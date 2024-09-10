void GraphEdit::_bake_segment2d(Vector<Vector2> &points, Vector<Color> &colors, float p_begin, float p_end, const Vector2 &p_a, const Vector2 &p_out, const Vector2 &p_b, const Vector2 &p_in, int p_depth, int p_min_depth, int p_max_depth, float p_tol, const Color &p_color, const Color &p_to_color, int &lines) const {

	float mp = p_begin + (p_end - p_begin) * 0.5;
	Vector2 beg = _bezier_interp(p_begin, p_a, p_a + p_out, p_b + p_in, p_b);
	Vector2 mid = _bezier_interp(mp, p_a, p_a + p_out, p_b + p_in, p_b);
	Vector2 end = _bezier_interp(p_end, p_a, p_a + p_out, p_b + p_in, p_b);

	Vector2 na = (mid - beg).normalized();
	Vector2 nb = (end - mid).normalized();
	float dp = Math::rad2deg(Math::acos(na.dot(nb)));

	if (p_depth >= p_min_depth && (dp < p_tol || p_depth >= p_max_depth)) {

		points.push_back((beg + end) * 0.5);
		colors.push_back(p_color.linear_interpolate(p_to_color, mp));
		lines++;
	} else {
		_bake_segment2d(points, colors, p_begin, mp, p_a, p_out, p_b, p_in, p_depth + 1, p_min_depth, p_max_depth, p_tol, p_color, p_to_color, lines);
		_bake_segment2d(points, colors, mp, p_end, p_a, p_out, p_b, p_in, p_depth + 1, p_min_depth, p_max_depth, p_tol, p_color, p_to_color, lines);
	}
}