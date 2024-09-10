inline float Recognizer::local_distance(float *v1, float *v2) {
    float sum = 0;
#ifdef __SSE__
    wg_v4sf res, v_;
    v_.v = _mm_set_ps1(-0.0);
    
    res.v = _mm_sub_ps(((wg_v4sf *)v2)->v, ((wg_v4sf *)v1)->v);
    res.v = _mm_andnot_ps(v_.v,res.v); // absolute value

    for (unsigned int i=0; i < dimension; i++)
        sum += res.s[i];
#else
    for (unsigned int i=0; i < dimension; i++) 
        sum += fabs(v2[i] - v1[i]);
#endif
    return sum;
}