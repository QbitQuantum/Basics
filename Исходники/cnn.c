void conv_forward(conv_layer_t* l, vol_t** in, vol_t** out, int start, int end) {
  uint64_t tempTime = timestamp_us();
  for (int i = start; i <= end; i++) {
    vol_t* V = in[i];
    vol_t* A = out[i];
    for(int d = 0; d < 16; d++) {
      vol_t* f = l->filters[d];
      int x = -2;
      int y = -2;
      for(int ay = 0; ay < 32; y += 1, ay++) {
        x = -2;
        for(int ax=0; ax < 32; x += 1, ax++) {
          double a = 0.0;
          __m256d sum = _mm256_setzero_pd();
          for(int fy = 0; fy < 5; fy++) {
            int oy = y + fy;
            for(int fx = 0; fx < 5; fx++) {
              int ox = x + fx;
              if(oy >= 0 && oy < 32 && ox >=0 && ox < 32) {
                __m256d vector = _mm256_loadu_pd (&(f->w[((5 * fy)+fx)*3]));
                __m256d vector2 = _mm256_loadu_pd (&(V->w[((32 * oy)+ox)*3]));
                __m256d vectorMult = _mm256_mul_pd(vector, vector2);
                sum =_mm256_add_pd (vectorMult, sum);
              }
            }
          }
          for(int i = 0; i < 3; i++) {
            a+= sum[i];
          }
          a += l->biases->w[d];
          set_vol(A, ax, ay, d, a);
        }
      }
    }
  }
  l->myTime += timestamp_us() - tempTime;
}