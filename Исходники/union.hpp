  //this method is untested as of right now....
 inline void set_union(Set<bitset> *A_in, Set<bitset> *B_in){
    if(A_in->number_of_bytes > 0 && B_in->number_of_bytes > 0){
      const uint64_t *a_index = (uint64_t*) A_in->data;
      const uint64_t *b_index = (uint64_t*) B_in->data;

      uint64_t* A = (uint64_t*)(A_in->data+sizeof(uint64_t));
      uint64_t* B = (uint64_t*)(B_in->data+sizeof(uint64_t));
      const size_t s_a = ((A_in->number_of_bytes-sizeof(uint64_t))/sizeof(uint64_t));
      const size_t s_b = ((B_in->number_of_bytes-sizeof(uint64_t))/sizeof(uint64_t));

      const bool a_big = a_index[0] > b_index[0];

      assert(a_index[0] <= b_index[0]);

      const uint64_t start_index = (a_big) ? a_index[0] : b_index[0];
      const uint64_t a_start_index = (a_big) ? 0:(b_index[0]-a_index[0]);
      const uint64_t b_start_index = (a_big) ? (a_index[0]-b_index[0]):0;

      const uint64_t end_index = ((a_index[0]+s_a) > (b_index[0]+s_b)) ? (b_index[0]+s_b):(a_index[0]+s_a);
      const uint64_t total_size = (start_index > end_index) ? 0:(end_index-start_index);

      //16 uint16_ts
      //8 ints
      //4 longs
      size_t i = 0;
      A += a_start_index;
      B += b_start_index;
      #if VECTORIZE == 1
      for(; (i+3) < total_size; i += 4, A += 4, B += 4){
        const __m256 a1 = _mm256_loadu_ps((const float*)A);
        const __m256 a2 = _mm256_loadu_ps((const float*)B);
        const __m256 r = _mm256_or_ps(a2, a1);

        _mm256_storeu_ps((float*)A, r);
      }
      #endif

      for(; i < total_size; i++, A++, B++){
        *A |= *B;
      }
    }
  }