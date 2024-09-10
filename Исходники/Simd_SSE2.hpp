	static inline Simd set(double x, double y) {
		Simd res;
		res.reg = _mm_setr_pd(x, y);
		return res;
	}