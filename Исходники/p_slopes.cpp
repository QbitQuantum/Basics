void P_SetSlope (secplane_t *plane, bool setCeil, int xyangi, int zangi, const DVector3 &pos)
{
	DAngle xyang;
	DAngle zang;

	if (zangi >= 180)
	{
		zang = 179.;
	}
	else if (zangi <= 0)
	{
		zang = 1.;
	}
	else
	{
		zang = (double)zangi;
	}
	if (setCeil)
	{
		zang += 180.;
	}

	xyang = (double)xyangi;

	DVector3 norm;

	if (ib_compatflags & BCOMPATF_SETSLOPEOVERFLOW)
	{
		// We have to consider an integer multiplication overflow here.
		norm[0] = FixedToFloat(FloatToFixed(zang.Cos()) * FloatToFixed(xyang.Cos()));
		norm[1] = FixedToFloat(FloatToFixed(zang.Cos()) * FloatToFixed(xyang.Sin()));
	}
	else
	{
		norm[0] = zang.Cos() * xyang.Cos();
		norm[1] = zang.Cos() * xyang.Sin();
	}
	norm[2] = zang.Sin();
	norm.MakeUnit();
	double dist = -norm[0] * pos.X - norm[1] * pos.Y - norm[2] * pos.Z;
	plane->set(norm[0], norm[1], norm[2], dist);
}