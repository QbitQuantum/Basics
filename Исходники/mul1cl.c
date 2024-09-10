GF2X_STORAGE_CLASS_mul1 void
gf2x_mul1 (unsigned long *c, unsigned long a, unsigned long b)
{
    __v2di aa = (__v2di) { a, 0 };
    __v2di bb = (__v2di) { b, 0 };
    _mm_storeu_si128((__v2di*)c, _mm_clmulepi64_si128(aa, bb, 0));
}