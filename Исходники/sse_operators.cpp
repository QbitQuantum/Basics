__m128i operator^(sse_vector a, sse_vector b) {

    return _mm_xor_si128(a.v, b.v);
}