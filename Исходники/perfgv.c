void gvrotg_fma(double *c, double *s, double *r, double a, double b)
{
#if defined(__FMA__)
    register __m256d x0, x1, t0, t2, u0, u1, one, b0, b1;
    if (b == 0.0) {
        *c = 1.0;
        *s = 0.0;
        *r = a;
        return;
    }
    if (a == 0.0) {
        *c = 0.0;
        *s = 1.0;
        *r = b;
        return;
    }

    // set_pd() order: [3, 2, 1, 0]
    // x[0], x[1]: |a| > |b|,  x[2],x[3]: |b| > |a|

    one = _mm256_set1_pd(1.0);
    x0  = _mm256_set_pd(1.0, a, b, 1.0);   // x0 = {1, a,   b,   1}
    x1  = _mm256_set_pd(1.0, b, a, 1.0);   // x0 = {1, b,   a,   1}
    t0  = _mm256_div_pd(x0, x1);           // t0 = {1, a/b, b/a, 1}
    t2  = _mm256_fmadd_pd(t0, t0, one);    // x3 = {1, 1+(a/b)^2, (b/a)^2+1, 1}
    u0  = _mm256_sqrt_pd(t2);              // u0 = {1, sqrt(1+(a/b)^2), sqrt((b/2)^2+1), 1}
    u1  = _mm256_div_pd(one, u0);
    b0  = _mm256_blend_pd(u0, u1, 0x9);    // b0 = {1/u(a),   u(a),   u(b), 1/u(b)} 
    b0  = _mm256_mul_pd(b0, x1);           // b0 = {1/u(a), b*u(a), a*u(b), 1/u(b)} 
    b1  = _mm256_mul_pd(t0, u1);           // b1 = {1/u(a), t*u(a), t*u(b), 1/u(b)} 

    if (fabs(b) > fabs(a)) {
      *s = b0[3];
      *r = b0[2];
      *c = b1[2];
      if (signbit(b)) {
          *s = -(*s);
          *c = -(*c);
          *r = -(*r);
      }
    } else {
      *c = b0[0];
      *r = b0[1];
      *s = b1[1];
    }
#endif
}