static void
TEST (void)
{
  int i;

  init_data (src1, edst);

  for (i = 0; i < NUM; i += 16)
    {
      resdst[i]  = _mm_aeskeygenassist_si128 (src1[i], IMM8);
      resdst[i + 1] = _mm_aeskeygenassist_si128 (src1[i + 1], IMM8);
      resdst[i + 2] = _mm_aeskeygenassist_si128 (src1[i + 2], IMM8);
      resdst[i + 3] = _mm_aeskeygenassist_si128 (src1[i + 3], IMM8);
      resdst[i + 4] = _mm_aeskeygenassist_si128 (src1[i + 4], IMM8);
      resdst[i + 5] = _mm_aeskeygenassist_si128 (src1[i + 5], IMM8);
      resdst[i + 6] = _mm_aeskeygenassist_si128 (src1[i + 6], IMM8);
      resdst[i + 7] = _mm_aeskeygenassist_si128 (src1[i + 7], IMM8);
      resdst[i + 8] = _mm_aeskeygenassist_si128 (src1[i + 8], IMM8);
      resdst[i + 9] = _mm_aeskeygenassist_si128 (src1[i + 9], IMM8);
      resdst[i + 10] = _mm_aeskeygenassist_si128 (src1[i + 10], IMM8);
      resdst[i + 11] = _mm_aeskeygenassist_si128 (src1[i + 11], IMM8);
      resdst[i + 12] = _mm_aeskeygenassist_si128 (src1[i + 12], IMM8);
      resdst[i + 13] = _mm_aeskeygenassist_si128 (src1[i + 13], IMM8);
      resdst[i + 14] = _mm_aeskeygenassist_si128 (src1[i + 14], IMM8);
      resdst[i + 15] = _mm_aeskeygenassist_si128 (src1[i + 15], IMM8);
    }

  for (i = 0; i < NUM; i++)
    if (memcmp(edst + i, resdst + i, sizeof (__m128i)))
      abort ();
}