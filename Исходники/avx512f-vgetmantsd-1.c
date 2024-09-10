void extern
avx512f_test (void)
{
  x = _mm_getmant_sd (y, z, _MM_MANT_NORM_p75_1p5, _MM_MANT_SIGN_src);
  x = _mm_getmant_round_sd (y, z, _MM_MANT_NORM_p75_1p5, _MM_MANT_SIGN_src,
			    _MM_FROUND_NO_EXC);
}