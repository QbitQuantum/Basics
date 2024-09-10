float sumSSE(float* floats, int size) {

    int i,q,r;
    float f[4] = {0};

    //if(size<10) { float ax; while(size) { ax+=floats[size]; --size; } return ax; }

    q = 4*(size/4); // whole
    r = size - q; // remainder

    // load and sum first 8
    __m128 x = _mm_load_ps( floats);
    __m128 y = _mm_load_ps( floats + 4);
    x = _mm_add_ps(x,y);

    // sum remaining whole blocks one at a time (use j which is size-r...)
    for(i=8; i<q; i+=4) {
        y = _mm_load_ps(floats + i );
        x = _mm_add_ps(x,y);
    }

    //printf("size:%d q:%d r: %d\n",size,q,r);
    // if we have a remainder add it to our sum
    for(; r; --r) f[r] = floats[size-r];
    y = _mm_loadu_ps(f);
    x = _mm_add_ps(x,y);

    // move back into float array, and return the sum
    _mm_store_ps(f,x);
    return f[0] + f[1] + f[2] + f[3];
}