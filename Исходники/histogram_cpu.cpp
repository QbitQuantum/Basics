void reduceHistogram_helper(float* thist,
							float* _hist,
							unsigned int _histx,
							unsigned int _histy,
							unsigned int _histz,
							unsigned int _histdim,
							unsigned int _threads) {
	
	
    // Sum histograms
    // (Could be done using parallel reduction)
    unsigned int i=0;
#ifdef USE_AVX1
    for(  ;i<_histdim; i+=8 ) {
        float *th = thist+i;
        __m256 h1 = _mm256_loadu_ps( th );
        for( unsigned int j=1; j<_threads; ++j ) {
            const __m256 h2 = _mm256_loadu_ps( th+j*_histdim );
            h1 = _mm256_add_ps( h1, h2 );
        }
        _mm256_storeu_ps( _hist+i, h1 );
    }
    i-=8;
#endif
    
    // Do the rest
    for(  ;i<_histdim; i+=1 ) {
        _hist[i] = thist[i];
        for( unsigned int j=1; j<_threads; ++j ) {
            _hist[i] += thist[j*_histdim+i];
        }
    }
	
	
	normalizeHistogram_helper(_hist, _histx, _histy, _histz);
    
}