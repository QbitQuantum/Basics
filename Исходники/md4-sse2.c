void hashcat_md4_64 (__m128i digests[4], __m128i W[16])
{
  __m128i a = digests[0];
  __m128i b = digests[1];
  __m128i c = digests[2];
  __m128i d = digests[3];

  __m128i tmp2;

  MD4_STEP (MD4_F , a, b, c, d, W[ 0], MD4C00, MD4S00);
  MD4_STEP (MD4_F , d, a, b, c, W[ 1], MD4C00, MD4S01);
  MD4_STEP (MD4_F , c, d, a, b, W[ 2], MD4C00, MD4S02);
  MD4_STEP (MD4_F , b, c, d, a, W[ 3], MD4C00, MD4S03);
  MD4_STEP (MD4_F , a, b, c, d, W[ 4], MD4C00, MD4S00);
  MD4_STEP (MD4_F , d, a, b, c, W[ 5], MD4C00, MD4S01);
  MD4_STEP (MD4_F , c, d, a, b, W[ 6], MD4C00, MD4S02);
  MD4_STEP (MD4_F , b, c, d, a, W[ 7], MD4C00, MD4S03);
  MD4_STEP (MD4_F , a, b, c, d, W[ 8], MD4C00, MD4S00);
  MD4_STEP (MD4_F , d, a, b, c, W[ 9], MD4C00, MD4S01);
  MD4_STEP (MD4_F , c, d, a, b, W[10], MD4C00, MD4S02);
  MD4_STEP (MD4_F , b, c, d, a, W[11], MD4C00, MD4S03);
  MD4_STEP (MD4_F , a, b, c, d, W[12], MD4C00, MD4S00);
  MD4_STEP (MD4_F , d, a, b, c, W[13], MD4C00, MD4S01);
  MD4_STEP (MD4_F , c, d, a, b, W[14], MD4C00, MD4S02);
  MD4_STEP (MD4_F , b, c, d, a, W[15], MD4C00, MD4S03);

  MD4_STEP (MD4_G , a, b, c, d, W[ 0], MD4C01, MD4S10);
  MD4_STEP (MD4_G , d, a, b, c, W[ 4], MD4C01, MD4S11);
  MD4_STEP (MD4_G , c, d, a, b, W[ 8], MD4C01, MD4S12);
  MD4_STEP (MD4_G , b, c, d, a, W[12], MD4C01, MD4S13);
  MD4_STEP (MD4_G , a, b, c, d, W[ 1], MD4C01, MD4S10);
  MD4_STEP (MD4_G , d, a, b, c, W[ 5], MD4C01, MD4S11);
  MD4_STEP (MD4_G , c, d, a, b, W[ 9], MD4C01, MD4S12);
  MD4_STEP (MD4_G , b, c, d, a, W[13], MD4C01, MD4S13);
  MD4_STEP (MD4_G , a, b, c, d, W[ 2], MD4C01, MD4S10);
  MD4_STEP (MD4_G , d, a, b, c, W[ 6], MD4C01, MD4S11);
  MD4_STEP (MD4_G , c, d, a, b, W[10], MD4C01, MD4S12);
  MD4_STEP (MD4_G , b, c, d, a, W[14], MD4C01, MD4S13);
  MD4_STEP (MD4_G , a, b, c, d, W[ 3], MD4C01, MD4S10);
  MD4_STEP (MD4_G , d, a, b, c, W[ 7], MD4C01, MD4S11);
  MD4_STEP (MD4_G , c, d, a, b, W[11], MD4C01, MD4S12);
  MD4_STEP (MD4_G , b, c, d, a, W[15], MD4C01, MD4S13);

  MD4_STEP (MD4_H1, a, b, c, d, W[ 0], MD4C02, MD4S20);
  MD4_STEP (MD4_H2, d, a, b, c, W[ 8], MD4C02, MD4S21);
  MD4_STEP (MD4_H1, c, d, a, b, W[ 4], MD4C02, MD4S22);
  MD4_STEP (MD4_H2, b, c, d, a, W[12], MD4C02, MD4S23);
  MD4_STEP (MD4_H1, a, b, c, d, W[ 2], MD4C02, MD4S20);
  MD4_STEP (MD4_H2, d, a, b, c, W[10], MD4C02, MD4S21);
  MD4_STEP (MD4_H1, c, d, a, b, W[ 6], MD4C02, MD4S22);
  MD4_STEP (MD4_H2, b, c, d, a, W[14], MD4C02, MD4S23);
  MD4_STEP (MD4_H1, a, b, c, d, W[ 1], MD4C02, MD4S20);
  MD4_STEP (MD4_H2, d, a, b, c, W[ 9], MD4C02, MD4S21);
  MD4_STEP (MD4_H1, c, d, a, b, W[ 5], MD4C02, MD4S22);
  MD4_STEP (MD4_H2, b, c, d, a, W[13], MD4C02, MD4S23);
  MD4_STEP (MD4_H1, a, b, c, d, W[ 3], MD4C02, MD4S20);
  MD4_STEP (MD4_H2, d, a, b, c, W[11], MD4C02, MD4S21);
  MD4_STEP (MD4_H1, c, d, a, b, W[ 7], MD4C02, MD4S22);
  MD4_STEP (MD4_H2, b, c, d, a, W[15], MD4C02, MD4S23);

  digests[0] = _mm_add_epi32 (a, digests[0]);
  digests[1] = _mm_add_epi32 (b, digests[1]);
  digests[2] = _mm_add_epi32 (c, digests[2]);
  digests[3] = _mm_add_epi32 (d, digests[3]);
}