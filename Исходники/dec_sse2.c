// Applies filter on 4 pixels (p1, p0, q0 and q1)
static WEBP_INLINE void DoFilter4(__m128i* const p1, __m128i* const p0,
                                  __m128i* const q0, __m128i* const q1,
                                  const __m128i* const mask, int hev_thresh) {
    const __m128i sign_bit = _mm_set1_epi8(0x80);
    const __m128i k64 = _mm_set1_epi8(0x40);
    const __m128i zero = _mm_setzero_si128();
    __m128i not_hev;
    __m128i t1, t2, t3;

    // compute hev mask
    GetNotHEV(p1, p0, q0, q1, hev_thresh, &not_hev);

    // convert to signed values
    FLIP_SIGN_BIT4(*p1, *p0, *q0, *q1);

    t1 = _mm_subs_epi8(*p1, *q1);        // p1 - q1
    t1 = _mm_andnot_si128(not_hev, t1);  // hev(p1 - q1)
    t2 = _mm_subs_epi8(*q0, *p0);        // q0 - p0
    t1 = _mm_adds_epi8(t1, t2);          // hev(p1 - q1) + 1 * (q0 - p0)
    t1 = _mm_adds_epi8(t1, t2);          // hev(p1 - q1) + 2 * (q0 - p0)
    t1 = _mm_adds_epi8(t1, t2);          // hev(p1 - q1) + 3 * (q0 - p0)
    t1 = _mm_and_si128(t1, *mask);       // mask filter values we don't care about

    t2 = _mm_set1_epi8(3);
    t3 = _mm_set1_epi8(4);
    t2 = _mm_adds_epi8(t1, t2);        // 3 * (q0 - p0) + (p1 - q1) + 3
    t3 = _mm_adds_epi8(t1, t3);        // 3 * (q0 - p0) + (p1 - q1) + 4
    SignedShift8b(&t2);                // (3 * (q0 - p0) + hev(p1 - q1) + 3) >> 3
    SignedShift8b(&t3);                // (3 * (q0 - p0) + hev(p1 - q1) + 4) >> 3
    *p0 = _mm_adds_epi8(*p0, t2);      // p0 += t2
    *q0 = _mm_subs_epi8(*q0, t3);      // q0 -= t3
    FLIP_SIGN_BIT2(*p0, *q0);

    // this is equivalent to signed (a + 1) >> 1 calculation
    t2 = _mm_add_epi8(t3, sign_bit);
    t3 = _mm_avg_epu8(t2, zero);
    t3 = _mm_sub_epi8(t3, k64);

    t3 = _mm_and_si128(not_hev, t3);   // if !hev
    *q1 = _mm_subs_epi8(*q1, t3);      // q1 -= t3
    *p1 = _mm_adds_epi8(*p1, t3);      // p1 += t3
    FLIP_SIGN_BIT2(*p1, *q1);
}