__m128i branchfree_search4_avx(int* source, size_t n, __m128i target) {
    __m128i offsets = _mm_setzero_si128();
    if(n == 0) return offsets;

    __m128i ha = _mm_set1_epi32(n>>1);
    while(n>1) {
        n -=  n>>1;
        __m128i offsetsplushalf = _mm_add_epi32(offsets,ha);
        ha = _mm_sub_epi32(ha,_mm_srli_epi32(ha,1));
        __m128i keys = _mm_i32gather_epi32(source,offsetsplushalf,4);
        __m128i lt = _mm_cmplt_epi32(keys,target);
        offsets = _mm_blendv_epi8(offsets,offsetsplushalf,lt);
    }
    __m128i lastkeys = _mm_i32gather_epi32(source,offsets,4);
    __m128i lastlt = _mm_cmplt_epi32(lastkeys,target);
    __m128i oneswhereneeded = _mm_srli_epi32(lastlt,31);
    __m128i  answer = _mm_add_epi32(offsets,oneswhereneeded);
    return answer;
}