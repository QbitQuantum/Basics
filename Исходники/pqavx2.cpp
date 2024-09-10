// Compare rank with all values currently in the queue.  Returns -1 if the value already exists
// or is larger than all values.
// Otherwise, returns the index of the register in which the value should be inserted.
// Mask is replicated to both lanes, so it can be used for both value and rank lane.
int PriorityQueue_AVX2::compare(__m256i mrank, int &field, __m256i &gtmask)
{
    static const __m256i eq4mask = _mm256_set_epi32(0, 0, 0, 0, -1, -1, -1, -1);
    __m256i eq, eq4;
    int reg, mask;

    // Because items are sorted in ascending order within each (double) register, the mask after GT
    // comparison must be of the form 000...1111, which is one less than a power of two.
    {
        __m256i r0_7 = _mm256_permute2x128_si256(_rv[1], _rv[0], 0x20);		// [0 .. 7]
        gtmask = _mm256_cmpgt_epi32(r0_7, mrank);
        mask = _mm256_movemask_ps(_mm256_castsi256_ps(gtmask));
        eq = _mm256_cmpeq_epi32(r0_7, mrank);
        _ASSERTE(((mask + 1) & mask) == 0);
        reg = 1;
    }

    if (!mask) {
        __m256i r8_15 = _mm256_permute2x128_si256(_rv[3], _rv[2], 0x20);	// [8 .. 15]
        gtmask = _mm256_cmpgt_epi32(r8_15, mrank);
        mask = _mm256_movemask_ps(_mm256_castsi256_ps(gtmask));
        eq = _mm256_or_si256(eq, _mm256_cmpeq_epi32(r8_15, mrank));
        _ASSERTE(((mask + 1) & mask) == 0);
        reg = 3;
    }

    if (!mask) {
        gtmask = _mm256_cmpgt_epi32(_rv[4], mrank);							// [16 .. 19]; don't care about value
        eq4 = _mm256_and_si256(eq4mask, _mm256_cmpeq_epi32(mrank, _rv[4])); // .. ditto
        mask = _mm256_movemask_ps(_mm256_castsi256_ps(gtmask)) & 0xF;       // ignore comparison with values
        eq = _mm256_or_si256(eq, eq4);
        _ASSERTE(((mask + 1) & mask) == 0);
        reg = 4;
    }

    if (_mm256_movemask_ps(_mm256_castsi256_ps(eq)) != 0)
        mask = 0;
    if (!mask)
        return -1;

    // Adjust register according to mask (higher 128-bits i double register: one register lower)
    // There is no "previous" register to test against for equality if we need to insert in the
    // very first register.  Also duplicate the same mask to both lanes.

    if (mask > 0xF) {
        mask >>= 4;
        --reg;
        gtmask = _mm256_permute2x128_si256(gtmask, gtmask, 0x11);           // replicate high lane to both
    }