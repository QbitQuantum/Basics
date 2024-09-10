int
drid_moments(float* coords, int32_t index, int32_t* partners, int32_t n_partners, double* moments)
{
    int32_t i;
    float d;
    moments_t onlinemoments;
    __m128 x, y, r, r2, s;

    moments_clear(&onlinemoments);
    x = load_float3(&coords[3 * index]);

    for (i = 0; i < n_partners; i++) {
        y = load_float3(&coords[3 * partners[i]]);
        r = _mm_sub_ps(x, y);     /* x - y       */
        r2 = _mm_mul_ps(r, r);    /* (x - y)**2  */

        /* horizontal add the components of d2 with */
        /* two instructions. note: it's critical */
        /* here that the last entry of x1 and x2 was 0 */
        /* so that d2.w = 0 */
	s = _mm_add_ps(r2, _mm_movehl_ps(r2, r2));
        s = _mm_add_ss(s, _mm_shuffle_ps(s, s, 1));
        /* store into a regular float. I tried using _mm_rsqrt_ps, but it's not
           accurate to pass the tests */
        _mm_store_ss(&d, s);
        moments_push(&onlinemoments, 1.0 / sqrt((double) d));
    }

    moments[0] = moments_mean(&onlinemoments);
    moments[1] = sqrt(moments_second(&onlinemoments));
    moments[2] = cbrt(moments_third(&onlinemoments));

    return 1;
}