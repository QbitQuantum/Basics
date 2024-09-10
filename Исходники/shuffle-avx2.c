/* Routine optimized for unshuffling a buffer for a type size of 16 bytes. */
static void
unshuffle16_avx2(uint8_t* const dest, const uint8_t* const src,
  const size_t vectorizable_elements, const size_t total_elements)
{
  static const size_t bytesoftype = 16;
  size_t i;
  int j;
  __m256i ymm0[16], ymm1[16];

  for (i = 0; i < vectorizable_elements; i += sizeof(__m256i)) {
    /* Fetch 32 elements (512 bytes) into 16 YMM registers. */
    const uint8_t* const src_for_ith_element = src + i;
    for (j = 0; j < 16; j++) {
      ymm0[j] = _mm256_loadu_si256((__m256i*)(src_for_ith_element + (j * total_elements)));
    }

    /* Shuffle bytes */
    for (j = 0; j < 8; j++) {
      /* Compute the low 32 bytes */
      ymm1[j] = _mm256_unpacklo_epi8(ymm0[j*2], ymm0[j*2+1]);
      /* Compute the hi 32 bytes */
      ymm1[8+j] = _mm256_unpackhi_epi8(ymm0[j*2], ymm0[j*2+1]);
    }
    /* Shuffle 2-byte words */
    for (j = 0; j < 8; j++) {
      /* Compute the low 32 bytes */
      ymm0[j] = _mm256_unpacklo_epi16(ymm1[j*2], ymm1[j*2+1]);
      /* Compute the hi 32 bytes */
      ymm0[8+j] = _mm256_unpackhi_epi16(ymm1[j*2], ymm1[j*2+1]);
    }
    /* Shuffle 4-byte dwords */
    for (j = 0; j < 8; j++) {
      /* Compute the low 32 bytes */
      ymm1[j] = _mm256_unpacklo_epi32(ymm0[j*2], ymm0[j*2+1]);
      /* Compute the hi 32 bytes */
      ymm1[8+j] = _mm256_unpackhi_epi32(ymm0[j*2], ymm0[j*2+1]);
    }

    /* Shuffle 8-byte qwords */
    for (j = 0; j < 8; j++) {
      /* Compute the low 32 bytes */
      ymm0[j] = _mm256_unpacklo_epi64(ymm1[j*2], ymm1[j*2+1]);
      /* Compute the hi 32 bytes */
      ymm0[8+j] = _mm256_unpackhi_epi64(ymm1[j*2], ymm1[j*2+1]);
    }

    for (j = 0; j < 8; j++) {
      ymm1[j] = _mm256_permute2x128_si256(ymm0[j], ymm0[j+8], 0x20);
      ymm1[j+8] = _mm256_permute2x128_si256(ymm0[j], ymm0[j+8], 0x31);
    }

    /* Store the result vectors in proper order */
    _mm256_storeu_si256((__m256i*)(dest + (i * bytesoftype) + (0 * sizeof(__m256i))), ymm1[0]);
    _mm256_storeu_si256((__m256i*)(dest + (i * bytesoftype) + (1 * sizeof(__m256i))), ymm1[4]);
    _mm256_storeu_si256((__m256i*)(dest + (i * bytesoftype) + (2 * sizeof(__m256i))), ymm1[2]);
    _mm256_storeu_si256((__m256i*)(dest + (i * bytesoftype) + (3 * sizeof(__m256i))), ymm1[6]);
    _mm256_storeu_si256((__m256i*)(dest + (i * bytesoftype) + (4 * sizeof(__m256i))), ymm1[1]);
    _mm256_storeu_si256((__m256i*)(dest + (i * bytesoftype) + (5 * sizeof(__m256i))), ymm1[5]);
    _mm256_storeu_si256((__m256i*)(dest + (i * bytesoftype) + (6 * sizeof(__m256i))), ymm1[3]);
    _mm256_storeu_si256((__m256i*)(dest + (i * bytesoftype) + (7 * sizeof(__m256i))), ymm1[7]);
    _mm256_storeu_si256((__m256i*)(dest + (i * bytesoftype) + (8 * sizeof(__m256i))), ymm1[8]);
    _mm256_storeu_si256((__m256i*)(dest + (i * bytesoftype) + (9 * sizeof(__m256i))), ymm1[12]);
    _mm256_storeu_si256((__m256i*)(dest + (i * bytesoftype) + (10 * sizeof(__m256i))), ymm1[10]);
    _mm256_storeu_si256((__m256i*)(dest + (i * bytesoftype) + (11 * sizeof(__m256i))), ymm1[14]);
    _mm256_storeu_si256((__m256i*)(dest + (i * bytesoftype) + (12 * sizeof(__m256i))), ymm1[9]);
    _mm256_storeu_si256((__m256i*)(dest + (i * bytesoftype) + (13 * sizeof(__m256i))), ymm1[13]);
    _mm256_storeu_si256((__m256i*)(dest + (i * bytesoftype) + (14 * sizeof(__m256i))), ymm1[11]);
    _mm256_storeu_si256((__m256i*)(dest + (i * bytesoftype) + (15 * sizeof(__m256i))), ymm1[15]);
  }
}