foo (long long *v)
{
  return _mm256_set_epi64x (v[3], v[2], v[1], v[0]);
}