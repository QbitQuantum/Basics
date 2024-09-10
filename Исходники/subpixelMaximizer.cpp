void SubpixelMaximizer::fitUsingSSE3(float coef[FitMatrix::ROWS], const signed short data[3][3][3]) const
{
  assert(FitMatrix::PADDEDCOLS == 32);
  __m128 localFitMatrixScale = _mm_set_ss(fitMatrix.scale);
  const short* localFitMatrix = fitMatrix();
  // Load data into four SSE Registers
  __m128i x[4];
  signed short* dataFlat = (signed short*) data; // flat arraw of 27 signed shorts
  x[0] = _mm_loadu_si128((__m128i*)(dataFlat + 0));
  x[1] = _mm_loadu_si128((__m128i*)(dataFlat + 8));
  x[2] = _mm_loadu_si128((__m128i*)(dataFlat + 16));
  x[3] = _mm_loadu_si128((__m128i*)(dataFlat + 24));
  x[3] = _mm_srli_si128(_mm_slli_si128(x[3], 10), 10);   // Clear dataFlat[27..31]

  for(int i = 0; i < FitMatrix::ROWS; i++)
  {
    // Compute scalar product between ((float*)x)[0..31] and localFitMatrix
    __m128i sum =             _mm_madd_epi16(x[0], *(__m128i*)(localFitMatrix + 0));
    sum = _mm_add_epi32(sum, _mm_madd_epi16(x[1], *(__m128i*)(localFitMatrix + 8)));
    sum = _mm_add_epi32(sum, _mm_madd_epi16(x[2], *(__m128i*)(localFitMatrix + 16)));
    sum = _mm_add_epi32(sum, _mm_madd_epi16(x[3], *(__m128i*)(localFitMatrix + 24)));
    sum = _mm_hadd_epi32(sum, sum);
    sum = _mm_hadd_epi32(sum, sum);
    _mm_store_ss(coef + i, _mm_mul_ss(_mm_cvtepi32_ps(sum), localFitMatrixScale));
    localFitMatrix += 32;
  }
}