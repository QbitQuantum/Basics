template<> INLINE avxb shuffle<0,1,0,1>(const avxb& b) {
  return _mm256_castpd_ps(_mm256_movedup_pd(_mm256_castps_pd(b)));
}