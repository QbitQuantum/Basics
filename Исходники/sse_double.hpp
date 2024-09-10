BI_FORCE_INLINE inline sse_double operator!=(const sse_double& o1,
    const sse_double& o2) {
  sse_double res;
  res.packed = _mm_cmpneq_pd(o1.packed, o2.packed);
  return res;
}