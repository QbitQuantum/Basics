int __kernel_rem_pio2(double *x, double *y, int e0, int nx, int prec,
		const s32_t *ipio2)
{
	s32_t jz, jx, jv, jp, jk, carry, n, iq[20], i, j, k, m, q0, ih;
	double z, fw, f[20], fq[20], q[20];

	jk = init_jk[prec];
	jp = jk;

	jx = nx - 1;
	jv = (e0 - 3) / 24;
	if (jv < 0)
		jv = 0;
	q0 = e0 - 24 * (jv + 1);

	j = jv - jx;
	m = jx + jk;
	for (i = 0; i <= m; i++, j++)
		f[i] = (j < 0) ? zero : (double) ipio2[j];

	for (i = 0; i <= jk; i++)
	{
		for (j = 0, fw = 0.0; j <= jx; j++)
			fw += x[j] * f[jx + i - j];
		q[i] = fw;
	}

	jz = jk;
	recompute:

	for (i = 0, j = jz, z = q[jz]; j > 0; i++, j--)
	{
		fw = (double) ((s32_t)(twon24 * z));
		iq[i] = (s32_t)(z - two24 * fw);
		z = q[j - 1] + fw;
	}

	z = scalbn(z, q0);
	z -= 8.0 * floor(z * 0.125);
	n = (s32_t) z;
	z -= (double) n;
	ih = 0;
	if (q0 > 0)
	{
		i = (iq[jz - 1] >> (24 - q0));
		n += i;
		iq[jz - 1] -= i << (24 - q0);
		ih = iq[jz - 1] >> (23 - q0);
	}