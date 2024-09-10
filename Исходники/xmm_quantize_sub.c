void
fht_SSE2(FLOAT * fz, int n)
{
    const FLOAT *tri = costab;
    int     k4;
    FLOAT  *fi, *gi;
    FLOAT const *fn;

    n <<= 1;            /* to get BLKSIZE, because of 3DNow! ASM routine */
    fn = fz + n;
    k4 = 4;
    do {
        FLOAT   s1, c1;
        int     i, k1, k2, k3, kx;
        kx = k4 >> 1;
        k1 = k4;
        k2 = k4 << 1;
        k3 = k2 + k1;
        k4 = k2 << 1;
        fi = fz;
        gi = fi + kx;
        do {
            FLOAT   f0, f1, f2, f3;
            f1 = fi[0] - fi[k1];
            f0 = fi[0] + fi[k1];
            f3 = fi[k2] - fi[k3];
            f2 = fi[k2] + fi[k3];
            fi[k2] = f0 - f2;
            fi[0] = f0 + f2;
            fi[k3] = f1 - f3;
            fi[k1] = f1 + f3;
            f1 = gi[0] - gi[k1];
            f0 = gi[0] + gi[k1];
            f3 = SQRT2 * gi[k3];
            f2 = SQRT2 * gi[k2];
            gi[k2] = f0 - f2;
            gi[0] = f0 + f2;
            gi[k3] = f1 - f3;
            gi[k1] = f1 + f3;
            gi += k4;
            fi += k4;
        } while (fi < fn);
        c1 = tri[0];
        s1 = tri[1];
        for (i = 1; i < kx; i++) {
            __m128 v_s2;
            __m128 v_c2;
            __m128 v_c1;
            __m128 v_s1;
            FLOAT   c2, s2, s1_2 = s1+s1;
            c2 = 1 - s1_2 * s1;
            s2 = s1_2 * c1;
            fi = fz + i;
            gi = fz + k1 - i;
            v_c1 = _mm_set_ps1(c1);
            v_s1 = _mm_set_ps1(s1);
            v_c2 = _mm_set_ps1(c2);
            v_s2 = _mm_set_ps1(s2);
            {
                static const vecfloat_union sign_mask = {{0x80000000,0,0,0}};
                v_c1 = _mm_xor_ps(sign_mask._m128, v_c1); /* v_c1 := {-c1, +c1, +c1, +c1} */
            }
            {
                static const vecfloat_union sign_mask = {{0,0x80000000,0,0}};
                v_s1 = _mm_xor_ps(sign_mask._m128, v_s1); /* v_s1 := {+s1, -s1, +s1, +s1} */
            }
            {
                static const vecfloat_union sign_mask = {{0,0,0x80000000,0x80000000}};
                v_c2 = _mm_xor_ps(sign_mask._m128, v_c2); /* v_c2 := {+c2, +c2, -c2, -c2} */
            }
            do {
                __m128 p, q, r;

                q = _mm_setr_ps(fi[k1], fi[k3], gi[k1], gi[k3]); /* Q := {fi_k1,fi_k3,gi_k1,gi_k3}*/
                p = _mm_mul_ps(_mm_set_ps1(s2), q);              /* P := s2 * Q */
                q = _mm_mul_ps(v_c2, q);                         /* Q := c2 * Q */
                q = _mm_shuffle_ps(q, q, _MM_SHUFFLE(1,0,3,2));  /* Q := {-c2*gi_k1,-c2*gi_k3,c2*fi_k1,c2*fi_k3} */
                p = _mm_add_ps(p, q);
                
                r = _mm_setr_ps(gi[0], gi[k2], fi[0], fi[k2]);   /* R := {gi_0,gi_k2,fi_0,fi_k2} */
                q = _mm_sub_ps(r, p);                            /* Q := {gi_0-p0,gi_k2-p1,fi_0-p2,fi_k2-p3} */
                r = _mm_add_ps(r, p);                            /* R := {gi_0+p0,gi_k2+p1,fi_0+p2,fi_k2+p3} */
                p = _mm_shuffle_ps(q, r, _MM_SHUFFLE(2,0,2,0));  /* P := {q0,q2,r0,r2} */
                p = _mm_shuffle_ps(p, p, _MM_SHUFFLE(3,1,2,0));  /* P := {q0,r0,q2,r2} */
                q = _mm_shuffle_ps(q, r, _MM_SHUFFLE(3,1,3,1));  /* Q := {q1,q3,r1,r3} */
                r = _mm_mul_ps(v_c1, q);
                q = _mm_mul_ps(v_s1, q);
                q = _mm_shuffle_ps(q, q, _MM_SHUFFLE(0,1,2,3));  /* Q := {q3,q2,q1,q0} */
                q = _mm_add_ps(q, r);

                store4(_mm_sub_ps(p, q), &gi[k3], &gi[k2], &fi[k3], &fi[k2]);
                store4(_mm_add_ps(p, q), &gi[k1], &gi[ 0], &fi[k1], &fi[ 0]);

                gi += k4;
                fi += k4;
            } while (fi < fn);
            c2 = c1;
            c1 = c2 * tri[0] - s1 * tri[1];
            s1 = c2 * tri[1] + s1 * tri[0];
        }
        tri += 2;
    } while (k4 < n);
}