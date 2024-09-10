_MRTIMP2_NCEEPURE short __CLRCALL_PURE_OR_CDECL _FExp(float *px, float y, short eoff)
	{	/* compute y*e^(*px), (*px) finite, |y| not huge */
	if (*px < -hugexp || y == 0.0F)
		{	/* certain underflow */
		*px = 0.0F;
		return (0);
		}
	else if (hugexp < *px)
		{	/* certain overflow */
		*px = _FInf._Float;
		return (_INFCODE);
		}
	else
		{	/* xexp won't overflow */
		float g = *px * invln2;
		short xexp = (short)(g + (g < 0.0F ? - 0.5F : + 0.5F));

		g = xexp;
		g = (float)((*px - g * c1) - g * c2);
		if (-_FEps._Float < g && g < _FEps._Float)
			*px = y;
		else
			{	/* g*g worth computing */
			const float z = g * g;
			const float w = q[0] * z + q[1];

			g *= z + p[1];
			*px = (w + g) / (w - g) * 2.0F * y;
			--xexp;
			}
		return (_FDscale(px, (long)xexp + eoff));
		}
	}