static void *
add_sse2_unroll(void *ptr)
{
    size_t n;
    char *p1, *p2, *p3;
    struct narray3 *a = (struct narray3*)ptr;
    dtype x, y;
    size_t i, n4;
    ssize_t s1, s2, s3;
    __m128d d1, d2, d3;
    __m128d e1, e2, e3;
    char *q1, *q2, *q3;

    p1 = a->x->ptr;
    p2 = a->y->ptr;
    p3 = a->z->ptr;
    n =  a->x->size;

    s1 = s2 = s3 = sizeof(dtype);

    q1 = p1 + s1*2;
    q2 = p2 + s2*2;
    q3 = p3 + s3*2;

    s1 = s2 = s3 = sizeof(dtype)*4;

    n4 = 3;
    n4 = (n & ~n4) - 2;
        e1 = _mm_load_pd((dtype*)q1);
        q1+=s1;
        e2 = _mm_load_pd((dtype*)q2);
        q2+=s2;
        e3 = _mm_add_pd(e1,e2);
    for (i=2; i<n4; i+=4) {
        d1 = _mm_load_pd((dtype*)p1);
        p1+=s1;
        d2 = _mm_load_pd((dtype*)p2);
        p2+=s2;
        d3 = _mm_add_pd(d1,d2);
        _mm_store_pd((dtype*)q3,e3);
        q3+=s3;
        e1 = _mm_load_pd((dtype*)q1);
        q1+=s1;
        e2 = _mm_load_pd((dtype*)q2);
        q2+=s2;
        e3 = _mm_add_pd(e1,e2);
        _mm_store_pd((dtype*)p3,d3);
        p3+=s3;
    }
    _mm_store_pd((dtype*)q3,e3);

    for (; i<n; i++) {
        x = *(dtype*)p1; p1+=s1;
        y = *(dtype*)p2; p2+=s2;
        x = x+y;
        *(dtype*)p3 = x; p3+=s3;
    }
    return 0;
}