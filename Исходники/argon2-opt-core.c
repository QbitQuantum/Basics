void FillBlock(__m128i* state, const uint8_t *ref_block, uint8_t *next_block, const uint64_t* Sbox) {
    __m128i block_XY[ARGON2_QWORDS_IN_BLOCK];
    //__m128i state[64];



    for (uint32_t i = 0; i < ARGON2_QWORDS_IN_BLOCK; i++) {
        block_XY[i] = _mm_load_si128((__m128i *) ref_block);
        ref_block += 16;
    }
    for (uint32_t i = 0; i < ARGON2_QWORDS_IN_BLOCK; i++) {
        block_XY[i] = state[i] = _mm_xor_si128(state[i], block_XY[i]);
    }

    uint64_t x = 0;
    if (Sbox != NULL) {
        x = _mm_extract_epi64(block_XY[0], 0) ^ _mm_extract_epi64(block_XY[ARGON2_QWORDS_IN_BLOCK - 1], 1);
        for (int i = 0; i < 6 * 16; ++i) {
            uint32_t x1 = x >> 32;
            uint32_t x2 = x & 0xFFFFFFFF;
            uint64_t y = Sbox[x1 & ARGON2_SBOX_MASK];
            uint64_t z = Sbox[(x2 & ARGON2_SBOX_MASK) + ARGON2_SBOX_SIZE / 2];
            x = (uint64_t) x1 * (uint64_t) x2;
            x += y;
            x ^= z;
        }
    }