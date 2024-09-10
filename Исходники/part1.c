void warmup_vector(float* x, float* y, int size, float* alpha){
    int i;
    __m128 RX_2, RX_2i, RY, R_t1, R_t2, R_alpha;
    int x_2;
    int x_2i;
    R_alpha = _mm_load_ps(&alpha[0]);
    for(i=0; i<size; i+=4){
        //load our various x values
        RX_2 = _mm_load_ps(&x[i*2]);   
        RX_2i = _mm_load_ps(&x[2*i+1]);
        //perform x[2*i+1]/alpha -> store in R_t1
        R_t1 = _mm_div_ps(RX_2i, R_alpha);
        //multiply x[2*i] by x[2*i] -> store in R_t2
        R_t2= _mm_mul_ps(RX_2, RX_2);
        //add all our variables together; this will be stored as our new y[i] values (in RY)
        //issue resulting in seg fault seems to reside in below code.... not sure what's going on
        //tried increasing the size of things in our array to see if we were getting some negative values
        //something able to set to handle negatives?
        //  RY = _mm_add_ps(R_t1, R_t2);
        RY = _mm_add_ps(R_t1, R_t2);
        // copy everything to y[i]
        _mm_store_ps(&y[i], RY);     
    }

}