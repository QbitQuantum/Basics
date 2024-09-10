void O3QuadraticEquation<TYPE>::GetXIntercepts(double* r1, double* r2, const double x) const {
	double a=GetA(), b=GetB(), c=GetC()-x;
	double sqrt_b2_minus_4ac = sqrt((b*b)-(4*a*c));
	double recip_2a = O3recip(2*a);
	if (r1) *r1 = (-b + sqrt_b2_minus_4ac) * recip_2a;
	if (r2) *r2 = (-b - sqrt_b2_minus_4ac) * recip_2a;
}