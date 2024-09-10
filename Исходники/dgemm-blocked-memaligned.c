// this function assumes data is stored in col-major
// if data is in row major, call it like matmul4x4(B, A, C)
void matmul4x4(double *A, double *B, double *C) {
    __m256d col[4], sum[4];
    //load every column into registers
    for(int i=0; i<4; i++)  
      col[i] = _mm256_load_pd(&A[i*4]);
    for(int i=0; i<4; i++) {
        sum[i] = _mm256_setzero_pd();      
        for(int j=0; j<4; j++) {
            sum[i] = _mm256_add_pd(_mm256_mul_pd(_mm256_set1_pd(B[i*4+j]), col[j]), sum[i]);
        }           
    }
    for(int i=0; i<4; i++) 
      _mm256_store_pd(&C[i*4], sum[i]); 
}