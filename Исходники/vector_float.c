SPAN_DECLARE(void) vec_negatef(float z[], const float x[], int n)
{
    int i;
	static const uint32_t mask = 0x80000000;
	static const float *fmask = (float *) &mask;
    __m128 n1;
    __m128 n2;
 
    if ((i = n & ~3))
    {
        n2 = _mm_set1_ps(*fmask);
        for (i -= 4;  i >= 0;  i -= 4)
        {
            n1 = _mm_loadu_ps(x + i);
		    n1 = _mm_xor_ps(n1, n2);
            _mm_storeu_ps(z + i, n1);
        }
    }
    /* Now deal with the last 1 to 3 elements, which don't fill an SSE2 register */
    switch (n & 3)
    {
    case 3:
        z[n - 3] = -x[n - 3];
    case 2:
        z[n - 2] = -x[n - 2];
    case 1:
        z[n - 1] = -x[n - 1];
    }
}