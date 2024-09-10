    mul(avx_simd_complex_double<T> lhs, avx_simd_complex_double<T> rhs) {
        //lhs = [x1.real, x1.img, x2.real, x2.img]
        //rhs = [y1.real, y1.img, y2.real, y2.img]

        //ymm1 = [y1.real, y1.real, y2.real, y2.real]
        __m256d ymm1 = _mm256_movedup_pd(rhs.value);

        //ymm2 = [x1.img, x1.real, x2.img, x2.real]
        __m256d ymm2 = _mm256_permute_pd(lhs.value, 0b0101);

        //ymm3 = [y1.imag, y1.imag, y2.imag, y2.imag]
        __m256d ymm3 = _mm256_permute_pd(rhs.value, 0b1111);

        //ymm4 = ymm2 * ymm3
        __m256d ymm4 = _mm256_mul_pd(ymm2, ymm3);

        //result = [(lhs * ymm1) -+ ymm4];

#ifdef __FMA__
        return _mm256_fmaddsub_pd(lhs.value, ymm1, ymm4);
#elif defined(__FMA4__)
        return _mm256_maddsub_pd(lhs.value, ymm1, ymm4);
#else
        __m256d tmp = _mm256_mul_pd(lhs.value, ymm1);
        return _mm256_addsub_pd(tmp, ymm4);
#endif
    }