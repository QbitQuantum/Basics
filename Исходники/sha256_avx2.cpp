void inline Write8(unsigned char* out, int offset, __m256i v) {
    v = _mm256_shuffle_epi8(v, _mm256_set_epi32(0x0C0D0E0FUL, 0x08090A0BUL, 0x04050607UL, 0x00010203UL, 0x0C0D0E0FUL, 0x08090A0BUL, 0x04050607UL, 0x00010203UL));
    WriteLE32(out + 0 + offset, _mm256_extract_epi32(v, 7));
    WriteLE32(out + 32 + offset, _mm256_extract_epi32(v, 6));
    WriteLE32(out + 64 + offset, _mm256_extract_epi32(v, 5));
    WriteLE32(out + 96 + offset, _mm256_extract_epi32(v, 4));
    WriteLE32(out + 128 + offset, _mm256_extract_epi32(v, 3));
    WriteLE32(out + 160 + offset, _mm256_extract_epi32(v, 2));
    WriteLE32(out + 192 + offset, _mm256_extract_epi32(v, 1));
    WriteLE32(out + 224 + offset, _mm256_extract_epi32(v, 0));
}