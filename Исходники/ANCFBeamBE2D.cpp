double ANCFBeamBE2D::GetKappaD(const double& p_loc) const
{
	Vector2D rx = GetPosx2DD(p_loc);
	Vector2D rxx = GetPosxx2DD(p_loc);
	return (rx.Cross(rxx))/rx.Norm2();
}