fcomplex
cexpf(fcomplex z) {
	fcomplex	ans;
	float		x, y, c, s;
	double		t;
	int		n, ix, iy, hx, hy;

	x = F_RE(z);
	y = F_IM(z);
	hx = THE_WORD(x);
	hy = THE_WORD(y);
	ix = hx & 0x7fffffff;
	iy = hy & 0x7fffffff;
	if (iy == 0) {		/* y = 0 */
		F_RE(ans) = expf(x);
		F_IM(ans) = y;
	} else if (ix == 0x7f800000) {	/* x is +-inf */
		if (hx < 0) {
			if (iy >= 0x7f800000) {
				F_RE(ans) = zero;
				F_IM(ans) = zero;
			} else {
				sincosf(y, &s, &c);
				F_RE(ans) = zero * c;
				F_IM(ans) = zero * s;
			}
		} else {
			if (iy >= 0x7f800000) {
				F_RE(ans) = x;
				F_IM(ans) = y - y;
			} else {
				sincosf(y, &s, &c);
				F_RE(ans) = x * c;
				F_IM(ans) = x * s;
			}
		}
	} else {
		sincosf(y, &s, &c);
		if (ix >= 0x42B171AA) {	/* |x| > 88.722... ~ log(2**128) */
#if defined(__i386) && !defined(__amd64)
			int	rp = __swapRP(fp_extended);
#endif
			t = __k_cexp(x, &n);
			F_RE(ans) = (float)scalbn(t * (double)c, n);
			F_IM(ans) = (float)scalbn(t * (double)s, n);
#if defined(__i386) && !defined(__amd64)
			if (rp != fp_extended)
				(void) __swapRP(rp);
#endif
		} else {
			t = expf(x);
			F_RE(ans) = t * c;
			F_IM(ans) = t * s;
		}
	}
	return (ans);
}