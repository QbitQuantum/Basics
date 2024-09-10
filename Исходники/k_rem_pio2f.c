int __kernel_rem_pio2f(float *x, float *y, int e0, int nx, int prec,
		const s32_t *ipio2)
{
	s32_t jz, jx, jv, jp, jk, carry, n, iq[20], i, j, k, m, q0, ih;
	float z, fw, f[20], fq[20], q[20];

	jk = init_jk[prec];
	jp = jk;

	jx = nx - 1;
	jv = (e0 - 3) / 8;
	if (jv < 0)
		jv = 0;
	q0 = e0 - 8 * (jv + 1);

	j = jv - jx;
	m = jx + jk;
	for (i = 0; i <= m; i++, j++)
		f[i] = (j < 0) ? zero : (float) ipio2[j];

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
		fw = (float) ((s32_t)(twon8 * z));
		iq[i] = (s32_t)(z - two8 * fw);
		z = q[j - 1] + fw;
	}

	z = scalbnf(z, q0);
	z -= (float) 8.0 * floorf(z * (float) 0.125);
	n = (s32_t) z;
	z -= (float) n;
	ih = 0;
	if (q0 > 0)
	{
		i = (iq[jz - 1] >> (8 - q0));
		n += i;
		iq[jz - 1] -= i << (8 - q0);
		ih = iq[jz - 1] >> (7 - q0);
	}