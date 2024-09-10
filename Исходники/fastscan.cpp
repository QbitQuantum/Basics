FORCE_INLINE
static inline void ft4_small_table(float qmax, const float* dists, __m128i (&ft4)[4][16], const float qmin) {
	for(int sq_i = 0; sq_i < 4; ++sq_i) {
		const float* const sq_dists = dists + (sq_i + 4) * NCENT;
		for(int h_cent_i = 0; h_cent_i < 16; ++h_cent_i) {
			const float* h_dists = sq_dists + h_cent_i * 16;
			ft4[sq_i][h_cent_i] = _mm_set_epi8(
					Q127(h_dists[15], qmin, qmax),
					Q127(h_dists[14], qmin, qmax),
					Q127(h_dists[13], qmin, qmax),
					Q127(h_dists[12], qmin, qmax),
					Q127(h_dists[11], qmin, qmax),
					Q127(h_dists[10], qmin, qmax),
					Q127(h_dists[9], qmin, qmax),
					Q127(h_dists[8], qmin, qmax),
					Q127(h_dists[7], qmin, qmax),
					Q127(h_dists[6], qmin, qmax),
					Q127(h_dists[5], qmin, qmax),
					Q127(h_dists[4], qmin, qmax),
					Q127(h_dists[3], qmin, qmax),
					Q127(h_dists[2], qmin, qmax),
					Q127(h_dists[1], qmin, qmax),
					Q127(h_dists[0], qmin, qmax)
					);
		}
	}
}