void navUkfMatrixExtractEuler(float *m, float *yaw, float *pitch, float *roll)
{
	if (m[1 * 3 + 0] > 0.998f)
	{ // singularity at north pole
		*pitch = atan2f(m[0 * 3 + 2], m[2 * 3 + 2]);
		*yaw = MATH_PI / 2.0f;
		*roll = 0.0f;
	}
	else if (m[1 * 3 + 0] < -0.998f)
	{ // singularity at south pole
		*pitch = atan2f(m[0 * 3 + 2], m[2 * 3 + 2]);
		*yaw = -MATH_PI / 2.0f;
		*roll = 0.0f;
	}
	else
	{
		*pitch = atan2f(-m[2 * 3 + 0], m[0 * 3 + 0]);
		*yaw = asinf(m[1 * 3 + 0]);
		*roll = atan2f(-m[1 * 3 + 2], m[1 * 3 + 1]);
	}
}