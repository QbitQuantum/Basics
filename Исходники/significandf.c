float significandf(float x)
{
	return scalbnf(x, -ilogbf(x));
}