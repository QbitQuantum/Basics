complex<double> CUniformDisk::GetVis(OIUVPtr uv, double wavelength)
{
	// TODO: Implement memoization to speed up computations.
	double b = uv->GetBaselineLength();
	double x = M_PI * mDiameter * b / wavelength;
	return 2 * j1(x) / x;
}