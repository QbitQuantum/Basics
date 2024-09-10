// @return true iff the two pages differ; false otherwise.
// @note Uses SSE3, so you must compile with -msse3.
bool pagesDifferent (const void * b1, const void * b2) {

  enum { PAGE_SIZE = 4096 };

  // Make a mask, initially all 1's.
  register __m128i mask = _mm_setzero_si128();
  mask = _mm_cmpeq_epi32(mask, mask); 


  __m128i * buf1 = (__m128i *) b1;
  __m128i * buf2 = (__m128i *) b2;

  // Some vectorizing pragamata here; not sure if gcc implements them.

#pragma vector always
  for (int i = 0; i < PAGE_SIZE / sizeof(__m128i); i += 8) {
#pragma ivdep
#pragma vector aligned

    register __m128i xmm1, xmm2;

    // Unrolled loop for speed: we load two 128-bit chunks,
    // and logically AND in their comparison.
    // If the mask gets any zero bits, the bytes differ.
    xmm1 = _mm_load_si128 (&buf1[i]);
    xmm2 = _mm_load_si128 (&buf2[i]);
    mask = _mm_and_si128 (mask, _mm_cmpeq_epi32 (xmm1, xmm2));
    xmm1 = _mm_load_si128 (&buf1[i+1]);
    xmm2 = _mm_load_si128 (&buf2[i+1]);
    mask = _mm_and_si128 (mask, _mm_cmpeq_epi32 (xmm1, xmm2));
    xmm1 = _mm_load_si128 (&buf1[i+2]);
    xmm2 = _mm_load_si128 (&buf2[i+2]);
    mask = _mm_and_si128 (mask, _mm_cmpeq_epi32 (xmm1, xmm2));
    xmm1 = _mm_load_si128 (&buf1[i+3]);
    xmm2 = _mm_load_si128 (&buf2[i+3]);
    mask = _mm_and_si128 (mask, _mm_cmpeq_epi32 (xmm1, xmm2));
    xmm1 = _mm_load_si128 (&buf1[i+4]);
    xmm2 = _mm_load_si128 (&buf2[i+4]);
    mask = _mm_and_si128 (mask, _mm_cmpeq_epi32 (xmm1, xmm2));
    xmm1 = _mm_load_si128 (&buf1[i+5]);
    xmm2 = _mm_load_si128 (&buf2[i+5]);
    mask = _mm_and_si128 (mask, _mm_cmpeq_epi32 (xmm1, xmm2));
    xmm1 = _mm_load_si128 (&buf1[i+6]);
    xmm2 = _mm_load_si128 (&buf2[i+6]);
    mask = _mm_and_si128 (mask, _mm_cmpeq_epi32 (xmm1, xmm2));
    xmm1 = _mm_load_si128 (&buf1[i+7]);
    xmm2 = _mm_load_si128 (&buf2[i+7]);
    mask = _mm_and_si128 (mask, _mm_cmpeq_epi32 (xmm1, xmm2));

    // Save the mask to see whether we have found a difference or not.
    unsigned long long buf[128 / sizeof(unsigned long long) / 8]  __attribute__((aligned(16)));
    _mm_store_si128 ((__m128i *) &buf, mask);
    
    // IMPORTANT: make sure long long = 64bits!
    enum { VERIFY_LONGLONG_64 = 1 / (sizeof(long long) == 8) };

    // Now check the result.
    // Both buf[0] and buf[1] should be all ones.
    if ((buf[0] != (unsigned long long) -1) ||
	(buf[1] != (unsigned long long) -1)) {
      return true;
    }
  }

  // No differences found.
  return false;
}