int main(int, char**)
{
    volatile __m128i a = _mm_setzero_si128();
    volatile __m128i b = _mm_set1_epi32(42);
    volatile __m128i result = _mm_cmpestrm(a, 16, b, 16, 0);
    (void)result;
    return 0;
}