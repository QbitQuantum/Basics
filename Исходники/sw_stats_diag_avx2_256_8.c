static inline __m256i _mm256_unpackhi_epi8_rpl(__m256i a, __m256i b) {
    __m256i an = _mm256_permute4x64_epi64(a, _MM_SHUFFLE(3,3,2,2));
    __m256i bn = _mm256_permute4x64_epi64(b, _MM_SHUFFLE(3,3,2,2));
    return _mm256_unpackhi_epi8(an, bn);
}