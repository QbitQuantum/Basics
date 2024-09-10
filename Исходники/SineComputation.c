/*
Copied from FDLIBM:

FDLIBM (Freely Distributable LIBM) is a C math library
for machines that support IEEE 754 floating-point arithmetic.
In this release, only double precision is supported.

FDLIBM is intended to provide a reasonably portable (see
assumptions below), reference quality (below one ulp for
major functions like sin,cos,exp,log) math library
(libm.a).  For a copy of FDLIBM, please see
	http://www.netlib.org/fdlibm/
or
	http://www.validlab.com/software/
*/
int __kernel_rem_pio2(double *x, double *y, int e0, int nx, int prec,
		const int *ipio2) {
	int jz, jx, jv, jp, jk, carry, n, iq[20], i, j, k, m, q0, ih;
	double z, fw, f[20], fq[20], q[20];

	/* initialize jk*/
	jk = init_jk[prec];
	jp = jk;

	/* determine jx,jv,q0, note that 3>q0 */
	jx = nx - 1;
	jv = (e0 - 3) / 24;
	if (jv < 0)
		jv = 0;
	q0 = e0 - 24 * (jv + 1);

	/* set up f[0] to f[jx+jk] where f[jx+jk] = ipio2[jv+jk] */
	j = jv - jx;
	m = jx + jk;
	for (i = 0; i <= m; i++, j++)
		f[i] = (j < 0) ? zero : (double) ipio2[j];

	/* compute q[0],q[1],...q[jk] */
	for (i = 0; i <= jk; i++) {
		for (j = 0, fw = 0.0; j <= jx; j++)
			fw += x[j] * f[jx + i - j];
		q[i] = fw;
	}

	jz = jk;
	recompute:
	/* distill q[] into iq[] reversingly */
	for (i = 0, j = jz, z = q[jz]; j > 0; i++, j--) {
		fw = (double) ((int) (twon24 * z));
		iq[i] = (int) (z - two24 * fw);
		z = q[j - 1] + fw;
	}

	/* compute n */
	z = scalbn(z, q0); /* actual value of z */
	z -= 8.0 * floor(z * 0.125); /* trim off integer >= 8 */
	n = (int) z;
	z -= (double) n;
	ih = 0;
	if (q0 > 0) { /* need iq[jz-1] to determine n */
		i = (iq[jz - 1] >> (24 - q0));
		n += i;
		iq[jz - 1] -= i << (24 - q0);
		ih = iq[jz - 1] >> (23 - q0);
	} else if (q0 == 0)