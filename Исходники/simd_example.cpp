 static void vectorDiv(float* a, float* b, float* c, size_t n) {
         __m128 A, B, C;
         for(size_t i = 0; i < n; i += 4) {
                 A = _mm_load_ps(&a[i]);
                 B = _mm_load_ps(&b[i]);
                 C = _mm_div_ps(A, B);
                 _mm_store_ps(&c[i], C);
         }
 }