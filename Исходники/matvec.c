static void
matvec_sse()
{
        /* Assume that the data size is an even multiple of the 128 bit
         * SSE vectors (i.e. 4 floats) */
        assert(!(SIZE & 0x3));

        /* TASK: Implement your SSE version of the matrix-vector
         * multiplication here.
         */
        /* HINT: You might find at least the following instructions
         * useful:
         *  - _mm_setzero_ps
         *  - _mm_load_ps
         *  - _mm_hadd_ps
         *  - _mm_cvtss_f32
         *
         * HINT: You can create the sum of all elements in a vector
         * using two hadd instructions.
         */

        __m128 dummy=_mm_setzero_ps();
        for(int i=0;i<SIZE;++i){
            __m128 temp=_mm_setzero_ps();
            for(int j=0;j<SIZE;j+=4){

                __m128 mm_vec_b=_mm_load_ps((__m128*)(vec_b+j));
                __m128 mm_matr=_mm_load_ps((__m128*)(mat_a+MINDEX(i,j)));
                __m128 out=_mm_mul_ps(mm_vec_b,mm_matr);
                temp=_mm_add_ps(temp,out);

//                vec_c[i]+=_mm_cvtss_f32(_mm_dp_ps(mm_matr,mm_vec_b,0xf1));
            }
            __m128 res=_mm_hadd_ps(_mm_hadd_ps(temp,dummy),dummy);
            vec_c[i]=_mm_cvtss_f32(res);
        }

}