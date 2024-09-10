_MRTIMP2_NCEEPURE short __CLRCALL_PURE_OR_CDECL _LExp(long double *px, long double y, short eoff)
	{	/* compute y*e^(*px), (*px) finite, |y| not huge */
	if (*px < -hugexp || y == 0.0L)
		{	/* certain underflow */
		*px = 0.0L;
		return (0);
		}
	else if (hugexp < *px)
		{	/* certain overflow */
		*px = _LInf._Long_double;
		return (_INFCODE);
		}
	else
		{	/* xexp won't overflow */
		long double g = *px * invln2;
		short xexp = (short)(g + (g < 0 ? - 0.5L : + 0.5L));

		g = xexp;
		g = (*px - g * c1) - g * c2;
		if (-_LEps._Long_double < g && g < _LEps._Long_double)
			*px = y;
		else
			{	/* g*g worth computing */

 #if _DLONG <= 1	/* assume IEEE 754 10 byte */
			const long double z = g * g;
			const long double w = ((z + q[1]) * z + q[2]) * z + q[3];

			g *= (p[0] * z + p[1]) * z + p[2];
			*px = (w + g) / (w - g) * 2.0L * y;
			--xexp;

 #else	/* assume IEEE 754 16 byte */
			const long double z = g * g;
			const long double w = ((q[0] * z + q[1]) * z + q[2]) * z + q[3];
			const long double v = (((p[0] * z + p[1]) * z + p[2])
				* z + p[3]) * z + p[4];
			const long double u = g * w - v;

			*px = g * (g + z * (w + w + u)) / (2.0L - (g + z * u)) + g + 1.0;
			*px *= y;
 #endif

			}
		return (_LDscale(px, (long)xexp + eoff));
		}
	}