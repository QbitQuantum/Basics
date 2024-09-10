/*
 =================
 FloatToShort
 =================
*/
short FloatToShort (float f){

#if defined SIMD_X86

	__m128	xmm;
	int		i;

	xmm = _mm_load_ss(&f);
	xmm = _mm_max_ss(xmm, _mm_set_ss(-32768.0f));
	xmm = _mm_min_ss(xmm, _mm_set_ss(32767.0f));
	i = _mm_cvtt_ss2si(xmm);

	return i;

#else

	int		i;

	i = (int)f;

	if (i < -32768)
		return -32768;

	if (i > 32767)
		return 32767;

	return i;

#endif
}