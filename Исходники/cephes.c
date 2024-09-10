double
cephes_normal(double x)
{
	double arg, result, sqrt2=1.414213562373095048801688724209698078569672;

	if (x > 0) {
		arg = x/sqrt2;
		result = 0.5 * ( 1 + erf(arg) );
	}
	else {
		arg = -x/sqrt2;
		result = 0.5 * ( 1 - erf(arg) );
	}

	return( result);
}