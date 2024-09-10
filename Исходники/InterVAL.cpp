Interval Interval::intersect(Interval& other) {
	Interval result;
	if (isEmpty() || other.isEmpty()) {
		return result;
	}
	if (intersects(*this, other)) {
		result = Interval(std::max(_min, other._min), std::min(_max, other._max));
	}
	return result;
}