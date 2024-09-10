fixed_t FixedHypot(fixed_t x, fixed_t y)
{
#ifdef HAVE_HYPOT
	const float fx = FIXED_TO_FLOAT(x);
	const float fy = FIXED_TO_FLOAT(y);
	float fz;
#ifdef HAVE_HYPOTF
	fz = hypotf(fx, fy);
#else
	fz = (float)hypot(fx, fy);
#endif
	return FLOAT_TO_FIXED(fz);
#else // !HAVE_HYPOT
	fixed_t ax, yx, yx2, yx1;
	if (abs(y) > abs(x)) // |y|>|x|
	{
		ax = abs(y); // |y| => ax
		yx = FixedDiv(x, y); // (x/y)
	}
	else // |x|>|y|
	{
		ax = abs(x); // |x| => ax
		yx = FixedDiv(y, x); // (x/y)
	}
	yx2 = FixedMul(yx, yx); // (x/y)^2
	yx1 = FixedSqrt(1+FRACUNIT + yx2); // (1 + (x/y)^2)^1/2
	return FixedMul(ax, yx1); // |x|*((1 + (x/y)^2)^1/2)
#endif
}