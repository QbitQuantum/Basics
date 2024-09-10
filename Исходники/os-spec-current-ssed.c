inline void vwl_s1( __m128d const vqn, __m128d const vx0, __m128d const vx1, __m128d vwl[] ) {

  vwl[0] = _mm_mul_pd( vqn, _mm_sub_pd( vx1, vx0 ) ); 
}