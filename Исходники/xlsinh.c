_CRTIMP2 long double __cdecl _LSinh(long double x, long double y)
	{	/* compute y*sinh(x), |y| <= 1 */
	switch (_LDtest(&x))
		{	/* test for special codes */
	case NAN:
		errno = EDOM;
		return (x);
	case INF:
		if (y == 0)
			return (0);
		errno = ERANGE;
		return (LSIGN(x) ? -_LInf._L : _LInf._L);
	case 0:
		return (0);
	default:	/* finite */
		 {	/* compute sinh(finite) */
		short neg;

		if (x < 0)
			x = -x, neg = 1;
		else
			neg = 0;
		if (x < _LRteps._L)
			x *= y;	/* x tiny */
		else if (x < 1)
			{
			long double w = x * x;

			x += x * w * _LPoly(w, p, NP - 1);
			x *= y;
			}
		else if (x < _LXbig)
			{	/* worth adding in exp(-x) */
			_LExp(&x, 1, -1);
			x = y * (x - 0.25 / x);
			}
		else if (0 <= _LExp(&x, y, -1))
			errno = ERANGE;	/* x large */
		return (neg ? -x : x);
		 }
		}
	}