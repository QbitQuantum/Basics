void extern
avx512f_test (void)
{
  x = _mm512_mask_loadu_epi64 (x, m, p);
  x = _mm512_maskz_loadu_epi64 (m, p);

  _mm512_mask_storeu_epi64 (p, m, x);
}