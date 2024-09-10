double
cabs(double complex z)
{
	return hypot(__real__ z, __imag__ z);
}