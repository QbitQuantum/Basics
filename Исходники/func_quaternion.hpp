inline float64x4_t conjugate(const float64x4_t ymm)
{
    static const float64x4_t sign_mask = _mm256_setr_pd(+0.0, -0.0, -0.0, -0.0);

    float64x4_t xor0 = _mm256_xor_pd(ymm, sign_mask);
    return xor0;
}