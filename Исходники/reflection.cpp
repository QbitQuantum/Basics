COREDLL Spectrum FresnelApproxEta(const Spectrum &Fr) {
	Spectrum reflectance = Fr.Clamp(0.f, .999f);
	return (Spectrum(1.) + reflectance.Sqrt()) /
		(Spectrum(1.) - reflectance.Sqrt());
}