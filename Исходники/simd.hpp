/// Element-wise comparison for greater than.
inline xmm_i8 operator > (const xmm_i8 &a, const xmm_i8 &b) { return _mm_cmpgt_epi8(a, b); }