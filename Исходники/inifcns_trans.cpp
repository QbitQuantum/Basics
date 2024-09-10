static ex exp_conjugate(const ex & x)
{
	// conjugate(exp(x))==exp(conjugate(x))
	return exp(x.conjugate());
}