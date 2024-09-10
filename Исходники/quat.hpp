	// negate
	inline quat operator-(const quat &q) {
		return conjugate(q);
	}