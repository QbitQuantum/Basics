foo (float *v)
{
  return _mm256_set_ps (v[7], v[6], v[5], v[4],
			v[3], v[2], v[1], v[0]);
}