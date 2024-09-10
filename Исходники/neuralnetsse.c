static inline __m128 sigmoid_positive_ps( __m128 xin )
{
	union {
		__m128i i;
		int32_t i32[4];
	} i;
	__m128 ex;
	float *ex_elem = (float*) &ex;
	__m128 x1 = _mm_min_ps( xin, tens.ps );

	x1 = _mm_mul_ps( x1, tens.ps );
	i.i  = _mm_cvttps_epi32( x1 );
 	ex_elem[0] = e[i.i32[0]];
	ex_elem[1] = e[i.i32[1]];
	ex_elem[2] = e[i.i32[2]];
	ex_elem[3] = e[i.i32[3]];
	x1 = _mm_sub_ps( x1, _mm_cvtepi32_ps( i.i ) ); 
	x1 = _mm_add_ps( x1, tens.ps );
	x1 = _mm_mul_ps( x1, ex );
	x1 = _mm_add_ps( x1, ones.ps ); 
#ifdef __FAST_MATH__
	return _mm_rcp_ps( x1 );
#else
	return _mm_div_ps( ones.ps, x1 );
#endif
}