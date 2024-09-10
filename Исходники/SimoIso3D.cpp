double SimoIso3D::ComputeEnergy(double J, const dSymMatrixT& b_bar)
{
	return U(J) +                          /* volumetric */
	       0.5*Mu()*(b_bar.Trace() - 3.0); /* deviatoric */
}