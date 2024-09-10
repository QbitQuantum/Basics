long double
cabsl(long double complex z)
{
	return hypotl(__real__ z, __imag__ z);
}