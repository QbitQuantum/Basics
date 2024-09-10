double roundTo(double num, int decimals)
{
	double shift = pow(10, decimals);
	return Round(num * shift) / shift;
};