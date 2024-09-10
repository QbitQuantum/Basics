BI_FORCE_INLINE inline avx_double operator*(const avx_double& o1,
    const double& o2) {
  avx_double res;
  res.packed = _mm256_mul_pd(o1.packed, _mm256_set1_pd(o2));
  return res;
}