vector unit_vector(const vector& v) {
	if (v.x == 0 && v.y == 0)
		return v;

	auto length = v.length();

	return{ v.x / length, v.y / length };
}