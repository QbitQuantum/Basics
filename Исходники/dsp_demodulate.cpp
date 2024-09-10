static inline float angle_precise(const complex32_t t) {
	return atan2f(t.imag(), t.real());
}