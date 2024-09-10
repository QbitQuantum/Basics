double (tan)(double x)
	{	/* compute tan(x) */
	double g, gd;
	long quad;

	switch (_Dtest(&x))
		{
	case NAN:
		errno = EDOM;
		return (x);
	case INF:
		errno = EDOM;
		return (_Nan._D);
	case 0:
		return (0.0);
	default:	/* finite */
		if (x < -HUGE_RAD || HUGE_RAD < x)
			{	/* x huge, sauve qui peut */
			g = x / twopi;
			_Dint(&g, 0);
			x -= g * twopi;
			}
		g = x * twobypi;
		quad = (long)(0 < g ? g + 0.5 : g - 0.5);
		g = (double)quad;
		g = (x - g * c1) - g * c2;
		gd = 1.0;
		if (_Rteps._D < (g < 0.0 ? -g : g))
			{	/* g*g worth computing */
			double y = g * g;
	
			gd += (((q[0] * y + q[1]) * y + q[2]) * y + q[3]) * y;
			g += ((p[0] * y + p[1]) * y + p[2]) * y * g;
			}
		return ((unsigned int)quad & 0x1 ? -gd / g : g / gd);
		}
	}