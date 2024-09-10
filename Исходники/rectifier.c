static inline void rectifier_kernel_avx10(float *a, const size_t blocks) {
    for (size_t i = 0; i < blocks; ++i) {
        _mm256_store_ps( &a[i*8*10 + 0*8], _mm256_max_ps( _mm256_load_ps( &a[i*8*10 + 0*8] ) , _mm256_setzero_ps() ) );
        _mm256_store_ps( &a[i*8*10 + 1*8], _mm256_max_ps( _mm256_load_ps( &a[i*8*10 + 1*8] ) , _mm256_setzero_ps() ) );
        _mm256_store_ps( &a[i*8*10 + 2*8], _mm256_max_ps( _mm256_load_ps( &a[i*8*10 + 2*8] ) , _mm256_setzero_ps() ) );
        _mm256_store_ps( &a[i*8*10 + 3*8], _mm256_max_ps( _mm256_load_ps( &a[i*8*10 + 3*8] ) , _mm256_setzero_ps() ) );
        _mm256_store_ps( &a[i*8*10 + 4*8], _mm256_max_ps( _mm256_load_ps( &a[i*8*10 + 4*8] ) , _mm256_setzero_ps() ) );
        _mm256_store_ps( &a[i*8*10 + 5*8], _mm256_max_ps( _mm256_load_ps( &a[i*8*10 + 5*8] ) , _mm256_setzero_ps() ) );
        _mm256_store_ps( &a[i*8*10 + 6*8], _mm256_max_ps( _mm256_load_ps( &a[i*8*10 + 6*8] ) , _mm256_setzero_ps() ) );
        _mm256_store_ps( &a[i*8*10 + 7*8], _mm256_max_ps( _mm256_load_ps( &a[i*8*10 + 7*8] ) , _mm256_setzero_ps() ) );
        _mm256_store_ps( &a[i*8*10 + 8*8], _mm256_max_ps( _mm256_load_ps( &a[i*8*10 + 8*8] ) , _mm256_setzero_ps() ) );
        _mm256_store_ps( &a[i*8*10 + 9*8], _mm256_max_ps( _mm256_load_ps( &a[i*8*10 + 9*8] ) , _mm256_setzero_ps() ) );
    }
}