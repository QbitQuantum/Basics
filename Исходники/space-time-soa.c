/*
 * Compute: s = sqrt( t**2 - x**2 - y**2 - z**2 ), with s, t, x, y, z
 * member variables of the st_coords structure arr.
 *
 * Traverse elements randomly
 */
void
comp_s(st_coords arr, int L)
{
  for(int j=0; j<L; j+=8) {
    int i = (rand() % (L/8)) * 8;
    __m256 x = _mm256_load_ps(&arr.x[i]);
    __m256 y = _mm256_load_ps(&arr.y[i]);
    __m256 z = _mm256_load_ps(&arr.z[i]);
    __m256 t = _mm256_load_ps(&arr.t[i]);
#ifdef FMA
    register __m256 s0;
    s0 = _mm256_mul_ps(x, x);
    s0 = _mm256_fmadd_ps(y, y, s0);
    s0 = _mm256_fmadd_ps(z, z, s0);
    s0 = _mm256_fmsub_ps(t, t, s0);
    s0 = _mm256_sqrt_ps(s0);
#else
    register __m256 s0, s1;
    s1 = _mm256_mul_ps(x, x);
    s0 = _mm256_mul_ps(y, y);
    s1 = _mm256_add_ps(s0, s1);
    s0 = _mm256_mul_ps(z, z);
    s1 = _mm256_add_ps(s0, s1);
    s0 = _mm256_mul_ps(t, t);
    s1 = _mm256_sub_ps(s0, s1);
    s0 = _mm256_sqrt_ps(s1);
#endif
    
    _mm256_store_ps(&arr.s[i], s0);
  }  
  return;
}