        template <bool align> SIMD_INLINE float SquaredDifferenceSum32f(const float * a, const float * b, size_t size)
        {
            if(align)
                assert(Aligned(a) && Aligned(b));

            float sum = 0;
            size_t i = 0;
            size_t alignedSize = AlignLo(size, 8);
            if(alignedSize)
            {
                __m256 _sum = _mm256_setzero_ps();
                for(; i < alignedSize; i += 8)
                {
                    __m256 _a = Avx::Load<align>(a + i);
                    __m256 _b = Avx::Load<align>(b + i);
                    __m256 _d = _mm256_sub_ps(_a, _b);
                    _sum = _mm256_add_ps(_sum, _mm256_mul_ps(_d, _d));
                }
                sum += Avx::ExtractSum(_sum);
            }
            for(; i < size; ++i)
                sum += Simd::Square(a[i] - b[i]);
            return sum;
        }