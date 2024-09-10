foo_r (long long *v)
{
  return _mm512_setr_epi64 (v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7]);
}