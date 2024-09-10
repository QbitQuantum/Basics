int
tst_audit10_aux (void)
{
#ifdef __AVX512F__
  extern __m512i audit_test (__m512i, __m512i, __m512i, __m512i,
                             __m512i, __m512i, __m512i, __m512i);

  __m512i zmm = _mm512_setzero_si512 ();
  __m512i ret = audit_test (zmm, zmm, zmm, zmm, zmm, zmm, zmm, zmm);

  zmm = _mm512_set1_epi64 (0x12349876);

  if (memcmp (&zmm, &ret, sizeof (ret)))
    abort ();
  return 0;
#else /* __AVX512F__ */
  return 77;
#endif /* __AVX512F__ */
}