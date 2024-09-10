static void add_block(double* new_A, double*  A, int M, int N, int lda, int M_even) {

    __m128d a; 
    int i_step;
    for (int j=0; j<N; j++) {
        for (int i=0; i<M; i+=I_STRIDE) {
            i_step = min(I_STRIDE,M-i); 
            if (i_step == 1) {
                A[i+j*lda] = new_A[i+j*M_even];
            } 
            else {
                a = _mm_load_pd(new_A + i + j*M_even);
                _mm_storeu_pd(A+i+j*lda,a);
            }
        }
    }
}