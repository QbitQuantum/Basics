Vector UniformSampleCone(const float u1, const float u2, float costhetamax,
	const Vector &x, const Vector &y, const Vector &z) {
	const float costheta = Lerp(u1, 1.f, costhetamax);
	const float u1x = (1.f - costhetamax) * u1;
	const float sintheta = sqrtf(Max(0.f, u1x * (2.f - u1x)));
	const float phi = u2 * 2.f * M_PI;
	return cosf(phi) * sintheta * x + sinf(phi) * sintheta * y +
		costheta * z;
}