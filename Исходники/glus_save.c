static GLUSvoid convertRGB(GLUSubyte* rgbe, const GLUSfloat* rgb)
{
	GLUSfloat significant[3];
	GLUSint exponent[3];
	GLUSint maxExponent;

	significant[0] = frexpf(rgb[0], &exponent[0]);
	significant[1] = frexpf(rgb[1], &exponent[1]);
	significant[2] = frexpf(rgb[2], &exponent[2]);

	maxExponent = exponent[0];
	if (exponent[1] > maxExponent)
	{
		maxExponent = exponent[1];
	}
	if (exponent[2] > maxExponent)
	{
		maxExponent = exponent[2];
	}

	rgbe[0] = (GLUSubyte)(significant[0] * 256.0f * powf(2.0f, (GLUSfloat)(exponent[0] - maxExponent)));
	rgbe[1] = (GLUSubyte)(significant[1] * 256.0f * powf(2.0f, (GLUSfloat)(exponent[1] - maxExponent)));
	rgbe[2] = (GLUSubyte)(significant[2] * 256.0f * powf(2.0f, (GLUSfloat)(exponent[2] - maxExponent)));
	rgbe[3] = (GLUSubyte)(maxExponent + 128);
}