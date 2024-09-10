	static inline scomplex_t mic_reduce_add_cps(mic_m512c_t v) {
		scomplex_t temp;
		temp.x = _mm512_reduce_add_ps(v.xvec);
		temp.y = _mm512_reduce_add_ps(v.yvec);
		return temp;
	} // mic_reduce_add_cps()