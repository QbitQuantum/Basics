/////////////////////////////////////////////////////////////////////////////
// Change lane value to reach a given radius
/////////////////////////////////////////////////////////////////////////////
void K1999::AdjustRadius(int prev, int i, int next, double TargetRInverse, double Security)
{
	double OldLane = tLane[i];

	double Width = Mag((txLeft[i]-txRight[i]),(tyLeft[i]-tyRight[i]));

	//
	// Start by aligning points for a reasonable initial lane
	//
	tLane[i] = (-(ty[next] - ty[prev]) * (txLeft[i] - tx[prev]) +
			(tx[next] - tx[prev]) * (tyLeft[i] - ty[prev])) /
			( (ty[next] - ty[prev]) * (txRight[i] - txLeft[i]) -
			(tx[next] - tx[prev]) * (tyRight[i] - tyLeft[i]));

	// the original algorithm allows going outside the track
	/*
	if (tLane[i] < -0.2)
		tLane[i] = -0.2;
	else if (tLane[i] > 1.2)
		tLane[i] = 1.2;*/
	if (tLane[i] < 0.0)
		tLane[i] = 0.0;
	else if (tLane[i] > 1.0)
		tLane[i] = 1.0;

	UpdateTxTy(i);

	//
	// Newton-like resolution method
	//
	const double dLane = 0.0001;

	double dx = dLane * (txRight[i] - txLeft[i]);
	double dy = dLane * (tyRight[i] - tyLeft[i]);

	double dRInverse = GetRInverse(prev, tx[i] + dx, ty[i] + dy, next);

	if (dRInverse > 0.000000001)
	{
		tLane[i] += (dLane / dRInverse) * TargetRInverse;

		double ExtLane = (SideDistExt + Security) / Width;
		double IntLane = (SideDistInt + Security) / Width;
		if (ExtLane > 0.5)
			ExtLane = 0.5;
		if (IntLane > 0.5)
			IntLane = 0.5;

		if (TargetRInverse >= 0.0)
		{
			if (tLane[i] < IntLane)
				tLane[i] = IntLane;
			if (1 - tLane[i] < ExtLane)
			{
				if (1 - OldLane < ExtLane)
					tLane[i] = Min(OldLane, tLane[i]);
				else
					tLane[i] = 1 - ExtLane;
			}
		}
		else
		{
			if (tLane[i] < ExtLane)
			{
				if (OldLane < ExtLane)
					tLane[i] = Max(OldLane, tLane[i]);
				else
					tLane[i] = ExtLane;
			}
			if (1 - tLane[i] < IntLane)
				tLane[i] = 1 - IntLane;
		}
	}

	UpdateTxTy(i);
}