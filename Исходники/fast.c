void gemm(complex float* A,
        complex float* B,
        complex float* C,
        int m,
        int n,
        int k,
        complex float alpha,
        complex float beta){

    __m128  c_reg, 
            a_reg,
            b_reg,
            alpha_reg,
            beta_reg,
            t,
            t2,
            t3;

    complex float *beta_reg_value = malloc(sizeof(complex float)*2);
    beta_reg_value[0] = beta;
    beta_reg_value[1] = beta;
    beta_reg = _mm_loadu_ps((float*)beta_reg_value);
    
    complex float *alpha_reg_value = malloc(sizeof(complex float)*2);
    alpha_reg_value[0] = alpha;
    alpha_reg_value[1] = alpha;
    alpha_reg = _mm_loadu_ps((float*)alpha_reg_value);
    

    complex float *a_value = malloc(sizeof(complex float)*2);



    for(int x = 0; x < n; x += 2){
        for(int y = 0; y < m; y++){
            t3 = _mm_setzero_ps();
            for(int z = 0; z < k; z++){
                // A[y*k+z]*B[z*n + x]
                a_value[0] = A[y*k + z];
                a_value[1] = *a_value;

                a_reg = _mm_loadu_ps((float*)a_value);
                b_reg = _mm_loadu_ps((float*)&B[z*n + x]);
                
                t = _mm_moveldup_ps(a_reg);
                t2 = t * b_reg;
                b_reg = _mm_shuffle_ps(b_reg, b_reg, 0xb1);
                t = _mm_movehdup_ps(a_reg);
                t = t * b_reg;
                a_reg = _mm_addsub_ps(t2, t);


                t3 = t3 + a_reg;
                
            }
            c_reg = _mm_loadu_ps((float*)&C[y*n + x]);
            t = _mm_moveldup_ps(c_reg);
            t2 = t * beta_reg;
            beta_reg = _mm_shuffle_ps(beta_reg, beta_reg, 0xb1);
            t = _mm_movehdup_ps(c_reg);
            t = t * beta_reg;
            c_reg = _mm_addsub_ps(t2, t);
            beta_reg = _mm_shuffle_ps(beta_reg, beta_reg, 0xb1);

            t = _mm_moveldup_ps(t3);
            t2 = t * alpha_reg;
            alpha_reg = _mm_shuffle_ps(alpha_reg, alpha_reg, 0xb1);
            t = _mm_movehdup_ps(t3);
            t = t * alpha_reg;
            b_reg = _mm_addsub_ps(t2, t);
            alpha_reg = _mm_shuffle_ps(alpha_reg, alpha_reg, 0xb1);
            
            c_reg = b_reg + c_reg;
            _mm_storeu_ps((float*)&C[y*n + x], c_reg);
        }
    }
    free(beta_reg_value);
    free(alpha_reg_value);
    free(a_value);
}