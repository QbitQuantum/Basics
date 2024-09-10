double
y0(double arg)
{
	double argsq, n, d;
	int i;

	errno = 0;
	if(arg <= 0) {
		errno = EDOM;
		return(-HUGE_VAL);
	}
	if(arg > 8) {
		asympt(arg);
		n = arg - pio4;
		return sqrt(tpi/arg)*(pzero*sin(n) + qzero*cos(n));
	}
	argsq = arg*arg;
	for(n=0,d=0,i=8;i>=0;i--) {
		n = n*argsq + p4[i];
		d = d*argsq + q4[i];
	}
	return n/d + tpi*j0(arg)*log(arg);
}