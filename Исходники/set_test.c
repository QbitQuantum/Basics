void main() {
    int i;
    __m128i v1, v2;
    char a1[16], a2[16];

    // packing data
    v1 = _mm_set_epi16(0, 1, 2, 3, 4, 5, 6, 7);
    v2 = _mm_set_epi32(0x0f0e0d0c, 0x0b0a0908, 0x07060504, 0x03020100);
    
    // load data
    _mm_storeu_si128((__m128i*)a1, v1);
    _mm_storeu_si128((__m128i*)a2, v2);

    printarr(a1, "a1");
    printarr(a2, "a2");

}