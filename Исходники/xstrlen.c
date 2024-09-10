size_t xstrlen(const char* src)
{
    __m256i m0 = _mm256_setzero_si256();
    __m256i m1 ;
    int mask;
    for (size_t count = 0;; count += 32){
        m1 = _mm256_loadu_si256((const __m256i*)((unsigned long)src + count));
        m1 = _mm256_cmpeq_epi8(m1, m0);
        mask = _mm256_movemask_epi8(m1);
        if (mask != 0) {
            __asm__("bsfl %0, %0\n\t"
                    :"=r"(mask)
                    :"r"(mask)
                   );
            return count + (size_t)mask;
        }
    }