void DoubleToComplex(double *srcI, double *srcQ, Complex *dst, const unsigned int len)
{
    __m256d avxR_D, avxI_D, avxX_D, avxY_D, avxA_D, avxB_D;
    __m128 avxA, avxB;
#if 1
    __m256 avxD;
#endif
    for (unsigned int i=0; i+4<=len; i+=4) {
        avxR_D = _mm256_loadu_pd(srcI + i);
        avxI_D = _mm256_loadu_pd(srcQ + i);
        avxX_D = _mm256_unpacklo_pd(avxR_D, avxI_D); //swizzle
        avxY_D = _mm256_unpackhi_pd(avxR_D, avxI_D);
        avxA_D = _mm256_permute2f128_pd(avxX_D, avxY_D, 0x20);
        avxB_D = _mm256_permute2f128_pd(avxX_D, avxY_D, 0x31);
        avxA = _mm256_cvtpd_ps(avxA_D); //double to float
        avxB = _mm256_cvtpd_ps(avxB_D);
#if 0
        avxD = _mm256_castps128_ps256(avxA); 
        avxD = _mm256_insertf128_ps(avxD, avxB, 1);
        _mm256_storeu_ps((float*)(dst+i), avxD);
#else
        _mm_maskstore_ps((float*)(dst+i), _mm_set_epi32(SET_1, SET_1, SET_1, SET_1), avxA);
        _mm_maskstore_ps((float*)(dst+i+2), _mm_set_epi32(SET_1, SET_1, SET_1, SET_1), avxB);
#endif
    }

    for (unsigned int i=len-(len & 0x03); i<len; ++i) {
        dst[i].m_real = static_cast<float>(srcI[i]);
        dst[i].m_imag = static_cast<float>(srcQ[i]);
    }
}