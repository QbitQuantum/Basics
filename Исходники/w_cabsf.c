//asq: transformed to "new"-style declaration
float
cabsf(float complex z)
//	float complex z;
{

	return hypotf(crealf(z), cimagf(z));
}