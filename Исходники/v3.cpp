double angle(const V3 & u, const V3 & v) 
{
	double dot = u * v;
	double nu = u.normL2();
	double nv = v.normL2();
	return remainder(acos(dot/(nu*nv)),2*M_PI);
}