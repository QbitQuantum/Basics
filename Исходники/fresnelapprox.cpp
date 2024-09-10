Spectrum FresnelApproxN(const Spectrum &Fr) {
	const Spectrum sqrtReflectance = Fr.Clamp(0.f, .999f).Sqrt();

	return (Spectrum(1.f) + sqrtReflectance) /
		(Spectrum(1.f) - sqrtReflectance);
}