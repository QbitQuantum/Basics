_MRTIMP2_NCEEPURE short __CLRCALL_PURE_OR_CDECL _Exp(double *px, double y, short eoff)
	{	/* compute y*e^(*px), (*px) finite, |y| not huge */
	if (*px < -hugexp || y == 0.0)
		{	/* certain underflow */
		*px = 0.0;
		return (0);
		}
	else if (hugexp < *px)
		{	/* certain overflow */
		*px = _Inf._Double;
		return (_INFCODE);
		}
	else
		{	/* xexp won't overflow */
		double g = *px * invln2;
		short xexp = (short)(g + (g < 0.0 ? - 0.5 : + 0.5));

		g = xexp;
		g = (*px - g * c1) - g * c2;
		if (-_Eps._Double < g && g < _Eps._Double)
			*px = y;
		else
			{	/* g*g worth computing */
			const double z = g * g;
			const double w = (q[0] * z + q[1]) * z + q[2];

			g *= (z + p[1]) * z + p[2];
			*px = (w + g) / (w - g) * 2.0 * y;
			--xexp;
			}
		return (_Dscale(px, (long)xexp + eoff));
		}
	}