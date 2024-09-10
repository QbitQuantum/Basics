void extern
avx512vl_test (void)
{
  x = _mm256_getmant_pd (y, _MM_MANT_NORM_p75_1p5, _MM_MANT_SIGN_src);
  x = _mm256_mask_getmant_pd (x, m, y, _MM_MANT_NORM_p75_1p5,
			      _MM_MANT_SIGN_src);
  x = _mm256_maskz_getmant_pd (m, y, _MM_MANT_NORM_p75_1p5,
			       _MM_MANT_SIGN_src);
  a = _mm_getmant_pd (b, _MM_MANT_NORM_p75_1p5, _MM_MANT_SIGN_src);
  a = _mm_mask_getmant_pd (a, m, b, _MM_MANT_NORM_p75_1p5,
			   _MM_MANT_SIGN_src);
  a = _mm_maskz_getmant_pd (m, b, _MM_MANT_NORM_p75_1p5,
			    _MM_MANT_SIGN_src);
}