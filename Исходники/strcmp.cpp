int substr( const char* s1, const char * s2 )
{
        __m128i s1chars = _mm_loadu_si128( (const __m128i *) s2 );
        __m128i s2chars = _mm_loadu_si128( (const __m128i *) (s1));
        return _mm_cmpistri( s1chars, s2chars, _SIDD_CMP_EQUAL_ANY );
}