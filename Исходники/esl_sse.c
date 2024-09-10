/* Function:  esl_sse_expf()
 * Synopsis:  <r[z] = exp x[z]>
 * Incept:    SRE, Fri Dec 14 14:46:27 2007 [Janelia]
 *
 * Purpose:   Given a vector <x> containing four floats, returns a
 *            vector <r> in which each element <r[z] = expf(x[z])>.
 *
 *            Valid for all IEEE754 floats $x_z$.
 *
 * Xref:      J2/71
 *            J10/62: bugfix, minlogf/maxlogf range was too wide;
 *                    (k+127) must be >=0 and <=255, so (k+127)<<23
 *                    is a valid IEEE754 float, without touching
 *                    the sign bit. Pommier had this right in the
 *                    first place, and I didn't understand.
 *
 * Note:      Derived from an SSE1 implementation by Julian
 *            Pommier. Converted to SSE2.
 *
 *            Note on maxlogf/minlogf, which are close to but not
 *            exactly 127.5/log2 [J10/63]. We need -127<=k<=128, so
 *            k+127 is 0..255, a valid IEEE754 8-bit exponent
 *            (0..255), so the bit pattern (k+127)<<23 is IEEE754
 *            single-precision for 2^k.  If k=-127, we get IEEE754 0.
 *            If k=128, we get IEEE754 +inf.  If k<-127, k+127 is
 *            negative and we get screwed up.  If k>128, k+127
 *            overflows the 8-bit exponent and sets the sign bit.  So
 *            for x' (base 2) < -127.5 we must definitely return e^x ~
 *            0; for x' < 126.5 we're going to calculate 0 anyway
 *            (because k=floor(-126.5-epsilon+0.5) = -127).  So any
 *            minlogf between -126.5 log2 ... -127.5 log2 will suffice
 *            as the cutoff. Ditto for 126.5 log2 .. 127.5log2.
 *            That's 87.68312 .. 88.3762655.  I think Pommier's
 *            thinking is, you don't want to get to close to the
 *            edges, lest fp roundoff error screw you (he may have
 *            consider 1 ulp carefully, I can't tell), but otherwise
 *            you may as well put your bounds close to the outer edge;
 *            so
 *              maxlogf =  127.5 log(2) - epsilon
 *              minlogf = -127.5 log(2) + epsilon
 *            for an epsilon that happen to be ~ 3e-6.
 */
__m128
esl_sse_expf(__m128 x)
{
    static float cephes_p[6] = { 1.9875691500E-4f, 1.3981999507E-3f, 8.3334519073E-3f,
                                 4.1665795894E-2f, 1.6666665459E-1f, 5.0000001201E-1f
                               };
    static float cephes_c[2] = { 0.693359375f,    -2.12194440e-4f };
    static float maxlogf     =  88.3762626647949f;  /* 127.5 log(2) - epsilon. above this, 0.5+x/log2 gives k>128 and breaks 2^k "float" construction, because (k+127)<<23 must be a valid IEEE754 exponent 0..255 */
    static float minlogf     = -88.3762626647949f;  /*-127.5 log(2) + epsilon. below this, 0.5+x/log2 gives k<-127 and breaks 2^k, see above */
    __m128i k;
    __m128  mask, tmp, fx, z, y, minmask, maxmask;

    /* handle out-of-range and special conditions */
    maxmask = _mm_cmpgt_ps(x, _mm_set1_ps(maxlogf));
    minmask = _mm_cmple_ps(x, _mm_set1_ps(minlogf));

    /* range reduction: exp(x) = 2^k e^f = exp(f + k log 2); k = floorf(0.5 + x / log2): */
    fx = _mm_mul_ps(x,  _mm_set1_ps(eslCONST_LOG2R));
    fx = _mm_add_ps(fx, _mm_set1_ps(0.5f));

    /* floorf() with SSE:  */
    k    = _mm_cvttps_epi32(fx);	              /* cast to int with truncation                  */
    tmp  = _mm_cvtepi32_ps(k);	              /* cast back to float                           */
    mask = _mm_cmpgt_ps(tmp, fx);               /* if it increased (i.e. if it was negative...) */
    mask = _mm_and_ps(mask, _mm_set1_ps(1.0f)); /* ...without a conditional branch...           */
    fx   = _mm_sub_ps(tmp, mask);	              /* then subtract one.                           */
    k    = _mm_cvttps_epi32(fx);	              /* k is now ready for the 2^k part.             */

    /* polynomial approx for e^f for f in range [-0.5, 0.5] */
    tmp = _mm_mul_ps(fx, _mm_set1_ps(cephes_c[0]));
    z   = _mm_mul_ps(fx, _mm_set1_ps(cephes_c[1]));
    x   = _mm_sub_ps(x, tmp);
    x   = _mm_sub_ps(x, z);
    z   = _mm_mul_ps(x, x);

    y =               _mm_set1_ps(cephes_p[0]);
    y = _mm_mul_ps(y, x);
    y = _mm_add_ps(y, _mm_set1_ps(cephes_p[1]));
    y = _mm_mul_ps(y, x);
    y = _mm_add_ps(y, _mm_set1_ps(cephes_p[2]));
    y = _mm_mul_ps(y, x);
    y = _mm_add_ps(y, _mm_set1_ps(cephes_p[3]));
    y = _mm_mul_ps(y, x);
    y = _mm_add_ps(y, _mm_set1_ps(cephes_p[4]));
    y = _mm_mul_ps(y, x);
    y = _mm_add_ps(y, _mm_set1_ps(cephes_p[5]));
    y = _mm_mul_ps(y, z);
    y = _mm_add_ps(y, x);
    y = _mm_add_ps(y, _mm_set1_ps(1.0f));

    /* build 2^k by hand, by creating a IEEE754 float */
    k  = _mm_add_epi32(k, _mm_set1_epi32(127));
    k  = _mm_slli_epi32(k, 23);
    fx = _mm_castsi128_ps(k);

    /* put 2^k e^f together (fx = 2^k,  y = e^f) and we're done */
    y = _mm_mul_ps(y, fx);

    /* special/range cleanup */
    y = esl_sse_select_ps(y, _mm_set1_ps(eslINFINITY), maxmask); /* exp(x) = inf for x > log(2^128)  */
    y = esl_sse_select_ps(y, _mm_set1_ps(0.0f),        minmask); /* exp(x) = 0   for x < log(2^-149) */
    return y;
}