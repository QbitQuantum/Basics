inline
void addGrids(
    complexd dst[]
  , const complexd srcs[]
  , int nthreads
  , int grid_pitch
  , int grid_size
  )
{
  int siz = grid_size*grid_pitch;
#pragma omp parallel for
  for (unsigned int i = 0; i < siz*sizeof(complexd)/(256/8); i++) {
    __m256d sum = as256pc(srcs)[i];
    // __m256d sum = _mm256_loadu_pd(reinterpret_cast<const double*>(as256pc(srcs)+i));

    for (int g = 1; g < nthreads; g ++)
      sum = _mm256_add_pd(sum, as256pc(srcs + g * siz)[i]);

    as256p(dst)[i] = sum;
  }
}