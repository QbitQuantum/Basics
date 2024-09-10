 inline
 void scatter(double *ptr, const int *offsets) const
 {
     __m256i indices;
     indices = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(offsets));
     _mm512_i32scatter_pd(ptr, indices, val, 8);
 }