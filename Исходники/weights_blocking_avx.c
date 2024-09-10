FORCE_INLINE void convolve_block(double* im, int ii, int jj, int N, uint32_t r, uint32_t c, double* dst){
    const double rw = 0.2989;
    const double gw = 0.5870;
    const double bw = 0.1140;
    const __m256d rgb0W = _mm256_setr_pd (rw,gw,bw,0); //rgb0
    const __m256d onehalf = _mm256_set1_pd(0.5);
    const __m256d minustwelvehalf = _mm256_set1_pd(-12.5);
    int64_t hi_bit_set = ((int64_t)1) << 63;
    const __m256i mask1110 = _mm256_setr_epi64x(hi_bit_set,hi_bit_set, hi_bit_set, 0);

    //determine non-special case boundaries
    int i_start = ii;
    int i_end = ii+N;
    int j_start = jj;
    int j_end = jj+N;
    if( ii == 0){
        i_start = 1;
    }
    if( ii + N == r){
        i_end = r-1;
    }
    if( jj == 0){
        j_start = 1;
    }
    if( jj + N == c){
        j_end = c-1;
    }

    if(ii == 0){
        if( jj == 0){
            //top left
            int i = 0;
            int j = 0;
            int center =  i*c+j;
            int bottom = (i+1)*c+j;
            int right   = i*c+j+1;
            dst[center] = single_pixel(im,
                                       3*center,
                                       3*center,3*center,3*right,3*bottom,
                                       mask1110,rgb0W,onehalf,minustwelvehalf);
            COST_INC_LOAD(1);
            COST_INC_STORE(1);
        }
        if( jj + N == c){
            //top right
            int i = 0;
            int j = c-1;
            int center =  i*c+j;
            int bottom = (i+1)*c+j;
            int left   = i*c+j-1;
            dst[center] = single_pixel(im,
                                       3*center,
                                       3*center,3*left,3*center,3*bottom,
                                       mask1110,rgb0W,onehalf,minustwelvehalf);
            COST_INC_LOAD(1);
            COST_INC_STORE(1);
        }
        //need to fill in top row
        int i = 0;
        for(int j = j_start; j < j_end; j++){
            int center =  i*c+j;
            int bottom = (i+1)*c+j;
            int left   = i*c+j-1;
            int right   = i*c+j+1;
            dst[center] = single_pixel(im,
                                       3*center,
                                       3*center,3*left,3*right,3*bottom,
                                       mask1110,rgb0W,onehalf,minustwelvehalf);
            COST_INC_LOAD(1);
            COST_INC_STORE(1);
        }
    }
    if(ii + N == r){
        if( jj == 0){
            //bottom left
            int i = r-1;
            int j = 0;
            int center =  i*c+j;
            int top    = (i-1)*c+j;
            int right   = i*c+j+1;
            dst[center] = single_pixel(im,
                                       3*center,
                                       3*top,3*center,3*right,3*center,
                                       mask1110,rgb0W,onehalf,minustwelvehalf);
            COST_INC_LOAD(1);
            COST_INC_STORE(1);
        }
        if( jj + N == c){
            //bottom right
            int i = r-1;
            int j = c-1;
            int center =  i*c+j;
            int top    = (i-1)*c+j;
            int left   = i*c+j-1;
            dst[center] = single_pixel(im,
                                       3*center,
                                       3*top,3*left,3*center,3*center,
                                       mask1110,rgb0W,onehalf,minustwelvehalf);
            COST_INC_LOAD(1);
            COST_INC_STORE(1);
        }
        //need to fill in bottom row
        int i = r-1;
        for(int j = j_start; j < j_end; j++){
            int center =  i*c+j;
            int top    = (i-1)*c+j;
            int left   = i*c+j-1;
            int right   = i*c+j+1;
            dst[center] = single_pixel(im,
                                       3*center,
                                       3*top,3*left,3*right,3*center,
                                       mask1110,rgb0W,onehalf,minustwelvehalf);
            COST_INC_LOAD(1);
            COST_INC_STORE(1);
        }
    }
    if( jj == 0){
        //need to fill in left edge
        int j = 0;
        for(int i = i_start; i < i_end; i++){
            int center =  i*c+j;
            int top    = (i-1)*c+j;
            int bottom = (i+1)*c+j;
            int right   = i*c+j+1;
            dst[center] = single_pixel(im,
                                       3*center,
                                       3*top,3*center,3*right,3*bottom,
                                       mask1110,rgb0W,onehalf,minustwelvehalf);
            COST_INC_LOAD(1);
            COST_INC_STORE(1);
        }
    }
    if( jj + N == c){
        //need to fill in right edge
        int j = c-1;
        for(int i = i_start; i < i_end; i++){
            int center =  i*c+j;
            int top    = (i-1)*c+j;
            int bottom = (i+1)*c+j;
            int left   = i*c+j-1;
            dst[center] = single_pixel(im,
                                       3*center,
                                       3*top,3*left,3*center,3*bottom,
                                       mask1110,rgb0W,onehalf,minustwelvehalf);
            COST_INC_LOAD(1);
            COST_INC_STORE(1);
        }
    }

    //now we can safely process everything inside the _start and _end margins
    //read pixels from _start-1 until _end+1 and process all inside

    for(int i = i_start; i < i_end; i++){
        for(int j = j_start; j < j_end; j++){
            int center =  i*c+j;
            int top    = (i-1)*c+j;
            int bottom = (i+1)*c+j;
            int left   = i*c+j-1;
            int right   = i*c+j+1;
            dst[center] = single_pixel(im,
                                       3*center,
                                       3*top,3*left,3*right,3*bottom,
                                       mask1110,rgb0W,onehalf,minustwelvehalf);
            COST_INC_LOAD(1);
            COST_INC_STORE(1);
        }
    }

}