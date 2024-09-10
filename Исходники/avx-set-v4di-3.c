foo (long long x)
{
  return _mm256_set_epi64x (x, x, x, x);
}