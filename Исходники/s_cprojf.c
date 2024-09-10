float complex
cprojf(float complex z)
{
	float complex res;

	if (isinf(__real__ z) || isinf(__imag__ z)) {
		__real__ res = INFINITY;
		__imag__ res = copysignf(0.0, __imag__ z);
	} else {
		res = z;
	}

	return res;
}