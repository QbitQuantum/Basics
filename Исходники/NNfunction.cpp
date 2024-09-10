double CNNfunction::IntegralTri(double from, double to, double a, double b)
{
	double sgn = 1.0;
	double v = 0.0;
	if (from > to) {double tmp = from; from=to; to=tmp; sgn = -1.0;}
	if (from < 0.0) from = 0;
	if (to > 1.0) to = 1.0;
//	if (a < 0) a = -a;
	if (b < 0) b = -b;

	double S1 =	0.5 *b;
	if (to < a - b)	 return 0.0;
	if (from > a + b)	 return 0.0;
	if (from < a - b) {
		if (to < a) v = ((to-a+b)*(1.0+(to-a)/b)*0.5);
		else if (to < a + b) v = (S1 + 0.5*(to-a)*(2.0-(to-a)/b));
		else v = b;
	} else if (from < a) {
		if (to < a) v = (0.5*(to-from)*(2.0+(to+from-2.0*a)/b));
		else if (to < a + b) v = (0.5*(a-from)*(2.0+(from-a)/b) 
									+ 0.5*(to-a)*(2.0-(to-a)/b));
		else v = (0.5*(a-from)*(2.0+(from-a)/b) + S1); 
	} else if (from < a + b) {
		if (to < a + b) v = (0.5*(to-from)*(2.0-(to+from-2.0*a)/b));
		else v = (0.5*(a+b-from)*(2.0-(b+from-a)/b));
	} else v = 0.0;

	return _copysign(v, sgn);
}