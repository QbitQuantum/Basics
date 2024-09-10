inline static void sse2_memset128aligned(void *ptr, int n, stm_word_t word)
{
#ifdef __LP64__
    __m128d d = (__m128d)_mm_set_epi64((__m64)word, (__m64)word);
#else    
    __m128d d = (__m128d)_mm_set_epi32(word, word, word, word);
#endif
    assert(((stm_word_t)ptr)%16==0);
    assert(n%128==0);
    
    char *p, *endptr = ((char*)ptr)+n; // = ptr;
    for(p = ptr; p < endptr; p+=128) {
	_mm_stream_pd((double*)&p[0], d);
	_mm_stream_pd((double*)&p[16], d);
	_mm_stream_pd((double*)&p[32], d);
	_mm_stream_pd((double*)&p[48], d);
	_mm_stream_pd((double*)&p[64], d);
	_mm_stream_pd((double*)&p[80], d);
	_mm_stream_pd((double*)&p[96], d);
	_mm_stream_pd((double*)&p[112], d);
    }
    _mm_sfence();
}