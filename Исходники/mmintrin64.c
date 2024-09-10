void _mm_stream_pi(__m64* _MM1, __m64 _MM2)
{
    _mm_stream_si32(&(_MM1->m64_i32[0]), _MM2.m64_i32[0]);
    _mm_stream_si32(&(_MM1->m64_i32[1]), _MM2.m64_i32[1]);
}