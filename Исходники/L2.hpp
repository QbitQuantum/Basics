// TODO: function to take SIZE
// TODO: requires implementation
// matrix is square?
// same questions as above
void matrix_vector_mul_SSE_double(double** mat, double* &vec)
{
  double* result = new double[SIZE]; // should be SIZE of result!
  for(unsigned i=0;i<SIZE;i++) { // row
    __m128d running_sum = _mm_set1_pd(0.0); // running sum initially 0
    for(unsigned j=0;j<SIZE;j+=2) { // col - requires skipping on 2 at a time
      // multiply each
      // add to running sum
      __m128d mat_vect = _mm_load_pd(&mat[i][j]); // hoping that addresses are as expected - seems like this is the way it's stored
						  // ^^ needs explanation and backup for REPORT - ROW major storing order in C/C++ such as python, pascal and others
      __m128d vec_elem = _mm_load_pd(&vec[j]);
      __m128d mult = _mm_mul_pd(mat_vect,vec_elem);
      running_sum = _mm_add_pd(mult,running_sum);


    }
    // shuffle & add (to make hadd)
    // store back to vec[i]
    __m128i mask = _mm_set_epi8(7 ,6 ,5, 4, 3, 2, 1, 0,
		      15, 14, 13, 12, 11, 10, 9, 8);
    __m128i sum_shuffled = _mm_shuffle_epi8((__m128i)running_sum, mask);
    running_sum = _mm_add_pd(running_sum,(__m128d)sum_shuffled);
    // convert running_sum back to f48s and store in memory

    _mm_store_sd(&result[i], running_sum);
  }
  vec = result;
}