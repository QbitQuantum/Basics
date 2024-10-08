_CRTIMP2_PURE float __CLRCALL_PURE_OR_CDECL _FSinh(float x, float y)
	{	/* compute y*sinh(x), |y| <= 1 */
	short neg;

	switch (_FDtest(&x))
		{	/* test for special codes */
	case _NANCODE:
		return (x);
	case _INFCODE:
		return (y != 0.0F ? x : FSIGN(x) ? -y : y);
	case 0:
		return (x * y);
	default:	/* finite */
		if (y == 0.0F)
			return (x < 0.0F ? -y : y);
		if (x < 0.0F)
			x = -x, neg = 1;
		else
			neg = 0;

		if (x < _FRteps._Float)
			x *= y;	/* x tiny */
		else if (x < 1.0F)
			{
			float w = x * x;

			x += ((p[0] * w + p[1]) * w + p[2]) * w * x;
			x *= y;
			}
		else if (x < _FXbig)
			{	/* worth adding in exp(-x) */
			_FExp(&x, 1.0F, -1);
			x = y * (x - 0.25F / x);
			}
		else
			switch (_FExp(&x, y, -1))
				{	/* report over/underflow */
			case 0:
				_Feraise(_FE_UNDERFLOW);
				break;
			case _INFCODE:
				_Feraise(_FE_OVERFLOW);
				}
		return (neg ? -x : x);
		}
	}