int main(int, char**)
{
    volatile __m256d a = _mm256_setzero_pd();
    volatile __m256d b = _mm256_set1_pd(42.42);
    volatile __m256d result = _mm256_add_pd(a, b);
    (void)result;
    return 0;
}