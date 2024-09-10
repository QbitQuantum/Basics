int
main (void)
{
  unsigned int eax, ebx, ecx, edx;

  /* Run AVX test only if AVX is supported.  */
  if (__get_cpuid (1, &eax, &ebx, &ecx, &edx)
      && (ecx & bit_AVX))
    {
      __m256i ymm = _mm256_setzero_si256 ();
      __m256i ret = audit_test (ymm, ymm, ymm, ymm, ymm, ymm, ymm, ymm);

      ymm =  _mm256_set1_epi32 (0x12349876);
      if (memcmp (&ymm, &ret, sizeof (ret)))
	abort ();
    }
  return 0;
}