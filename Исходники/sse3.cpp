int main(int, char**)
{
    volatile __m128d a = _mm_set1_pd(6.28);
    volatile __m128d b = _mm_set1_pd(3.14);
    volatile __m128d result = _mm_addsub_pd(a, b);
    result = _mm_movedup_pd(result);
    return 0;
}