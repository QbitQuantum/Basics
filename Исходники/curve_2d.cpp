void Curve2D::_bake_segment2d(
	std::map<float, Vector2>& r_bake, float p_begin,
	float p_end,
	const Vector2& p_a,
	const Vector2& p_out,
	const Vector2& p_b,
	const Vector2& p_in,
	int p_depth,
	int p_max_depth,
	float p_tol
) const {

	float mp = p_begin + (p_end - p_begin) * 0.5;
	Vector2 beg = _bezier_interp(p_begin, p_a, p_a + p_out, p_b + p_in, p_b);
	Vector2 mid = _bezier_interp(mp, p_a, p_a + p_out, p_b + p_in, p_b);
	Vector2 end = _bezier_interp(p_end, p_a, p_a + p_out, p_b + p_in, p_b);

	Vector2 na =(mid - beg).normalized();
	Vector2 nb =(end - mid).normalized();
	float dp = na.dot(nb);

	if(dp < cos(deg2rad(p_tol))) {
		r_bake[mp]=mid;
	}

	if(p_depth<p_max_depth) {
		_bake_segment2d(r_bake, p_begin, mp, p_a, p_out, p_b, p_in, p_depth + 1, p_max_depth, p_tol);
		_bake_segment2d(r_bake, mp, p_end, p_a, p_out, p_b, p_in, p_depth + 1, p_max_depth, p_tol);
	}
}